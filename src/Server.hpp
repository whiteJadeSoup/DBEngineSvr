#ifndef SERVER_HPP_INCLUDED
#define SERVER_HPP_INCLUDED

#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/io_service.hpp>

#include "Connection.hpp"

using namespace boost::asio;
using namespace std;


class Server
{
public:
    Server (unsigned short, unsigned short, unsigned short);

    // 等待loginsvr连接
    void wait_login_accept();
    // 等待msgsvr连接
    void wait_msgsvr_accept();
    // 等待routersvr连接
    void wait_router_accept();

    void run();

private:
    int allocate_conn_id();


private:
    io_service m_io_service;

    // 监听loginSvr的连接
    ip::tcp::acceptor   m_LoginAcc;
    ip::tcp::acceptor   m_MsgAcc;
    ip::tcp::acceptor   m_routerAcc;

private:
    connection_ptr m_login;
    connection_ptr m_msgsvr;
    connection_ptr m_router;

private:
    static int g_count;
};


#endif // SERVER_HPP_INCLUDED
