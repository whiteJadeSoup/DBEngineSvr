
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

    case (int)M2D::FETCH_CONTACTS:
        handle_fetch_contacts(buf_);
        break;

    default:
        cout << "invalid type." << endl;
        break;
    }
}


/**********************************************
 *
 *
 */


void MsgHandler::handle_read_user_info(string buf_)
{
    MSG_LOGIN_ID user;
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


void MsgHandler::handle_fetch_contacts(string buf_)
{
    MSG_LOGIN_ID user_id;
    deserialization(user_id, buf_);

    connection_ptr conn = ConnPool::get_instance()->get_free_conn();

    vector<string> result;
    m_sql_handler.read_contacts(conn, user_id.m_nId, result);


    MSG_CONTACTS contacts;
    contacts.m_req_id = user_id.m_nId;

    for(int i = 0; i < result.size(); i += 3)
    {
        USER user;
        user.m_user_id      = static_cast<int64_t>(stoi(result[i]));
        user.m_name         = result[i+1];
        user.m_nick_name    = result[i+2];

        contacts.m_contacts.push_back(user);
    }


    CMsg packet;
    packet.set_msg_type(static_cast<int>(M2D::FETCH_CONTACTS));
    packet.serialization_data_Asio(contacts);

    send(packet);
}








