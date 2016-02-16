#ifndef SERVER_HPP_INCLUDED
#define SERVER_HPP_INCLUDED

#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/io_service.hpp>

#include "LoginHandler.hpp"
using namespace boost::asio;

class Server
{
public:
    Server (io_service&, unsigned short);

    void wait_login_accept();

private:
    // socket for loginSvr
    ip::tcp::socket     m_LoginSock;
    // 监听loginSvr的连接
    ip::tcp::acceptor   m_LoginAcc;
};


#endif // SERVER_HPP_INCLUDED
