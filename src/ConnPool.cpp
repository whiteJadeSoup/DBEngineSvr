
#include "ConnPool.hpp"
#include <mysql_connection.h>
#include <mysql_driver.h>
#include <cppconn/metadata.h>
#include <cppconn/driver.h>
#include <cppconn/connection.h>

#include <algorithm>


/**********************************************
 *
 * Constructor and get instance
 *
 */


ConnPool::ConnPool(string url_, string user_, string passwd_)
  : m_url (std::move(url_)), m_User (std::move(user_)), m_password (std::move(passwd_)),
    m_driver (nullptr), m_conn_min(10), m_conn_max(50), m_active_conn(0)
{
    init_ConnPool();
}


ConnPool* ConnPool::get_instance()
{

    static ConnPool cp("tcp://127.0.0.1:3306", "root", "321");
    return &cp;
}



/**********************************************
 *
 *  init/destory connpool
 */

void ConnPool::init_ConnPool()
{
    try
    {
        m_driver = sql::mysql::get_driver_instance();

        for (int i = 0; i < m_conn_min; ++i)
        {
            m_conns.emplace_back(new_conn());
        }
    }
    catch (sql::SQLException& e)
    {
        cout << "# ERR: SQLException in " << __FILE__;
        cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << endl;
        cout << "# ERR: " << e.what();
        cout << " (MySQL error code: " << e.getErrorCode();
        cout << ", SQLState: " << e.getSQLState() << " )" << endl;
    }
}


void ConnPool::destory_ConnPool()
{
    for_each(m_conns.begin(), m_conns.end(),
        [] (Conn& conn_)
        {
            conn_.close_conn();
        });
}

/**********************************************
 *
 *  get/new/find a conn
 */
db_connect_ptr ConnPool::new_conn()
{
    try
    {
        shared_ptr<sql::Connection> conn(m_driver->connect(m_url, m_User, m_password));

        // 第一次链接， 检查数据库的最大连接数
        if (m_conns.size() == 0)
        {
            sql::DatabaseMetaData* db_meta = conn->getMetaData();
            int max_conn = db_meta->getMaxConnections();

            if ( max_conn > 0 && max_conn > get_conn_max() )
            {
                set_conn_max(max_conn);
            }
        }
        m_active_conn += 1;
        cout << "now active conn: " << m_active_conn << endl;
        return conn;
    }
    catch (sql::SQLException & e)
    {
        cout << "# ERR: SQLException in " << __FILE__;
        cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << endl;
        cout << "# ERR: " << e.what();
        cout << " (MySQL error code: " << e.getErrorCode();
        cout << ", SQLState: " << e.getSQLState() << " )" << endl;
        return nullptr;
    }
}

void ConnPool::release_conn(db_connect_ptr conn_ptr_)
{
     auto it = find_if(m_conns.begin(), m_conns.end(),
                [=] (Conn& conn_)
                {
                    return conn_.get_conn () == conn_ptr_;
                });

    if (it != m_conns.end())
    {
        it->set_use(false);
        cout << "release succ: "<< endl;
    }
    else
    {
        cout << "release error: "<< endl;
    }
}

db_connect_ptr ConnPool::get_free_conn()
{
    db_connect_ptr free_conn = find_free_conn();

    return free_conn;
}

db_connect_ptr ConnPool::find_free_conn()
{
    auto it = find_if(m_conns.begin(), m_conns.end(),
                [] (Conn& conn_)
                {
                    return !conn_.is_use();
                });

    // 连接存在并且始终存活
    if (it != m_conns.end() && it->get_conn()->isValid() )
    {
        it->set_use(true);
        return it->get_conn();
    }

    else if (m_active_conn < m_conn_max)
    {

        db_connect_ptr new_conn_ptr = new_conn();

        if (new_conn_ptr == nullptr)
            return nullptr;

        Conn conn(new_conn_ptr);
        conn.set_use(true);
        m_conns.push_back(conn);
//
        return  new_conn_ptr;
    }

    else
    {
        return nullptr;
    }
}



/**********************************************
 *
 *
 *
 */

void ConnPool::set_conn_max(int max_)
{
    m_conn_max = max_;
}

int ConnPool::get_conn_max()
{
    return m_conn_max;
}

