
#include "Server.hpp"


#include "LoginConn.hpp"
#include "MsgConn.hpp"


#include <memory>
#include <iostream>



using err_code = boost::system::error_code;


int Server::g_count = 1;


/**********************************************
 *
 *
 *
 */
Server::Server( unsigned short port_, unsigned short msg_port_)
  :m_io_service(),
   m_LoginAcc(m_io_service, ip::tcp::endpoint(ip::tcp::v4(), port_)),
   m_MsgAcc(m_io_service, ip::tcp::endpoint(ip::tcp::v4(), msg_port_))

{
    wait_login_accept();
    wait_msgsvr_accept();
}


void Server::run()
{
    m_io_service.run();
}


int Server::allocate_conn_id()
{
    return (g_count++) % 65535;
}



/**********************************************
 *
 *
 *
 */
void Server::wait_login_accept()
{

    m_login.reset(new LoginConn(m_io_service));

    m_LoginAcc.async_accept(m_login->socket(), [this] (const err_code& ec)
        {
            if (!ec)
            {
                std::cout << "connect loginsvr address: "
                     << m_login->socket().remote_endpoint().address().to_string()
                     << "connect loginsvr port: "
                     << m_login->socket().remote_endpoint().port() << std::endl;

                int id = allocate_conn_id();
                m_login->connect(id);
            }
            wait_login_accept();
        });
}


void Server::wait_msgsvr_accept()
{
    m_msgsvr.reset(new MsgConn(m_io_service));

    m_MsgAcc.async_accept(m_msgsvr->socket(), [this] (const err_code& ec)
        {
            if (!ec)
            {
                cout << "msgsvr address: "
                     << m_msgsvr->socket().remote_endpoint().address().to_string()
                     << "msgsvr port: "
                     << m_msgsvr->socket().remote_endpoint().port() << endl;

                int id = allocate_conn_id();
                m_msgsvr->connect(id);
            }
            wait_msgsvr_accept();
        });

}
