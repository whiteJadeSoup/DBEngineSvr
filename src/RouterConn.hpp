#ifndef ROUTER_HPP_INCLUDED
#define ROUTER_HPP_INCLUDED


#include "Connection.hpp"
#include "SQLhandler.hpp"
#include "MessageDispatcher.h"


using namespace std;
using namespace boost::asio;

class RouterConn: public Connection
{
public:
    RouterConn (io_service&);

public:
    virtual void on_connect () override;
    virtual void on_recv_msg(int, pb_message_ptr) override;
    virtual void on_disconnect() override;

private:
    // 存储离线消息
    void handle_offline_message(pb_message_ptr);
    // 存储频道离线消息
    void handle_add_channel_offline_msg(pb_message_ptr);

private:
    MessageDispatcher m_dispatcher;
    // 数据库处理器
    SQLhandler m_sql_handler;
};


void send_to_router(CMsg&);

#endif // ROUTER_HPP_INCLUDED
