#ifndef CONN_HPP_INCLUDED
#define CONN_HPP_INCLUDED
#include <memory>
#include <cppconn/connection.h>


typedef std::shared_ptr<sql::Connection> db_connect_ptr;

class Conn
{
public:
    Conn (db_connect_ptr );

    void set_use(bool);
    bool is_use();

    void set_conn(db_connect_ptr);
    db_connect_ptr get_conn();

    void close_conn();
private:

    db_connect_ptr m_conn;
    bool m_bInUse;      // 是否在使用中
};

#endif // CONN_HPP_INCLUDED
