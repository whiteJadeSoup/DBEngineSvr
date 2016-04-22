
#include "MsgConn.hpp"
#include "ConnPool.hpp"
#include "CMsg.hpp"
#include "MsgStruct.hpp"
#include "ClientMsgTypeDefine.hpp"


#include "login.pb.h"
#include "contacts.pb.h"
#include "message_cach.pb.h"
#include "channel.pb.h"



#include <iostream>
#include <google/protobuf/repeated_field.h>


MsgConn::MsgConn(io_service& io_)
  :Connection(io_)
{

}





void MsgConn::on_connect()
{
    m_dispatcher.register_message_callback((int)M2D::READ_INFO,
        bind(&MsgConn::handle_read_user_info,           this, std::placeholders::_1));

    m_dispatcher.register_message_callback((int)M2D::FETCH_CONTACTS,
        bind(&MsgConn::handle_fetch_contacts,           this, std::placeholders::_1));

    m_dispatcher.register_message_callback((int)M2D::FETCH_OFFLINE_MESSAGE,
        bind(&MsgConn::handle_fetch_offline_message,    this, std::placeholders::_1));

    m_dispatcher.register_message_callback((int)M2D::SAVE_TO_HISTORY,
        bind(&MsgConn::handle_save_history,             this, std::placeholders::_1));

    m_dispatcher.register_message_callback((int)M2D::FETCH_CHANNELS,
        bind(&MsgConn::handle_fetch_channels,          this, std::placeholders::_1));

    m_dispatcher.register_message_callback((int)M2D::JOIN_CHANNEL,
        bind(&MsgConn::handle_join_channel,            this, std::placeholders::_1));


    // connection pool init
    read_head();
}


void MsgConn::on_recv_msg(int type_, pb_message_ptr p_msg_)
{
    cout << "msg type: " << type_ << endl;
    m_dispatcher.on_message(type_, p_msg_);
}




void MsgConn::on_disconnect()
{


}





/**********************************************************
 *
 *  handle function
 *
 */


void MsgConn::handle_read_user_info(pb_message_ptr p_msg_)
{
    try
    {


        GOOGLE_PROTOBUF_VERIFY_VERSION;
        using namespace google::protobuf;

        auto descriptor = p_msg_->GetDescriptor();
        const Reflection* rf = p_msg_->GetReflection();
        const FieldDescriptor* f_req_id = descriptor->FindFieldByName("id");



        assert(f_req_id && f_req_id->type()==FieldDescriptor::TYPE_INT64);



        int64_t id = rf->GetInt64(*p_msg_, f_req_id);
        cout << "req id: " << id << endl;


        db_connect_ptr free_conn = ConnPool::get_instance()->get_free_conn();

        vector<string> result;
        m_sql_handler.read_info(free_conn, id, result);


        IM::User user;
        user.set_id(id);
        user.set_name(result[0]);
        user.set_nick_name(result[1]);
        user.set_sex(result[2]);



        CMsg packet;
        packet.encode((int)M2D::READ_INFO, user);
        send(packet);

        // release conn
        ConnPool::get_instance()->release_conn(free_conn);

    }
    catch (exception& e)
    {
        cout << "# ERR: exception in " << __FILE__;
        cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << endl;
        cout << "# ERR: " << e.what() << endl;
    }
}


void MsgConn::handle_fetch_contacts(pb_message_ptr p_msg_)
{
    try
    {
        GOOGLE_PROTOBUF_VERIFY_VERSION;
        using namespace google::protobuf;

        auto descriptor = p_msg_->GetDescriptor();
        const Reflection* rf = p_msg_->GetReflection();
        const FieldDescriptor* f_req_id = descriptor->FindFieldByName("id");


        assert(f_req_id && f_req_id->type() == FieldDescriptor::TYPE_INT64);



        int64_t id = rf->GetInt64(*p_msg_, f_req_id);
        cout << "req id: " << id << endl;


        db_connect_ptr conn = ConnPool::get_instance()->get_free_conn();

        vector<string> result;
        m_sql_handler.read_contacts(conn, id, result);


        IM::Contacts contacts;
        contacts.set_req_id(id);

        for(int i = 0; i < result.size(); i += 4)
        {
            IM::User* pUser = contacts.add_contacts();
            pUser->set_id(static_cast<int64_t>(stoi(result[i])));
            pUser->set_name(result[i+1]);
            pUser->set_nick_name(result[i+2]);
            pUser->set_sex(result[i+3]);
        }


        // release conn
        ConnPool::get_instance()->release_conn(conn);

        CMsg packet;
        packet.encode((int)M2D::FETCH_CONTACTS, contacts);
        send(packet);
    }
    catch (exception& e)
    {
        cout << "# ERR: exception in " << __FILE__;
        cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << endl;
        cout << "# ERR: " << e.what() << endl;
    }
}



void MsgConn::handle_fetch_offline_message(pb_message_ptr p_msg_)
{
    try
    {
        GOOGLE_PROTOBUF_VERIFY_VERSION;
        using namespace google::protobuf;

        auto descriptor = p_msg_->GetDescriptor();
        const Reflection* rf = p_msg_->GetReflection();
        const FieldDescriptor* f_req_id = descriptor->FindFieldByName("id");


        assert(f_req_id && f_req_id->type() == FieldDescriptor::TYPE_INT64);



        int64_t id = rf->GetInt64(*p_msg_, f_req_id);
        cout << "req id: " << id << endl;

        db_connect_ptr conn = ConnPool::get_instance()->get_free_conn();

        vector<string> result;
        m_sql_handler.read_offline_message(conn, id, result);


        IM::MessageCach MessageCach;
        MessageCach.set_user_id(id);

        if (result.size() < 3)
        {
            cout << "error! size < 3! req_id: " << id << endl;
            return ;
        }

        for(int i = 0; i < result.size(); i += 3)
        {
            IM::ChatPkt *pMessage = MessageCach.add_chat_message();
            pMessage->set_send_id((int64_t)(stoi(result[i])));
            pMessage->set_content(result[i+1]);
            pMessage->set_send_time(result[i+2]);
        }

        // release conn
        ConnPool::get_instance()->release_conn(conn);

        CMsg packet;
        packet.encode((int)M2D::FETCH_OFFLINE_MESSAGE, MessageCach);
        send(packet);
    }
    catch (exception& e)
    {
        cout << "# ERR: exception in " << __FILE__;
        cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << endl;
        cout << "# ERR: " << e.what() << endl;
    }

}



void MsgConn::handle_save_history(pb_message_ptr p_msg_)
{
    try
    {
        GOOGLE_PROTOBUF_VERIFY_VERSION;
        using namespace google::protobuf;

        auto descriptor = p_msg_->GetDescriptor();
        const Reflection* rf = p_msg_->GetReflection();
        const FieldDescriptor* f_req_id  = descriptor->FindFieldByName("user_id");
        const FieldDescriptor* f_message = descriptor->FindFieldByName("chat_message");


        assert(f_req_id  && f_req_id->type() == FieldDescriptor::TYPE_INT64);
        assert(f_message && f_message->is_repeated());


        int64_t recv_id = rf->GetInt64(*p_msg_, f_req_id);


        vector<string> vPassData;
        RepeatedPtrField<IM::ChatPkt> chat_messages = rf->GetRepeatedPtrField<IM::ChatPkt>(*p_msg_, f_message);

        auto it = chat_messages.begin();
        for(; it != chat_messages.end(); ++it)
        {
            int64_t send_id = it->send_id();
            string content  = it->content();
            string send_tm  = it->send_time();


            vPassData.push_back(to_string(send_id));
            vPassData.push_back(move(content));
            vPassData.push_back(move(send_tm));
        }


        db_connect_ptr conn = ConnPool::get_instance()->get_free_conn();
        m_sql_handler.save_to_history(conn, recv_id, vPassData);


        // release conn
        ConnPool::get_instance()->release_conn(conn);
    }
    catch (exception& e)
    {
        cout << "# ERR: exception in " << __FILE__;
        cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << endl;
        cout << "# ERR: " << e.what() << endl;
    }
}



void MsgConn::handle_fetch_channels(pb_message_ptr p_msg_)
{
    try
    {
        GOOGLE_PROTOBUF_VERIFY_VERSION;
        using namespace google::protobuf;



        vector<string> vResult;
        db_connect_ptr conn_ = ConnPool::get_instance()->get_free_conn();
        m_sql_handler.read_channels(conn_, vResult);


        //copy(vResult.begin(), vResult.end(), ostream_iterator<string>(cout, " "));

        IM::ChannelVec channels;
        for(int i = 0; i < vResult.size(); )
        {
            /// vReulst data:
            /// [loop] channel id, channel_name, count, [loop]user id, name, nick_name, sex
            int channel_id      = stoi(vResult[i]);
            string channel_name = vResult[i+1];
            int member_count    = stoi(vResult[i+2]);


            IM::Channel* pChannel = channels.add_channels();
            pChannel->set_id(channel_id);
            pChannel->set_name(channel_name);

            i += 3;


            for(int j = 0; j < member_count; )
            {
                int64_t user_id         = (int64_t)stoi(vResult[i]);
                string user_name        = vResult[i+1];
                string nick_name        = vResult[i+2];
                string user_sex         = vResult[i+3];

                i += 4;
                j += 1;

                IM::User* pUser = pChannel->add_user();
                pUser->set_id(user_id);
                pUser->set_name(user_name);
                pUser->set_nick_name(nick_name);
                pUser->set_sex(user_sex);

            }
        }


        CMsg packet;
        packet.encode((int)M2D::FETCH_CHANNELS, channels);
        send(packet);


        // release conn
        ConnPool::get_instance()->release_conn(conn_);
    }
    catch (exception& e)
    {
        cout << "# ERR: exception in " << __FILE__;
        cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << endl;
        cout << "# ERR: " << e.what() << endl;
    }

}



void MsgConn::handle_join_channel(pb_message_ptr p_msg_)
{
    TRY


    auto descriptor = p_msg_->GetDescriptor();
    const Reflection* rf = p_msg_->GetReflection();
    const FieldDescriptor* f_req_id     = descriptor->FindFieldByName("user_id");
    const FieldDescriptor* f_channel_id = descriptor->FindFieldByName("channel_id");
    const FieldDescriptor* f_result     = descriptor->FindFieldByName("result");

    assert(f_req_id     && f_req_id->type()     == FieldDescriptor::TYPE_INT64);
    assert(f_channel_id && f_channel_id->type() == FieldDescriptor::TYPE_INT32);
    assert(f_result     && f_result->type()     == FieldDescriptor::TYPE_INT32);



    int64_t  user_id    = rf->GetInt64(*p_msg_, f_req_id);
    int32_t  channel_id = rf->GetInt32(*p_msg_, f_channel_id);


    db_connect_ptr conn_ = ConnPool::get_instance()->get_free_conn();
    vector<string> vResult;
    vector<string> vPassData;
    vPassData.push_back(to_string(user_id));
    vPassData.push_back(to_string(channel_id));


    m_sql_handler.join_channel(conn_, vPassData, vResult);

    if (vResult.empty())
    {
        cout << "handler_join_channel Error!" << endl;
    }
    else
    {
        int result = stoi(vResult[0]);
        rf->SetInt32(&(*p_msg_), f_result, (int32_t)result);

        CMsg packet;
        packet.encode((int)M2D::JOIN_CHANNEL, *p_msg_);
        send(packet);
    }


    /// release conn
    ConnPool::get_instance()->release_conn(conn_);

    CATCH

}






