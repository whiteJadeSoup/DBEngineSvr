
#include "Server.hpp"

#include <memory>
#include <iostream>

using err_code = boost::system::error_code;

/**********************************************
 *
 *
 *
 */
Server::Server(io_service& io_, unsigned short port_)
  :m_LoginSock (io_),
   m_LoginAcc (io_, ip::tcp::endpoint(ip::tcp::v4(), port_))

{
    wait_login_accept();
}



/**********************************************
 *
 *
 *
 */
void Server::wait_login_accept()
{
    m_LoginAcc.async_accept(m_LoginSock,
        [this] (const err_code& ec)
        {
            if (!ec)
            {
                std::cout << "connect loginsvr address: "
                     << m_LoginSock.remote_endpoint().address().to_string()
                     << "connect loginsvr port: "
                     << m_LoginSock.remote_endpoint().port() << std::endl;

                // read to start
                std::make_shared<LoginHander>(std::move(m_LoginSock))->start();
            }
            wait_login_accept();
        });
}
