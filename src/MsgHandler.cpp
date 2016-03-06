
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
    read_head();
}


void MsgHandler::process_msg(int type_, string buf_)
{
    switch (type_)
    {
    case (int)M2D::READ_INFO:
        handle_read_user_info(buf_);
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


void MsgHandler::handle_read_user_info(string buf_)
{
    Msg_login_id user;
    deserialization(user, buf_);

    connection_ptr free_conn = ConnPool::get_instance()->get_free_conn();

    vector<string> result;
    m_sql_handler.read_info(free_conn, user.m_nId, result);

    Msg_user_info user_info;
    user_info.m_nId = user.m_nId;
    user_info.m_strName = result[0];
    user_info.m_strNickName = result[1];


    CMsg packet;
    packet.set_msg_type((int)M2D::READ_INFO);
    packet.serialization_data_Asio(user_info);

    send(packet);
}

