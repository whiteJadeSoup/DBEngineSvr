#ifndef CONNPOOL_HPP_INCLUDED
#define CONNPOOL_HPP_INCLUDED

#include <vector>
#include "Conn.hpp"


using namespace std;
class ConnPool
{
public:
    static ConnPool* get_instance();

    void init_ConnPool();
    connection_ptr new_conn();

    connection_ptr get_free_conn();
    connection_ptr find_free_conn();

    void release_conn(connection_ptr);
    void destory_ConnPool();

    void set_conn_max(int);
    int get_conn_max();

private:
    ConnPool (std::string, std::string, std::string);

private:
    vector<Conn> m_conns;
    // 链接url
    string m_url;
    // 用户名
    string m_User;
    // 密码
    string m_password;
    sql::Driver* m_driver;


    // 最小连接数
    int m_conn_min;
    // 最大连接数
    int m_conn_max;
    // 当前已用的链接数
    int m_active_conn;

};
#endif // CONNPOOL_HPP_INCLUDED
