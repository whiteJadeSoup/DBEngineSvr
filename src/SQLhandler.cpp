

#include "SQLhandler.hpp"
#include <cppconn/prepared_statement.h>


bool SQLhandler::validate (connection_ptr conn_ptr_, int64_t id, string& passwd)
{

    try
    {
        cout <<  "id: " << id << "password: " << passwd <<endl;
        // 检查连接是否还有效
        if (!conn_ptr_->isValid())
        {
            cout << "conn is invalid!" << endl;
            return false;
        }

        conn_ptr_->setSchema("account");

        sql::PreparedStatement  *prep_stmt =
        conn_ptr_->prepareStatement("SELECT * FROM t_user_auth WHERE id=? AND password=?");

        prep_stmt->setString(1,to_string(id));
        prep_stmt->setString(2, passwd);

        sql::ResultSet* rs = prep_stmt->executeQuery();


        bool result = false;
        if (rs->rowsCount())
        {
            result = true;
        }

        delete prep_stmt;
        delete rs;

        return result;

    }
    catch (sql::SQLException& e)
    {
        cout << "# ERR: SQLException in " << __FILE__;
        cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << endl;
        cout << "# ERR: " << e.what();
        cout << " (MySQL error code: " << e.getErrorCode();
        cout << ", SQLState: " << e.getSQLState() << " )" << endl;
        return false;
    }
}



bool SQLhandler::read_info(connection_ptr conn_, int64_t userid_, vector<string>& result_)
{

    try
    {
        if (!conn_->isValid())
        {
            cout << "conn is invalid!" << endl;
            return false;
        }



        conn_->setSchema("account");

        sql::PreparedStatement* prep_stmt =
            conn_->prepareStatement("SELECT name,nick_name,sex FROM t_user_info WHERE id=?");


        prep_stmt->setString(1, to_string(userid_));
        sql::ResultSet* res = prep_stmt->executeQuery();


        while (res->next())
        {
            result_.push_back(res->getString("name"));
            result_.push_back(res->getString("nick_name"));
            result_.push_back(res->getString("sex"));
        }


        delete prep_stmt;
        delete res;

        return true;

    }
    catch (sql::SQLException& e)
    {
        cout << "# ERR: SQLException in " << __FILE__;
        cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << endl;
        cout << "# ERR: " << e.what();
        cout << " (MySQL error code: " << e.getErrorCode();
        cout << ", SQLState: " << e.getSQLState() << " )" << endl;
        return false;
    }
}



bool SQLhandler::read_contacts(connection_ptr conn_, int64_t user_id_, vector<string>& vPassData)
{

    try
    {
        if (!conn_->isValid())
        {
            cout << "conn is invalid!" << endl;
            return false;
        }

        // 数据库
        conn_->setSchema("account");


        vector<string> contact_ids;
        // 获得联系人列表
        sql::PreparedStatement* prep_stmt =
            conn_->prepareStatement("SELECT c_id FROM t_contacts WHERE u_id=?");

        prep_stmt->setString(1, to_string(user_id_));
        sql::ResultSet* res = prep_stmt->executeQuery();

        while (res->next())
        {
            contact_ids.push_back(res->getString("c_id"));
        }


        // 获得联系人具体信息
        prep_stmt = conn_->prepareStatement("SELECT name, nick_name FROM t_user_info WHERE id=?");

        auto it = contact_ids.begin();
        for(; it != contact_ids.end(); ++it)
        {
            prep_stmt->setString(1, *it);
            res = prep_stmt->executeQuery();

            if (res->next())
            {
                vPassData.push_back(*it);                               // id
                vPassData.push_back(res->getString("name"));            // name
                vPassData.push_back(res->getString("nick_name"));       // nick_name
                vPassData.push_back(res->getString("sex"));
            }
            else
            {
                cout << "No data: " << __FILE__ << endl;
            }
        }



        delete prep_stmt;
        delete res;

        return true;

    }
    catch (sql::SQLException& e)
    {
        cout << "# ERR: SQLException in " << __FILE__;
        cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << endl;
        cout << "# ERR: " << e.what();
        cout << " (MySQL error code: " << e.getErrorCode();
        cout << ", SQLState: " << e.getSQLState() << " )" << endl;
        return false;
    }
}

























