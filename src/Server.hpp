#ifndef SERVER_HPP_INCLUDED
#define SERVER_HPP_INCLUDED

#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/io_service.hpp>

using namespace boost::asio;
using namespace std;


class Server
{
public:
    Server (io_service&, unsigned short, unsigned short);

    void wait_login_accept();

    void wait_msgsvr_accept();

private:
    // socket for loginSvr
    ip::tcp::socket     m_LoginSock;
    // 监听loginSvr的连接
    ip::tcp::acceptor   m_LoginAcc;

    ip::tcp::socket     m_MsgSock;

    ip::tcp::acceptor   m_MsgAcc;
};


#endif // SERVER_HPP_INCLUDED
