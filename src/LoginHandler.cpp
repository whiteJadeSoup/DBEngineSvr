
#include "LoginHandler.hpp"
#include "ConnPool.hpp"
#include "CMsg.h"
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


void LoginHander::process_msg(int type_)
{
    switch (type_)
    {
    case (int)L2D::UserValidate:
        handle_UserValidate();
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

void LoginHander::handle_UserValidate ()
{
    Msg_validate validate;
    deserialization(validate, m_rBuf);


    connection_ptr free_conn = ConnPool::get_instance()->get_free_conn();
    bool result = m_sql_handler.Validate(free_conn, validate.m_id, validate.m_passwd);

    Msg_validate_result validate_result;
    validate_result.m_bResult = result;
    validate_result.m_ulUserId = validate.m_id;

    std::cout << "validate result: " << result << std::endl;

    // release conn
    ConnPool::get_instance()->release_conn(free_conn);


    CMsg send_to_login;
    send_to_login.set_msg_type((int)L2D::UserValidate);
    send_to_login.set_send_data(validate);
    send_msg(send_to_login);
}
