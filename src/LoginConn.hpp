#ifndef LOGINCONN_HPP_INCLUDED
#define LOGINCONN_HPP_INCLUDED

#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/io_service.hpp>
#include <string>



#include "Connection.hpp"
#include "SQLhandler.hpp"
#include "MessageDispatcher.h"



using namespace boost::asio;
using namespace std;

class LoginConn: public Connection
{
public:
    LoginConn (io_service&);


    virtual void on_connect () override;
    virtual void on_recv_msg (int,  pb_message_ptr) override;
    virtual void on_disconnect() override;


private:
    void handle_UserValidate(pb_message_ptr);


private:
    // 数据库处理器
    SQLhandler m_sql_handler;
    // 消息分发器
    MessageDispatcher m_dispatcher;
};


#endif // LOGINHANDLER_HPP_INCLUDED
