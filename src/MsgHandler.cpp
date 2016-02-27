
#include "MsgHandler.hpp"
#include "ConnPool.hpp"
#include "CMsg.hpp"
#include "MsgStruct.hpp"
#include "ClientMsgTypeDefine.hpp"

#include <iostream>



MsgHandler::MsgHandler(ip::tcp::socket msg_sock_)
  :Handler(std::move(msg_sock_))
{

}



void MsgHandler::start()
{
    // connection pool init
    read_head_from_socket();
}


void MsgHandler::process_msg(int type_, string buf_)
{
    switch (type_)
    {
    case (int)M2D::ReadUserInfo:
        handle_ReadUserInfo();
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


void MsgHandler::handle_ReadUserInfo()
{
//    Msg_user_id user;
//    deserialization(user, m_rBuf);
//
//    connection_ptr free_conn = ConnPool::get_instance()->get_free_conn();
//
//    vector<string> result;
//    m_sql_handler.ReadInfo(free_conn, user.m_nId, result);
//
//    Msg_user_info user_info;
//    user_info.m_strName = result[0];
//    user_info.m_strNickName = result[1];
//
//
//    CMsg info;
//    info.set_msg_type((int)M2D::ReadUserInfo);
//    info.set_send_data(user_info);
//
//    send_msg(info);
}

