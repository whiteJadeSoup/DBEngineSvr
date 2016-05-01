#include "RouterConn.hpp"
#include "ClientMsgTypeDefine.hpp"
#include "ConnPool.hpp"



#include "chat.pb.h"


static RouterConn* g_router_handler = nullptr;

/**********************************************
 *
 * Constructor
 *
 */

RouterConn::RouterConn(io_service& io_)
  :Connection(io_)
{

}


/**********************************************
 *
 *
 *
 */

void RouterConn::on_connect()
{


    m_dispatcher.register_message_callback((int)R2D::ADD_OFFLINE_MESSAGE,
        bind(&RouterConn::handle_offline_message,           this, std::placeholders::_1));


    m_dispatcher.register_message_callback((int)R2D::ADD_OFFLINE_CHANNEL_MSG,
        bind(&RouterConn::handle_add_channel_offline_msg,   this, std::placeholders::_1));



    g_router_handler = this;
    read_head();
}


void RouterConn::on_disconnect()
{

}



void RouterConn::on_recv_msg(int type_, pb_message_ptr p_msg_)
{
    std::cout << "Recv msg type: " << type_ << std::endl;
    m_dispatcher.on_message(type_, p_msg_);
}



/**********************************************
 *
 *  msg process function
 *
 */

void RouterConn::handle_add_channel_offline_msg(pb_message_ptr p_msg_)
{
    TRY
        auto descriptor = p_msg_->GetDescriptor();
        const Reflection* rf = p_msg_->GetReflection();
        const FieldDescriptor* f_messages = descriptor->FindFieldByName("channel_messages");

        assert(f_messages && f_messages->is_repeated());


        vector<string> vPassData;
        RepeatedPtrField<IM::ChannelChatPkt> chat_messages
            = rf->GetRepeatedPtrField<IM::ChannelChatPkt>(*p_msg_, f_messages);

        auto it = chat_messages.begin();
        for(; it != chat_messages.end(); ++it)
        {

            int64_t send_id = it->send_id();
            int64_t recv_id = it->recv_id();
            int32_t ch_id   = it->channel_id();
            string content  = it->content();
            string send_tm  = it->send_time();


            vPassData.push_back(to_string(send_id));
            vPassData.push_back(to_string(recv_id));
            vPassData.push_back(to_string(ch_id));
            vPassData.push_back(move(content));
            vPassData.push_back(move(send_tm));
        }


        db_connect_ptr free_conn = ConnPool::get_instance()->get_free_conn();
        m_sql_handler.save_channel_offline_message(free_conn, vPassData);

        ConnPool::get_instance()->release_conn(free_conn);

    CATCH
}



void RouterConn::handle_offline_message(pb_message_ptr p_msg_)
{
    try
    {

        GOOGLE_PROTOBUF_VERIFY_VERSION;
        using namespace google::protobuf;

        auto descriptor = p_msg_->GetDescriptor();
        const Reflection* rf = p_msg_->GetReflection();
        const FieldDescriptor* f_send_id = descriptor->FindFieldByName("send_id");
        const FieldDescriptor* f_recv_id = descriptor->FindFieldByName("recv_id");
        const FieldDescriptor* f_content = descriptor->FindFieldByName("content");
        const FieldDescriptor* f_send_tm = descriptor->FindFieldByName("send_time");


        assert(f_send_id && f_send_id->type()==FieldDescriptor::TYPE_INT64);
        assert(f_recv_id && f_recv_id->type()==FieldDescriptor::TYPE_INT64);
        assert(f_content && f_content->type()==FieldDescriptor::TYPE_BYTES);
        assert(f_send_tm && f_send_tm->type()==FieldDescriptor::TYPE_STRING);



        int64_t send_id = rf->GetInt64(*p_msg_,  f_send_id);
        int64_t recv_id = rf->GetInt64(*p_msg_,  f_recv_id);
        string  content = rf->GetString(*p_msg_, f_content);
        string  send_tm = rf->GetString(*p_msg_, f_send_tm);


        vector<string> vPassData;
        vPassData.push_back(to_string(send_id));
        vPassData.push_back(to_string(recv_id));
        vPassData.push_back(content);
        vPassData.push_back(send_tm);


        db_connect_ptr free_conn = ConnPool::get_instance()->get_free_conn();
        m_sql_handler.save_offline_message(free_conn, vPassData);

        ConnPool::get_instance()->release_conn(free_conn);

    }
    catch (exception& e)
    {
        cout << "# ERR: exception in " << __FILE__;
        cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << endl;
        cout << "# ERR: " << e.what() << endl;
    }
}



void send_to_router (CMsg& msg)
{
    if (g_router_handler)
        g_router_handler->send(msg);
}

