
#include "MsgConn.hpp"
#include "ConnPool.hpp"
#include "CMsg.hpp"
#include "MsgStruct.hpp"
#include "ClientMsgTypeDefine.hpp"


#include "login.pb.h"
#include "contacts.pb.h"


#include <iostream>



MsgConn::MsgConn(io_service& io_)
  :Connection(io_)
{

}





void MsgConn::on_connect()
{
    m_dispatcher.register_message_callback((int)M2D::READ_INFO,
        bind(&MsgConn::handle_read_user_info, this, std::placeholders::_1));


    m_dispatcher.register_message_callback((int)M2D::FETCH_CONTACTS,
        bind(&MsgConn::handle_fetch_contacts, this, std::placeholders::_1));


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

    GOOGLE_PROTOBUF_VERIFY_VERSION;
    using namespace google::protobuf;

    auto descriptor = p_msg_->GetDescriptor();
    const Reflection* rf = p_msg_->GetReflection();
    const FieldDescriptor* f_req_id = descriptor->FindFieldByName("id");


    try
    {
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
    GOOGLE_PROTOBUF_VERIFY_VERSION;
    using namespace google::protobuf;

    auto descriptor = p_msg_->GetDescriptor();
    const Reflection* rf = p_msg_->GetReflection();
    const FieldDescriptor* f_req_id = descriptor->FindFieldByName("id");


    try
    {
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








