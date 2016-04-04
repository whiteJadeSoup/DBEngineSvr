
#include "LoginConn.hpp"
#include "ConnPool.hpp"
#include "CMsg.hpp"
#include "MsgStruct.hpp"
#include "ClientMsgTypeDefine.hpp"

#include "validate_result.pb.h"

#include <iostream>
#include <functional>


LoginConn::LoginConn(io_service& io_)
  :Connection(io_)
{

}



void LoginConn::on_connect()
{
    m_dispatcher.register_message_callback((int)L2D::VALIDATE,
        bind(&LoginConn::handle_UserValidate, this, std::placeholders::_1));


    // connection pool init
    ConnPool::get_instance()->init_ConnPool();
    read_head();
}


void LoginConn::on_recv_msg(int type_, pb_message_ptr p_msg_)
{

    cout << "msg type: " << type_ << endl;
    m_dispatcher.on_message(type_, p_msg_);
}

void LoginConn::on_disconnect()
{


}




/**********************************************
 *
 * handle function
 *
 */

void LoginConn::handle_UserValidate (pb_message_ptr p_msg_)
{
    GOOGLE_PROTOBUF_VERIFY_VERSION;
    using namespace google::protobuf;

    auto descriptor = p_msg_->GetDescriptor();
    const Reflection* rf = p_msg_->GetReflection();
    const FieldDescriptor* f_req_id = descriptor->FindFieldByName("id");
    const FieldDescriptor* f_passwd = descriptor->FindFieldByName("passwd");

    try
    {
        int64_t id = rf->GetInt64(*p_msg_, f_req_id);
        string passwd = rf->GetString(*p_msg_, f_passwd);




        db_connect_ptr conn = ConnPool::get_instance()->get_free_conn();
        bool result = m_sql_handler.validate(conn, id, passwd);
        cout << "id: " << id << "validate result: " << result << endl;


        IM::DBValidateResult db_result;
        db_result.set_id(id);
        db_result.set_result(result);


        // release conn
        ConnPool::get_instance()->release_conn(conn);


        CMsg packet;
        packet.encode((int)L2D::VALIDATE, db_result);
        send(packet);
    }
    catch (exception& e)
    {
        cout << "# ERR: exception in " << __FILE__;
        cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << endl;
        cout << "# ERR: " << e.what() << endl;
    }



}
