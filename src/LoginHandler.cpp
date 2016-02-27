
#include "LoginHandler.hpp"
#include "ConnPool.hpp"
#include "CMsg.hpp"
#include "MsgStruct.hpp"
#include "ClientMsgTypeDefine.hpp"
#include <iostream>



LoginHander::LoginHander(ip::tcp::socket login_sock_)
  :Handler(std::move(login_sock_))
{

}



void LoginHander::start()
{
    // connection pool init
    ConnPool::get_instance()->init_ConnPool();
    read_head_from_socket();
}


void LoginHander::process_msg(int type_, string buf_)
{
    switch (type_)
    {
    case (int)L2D::UserValidate:
        handle_UserValidate(buf_);
        break;
    default:
        std::cout << "invalid type." << std::endl;
        break;
    }
}


/**********************************************
 *
 *
 */

void LoginHander::handle_UserValidate (string buf_)
{
    Msg_validate validate;
    deserialization(validate, buf_);


    cout << "id: " << validate.m_id << endl;
    cout << "passwd: " << validate.m_passwd << endl;

    connection_ptr free_conn = ConnPool::get_instance()->get_free_conn();
    bool result = m_sql_handler.Validate(free_conn, validate.m_id, validate.m_passwd);

    Msg_validate_result validate_result;
    validate_result.m_bResult = result;
    validate_result.m_ulUserId = validate.m_id;

    std::cout << "validate result: " << result << std::endl;

    // release conn
    ConnPool::get_instance()->release_conn(free_conn);

    CMsg packet;
    packet.set_msg_type((int)L2D::UserValidate);
    packet.serialization_data_Asio(validate_result);
    send_msg(packet);
}
