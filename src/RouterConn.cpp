#include "RouterConn.hpp"
#include "ClientMsgTypeDefine.hpp"
#include "ConnPool.hpp"



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
        bind(&RouterConn::handle_offline_message, this, std::placeholders::_1));



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


        assert(f_send_id && f_send_id->type()==FieldDescriptor::TYPE_INT64);
        assert(f_recv_id && f_recv_id->type()==FieldDescriptor::TYPE_INT64);
        assert(f_content && f_content->type()==FieldDescriptor::TYPE_STRING);

        int64_t send_id = rf->GetInt64(*p_msg_, f_send_id);
        int64_t recv_id = rf->GetInt64(*p_msg_, f_recv_id);
        string content = rf->GetString(*p_msg_, f_content);


        vector<string> vPassData;
        vPassData.push_back(to_string(send_id));
        vPassData.push_back(to_string(recv_id));
        vPassData.push_back(content);


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

