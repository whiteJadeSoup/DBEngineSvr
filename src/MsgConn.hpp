#ifndef MSGHANDLER_HPP_INCLUDED
#define MSGHANDLER_HPP_INCLUDED

#include <boost/asio/ip/tcp.hpp>
#include <string>

#include "Connection.hpp"
#include "SQLhandler.hpp"
#include "MessageDispatcher.h"


using namespace boost::asio;
using namespace std;



class MsgConn: public Connection
{
public:
    MsgConn (io_service& );

    virtual void on_connect () override;
    virtual void on_recv_msg (int, pb_message_ptr) override;
    virtual void on_disconnect() override;


private:
    // 读取用户信息
    void handle_read_user_info(pb_message_ptr);
    // 获取联系人列表
    void handle_fetch_contacts(pb_message_ptr);
    // 获取离线消息
    void handle_fetch_offline_message(pb_message_ptr);
    // 保存历史信息
    void handle_save_history(pb_message_ptr);

private:
    SQLhandler m_sql_handler;
    MessageDispatcher m_dispatcher;


};


#endif // MSGHANDLER_HPP_INCLUDED
