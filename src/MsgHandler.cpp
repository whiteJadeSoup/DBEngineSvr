
#include "MsgHandler.hpp"
#include "ConnPool.hpp"
#include "CMsg.h"
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


void MsgHandler::process_msg(int type_)
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

}

