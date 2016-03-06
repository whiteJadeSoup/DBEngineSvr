
#include "Server.hpp"


#include "LoginHandler.hpp"
#include "MsgHandler.hpp"


#include <memory>
#include <iostream>

using err_code = boost::system::error_code;

/**********************************************
 *
 *
 *
 */
Server::Server(io_service& io_, unsigned short port_, unsigned short msg_port_)
  :m_LoginSock(io_),
   m_LoginAcc(io_, ip::tcp::endpoint(ip::tcp::v4(), port_)),
   m_MsgSock(io_),
   m_MsgAcc(io_, ip::tcp::endpoint(ip::tcp::v4(), msg_port_))

{
    wait_login_accept();
    wait_msgsvr_accept();
}



/**********************************************
 *
 *
 *
 */
void Server::wait_login_accept()
{
    m_LoginAcc.async_accept(m_LoginSock, [this] (const err_code& ec)
        {
            if (!ec)
            {
                std::cout << "connect loginsvr address: "
                     << m_LoginSock.remote_endpoint().address().to_string()
                     << "connect loginsvr port: "
                     << m_LoginSock.remote_endpoint().port() << std::endl;

                // read to start
                std::make_shared<LoginHandler>(std::move(m_LoginSock))->start();
            }
            wait_login_accept();
        });
}


void Server::wait_msgsvr_accept()
{
    m_MsgAcc.async_accept(m_MsgSock, [this] (const err_code& ec)
        {
            if (!ec)
            {
                cout << "msgsvr address: "
                     << m_MsgSock.remote_endpoint().address().to_string()
                     << "msgsvr port: "
                     << m_MsgSock.remote_endpoint().port() << endl;

                make_shared<MsgHandler>(move(m_MsgSock))->start();
            }
            wait_msgsvr_accept();
        });

}
