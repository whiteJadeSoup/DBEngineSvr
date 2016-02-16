#ifndef CONN_HPP_INCLUDED
#define CONN_HPP_INCLUDED
#include <memory>
#include <cppconn/connection.h>


typedef std::shared_ptr<sql::Connection> connection_ptr;
class Conn
{
public:
    Conn (connection_ptr );

    void set_use(bool);
    bool is_use();

    void set_conn(connection_ptr);
    connection_ptr get_conn();

    void close_conn();
private:

    connection_ptr m_conn;
    bool m_bInUse;      // 是否在使用中
};

#endif // CONN_HPP_INCLUDED
