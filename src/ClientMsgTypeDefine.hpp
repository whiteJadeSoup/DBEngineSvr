#ifndef CLIENTMSGTYPEDEFINE_HPP_INCLUDED
#define CLIENTMSGTYPEDEFINE_HPP_INCLUDED

/*********************************************************************************
 *Copyright(C),2010-2011,Your Company
 *FileName: // 文件名
 *Author: shub//作者
 *Version: //版本
 *Date: 2015-1-21//创建日期
 *Description: 消息协议定义//用于主要说明此程序文件完成的主要功能
 *********************************************************************************/


//
//

/*
 * 客户端发给服务器的消息类型编号
 * 服务器返回给客户端的消息编号一致
 *
 * 注释格式:
 * 消息用途
 * @parm    客户端请求的消息参数_: 参数意思
 * @return  服务器返回的消息参数 : 参数意思
 */


//  登陆服务器发送到数据库服务器的消息定义
enum class L2D
{
    /*
     *      玩家账号验证
     *
     * @parm      id_       : 玩家id
     * @parm      password  : 玩家密码
     * @retrun    res       : 登陆结果 0-成功  1-失败
     * @return    ip        : (如果验证成功则返回)监听ip
     * @return    port      : (如果验证成功则返回)监听端口
     */
    VALIDATE                     = 3000,
};


enum class M2D
{

    /*
     *
     * @parm      id          : 玩家id
     * @return    name        : 玩家名称
     * @return    nick_name   : 玩家昵称
     */
    READ_INFO                       = 5000,

    /*
     * 请求联系人列表
     * @parm    user_id
     * @return  int 总人数,
     *          循环
     *          [
     *              int     id,         // 用户id
     *              string  name,       // 姓名
     *              string  nick_name   // 昵称
     *          ]
     */
     FETCH_CONTACTS                 = 5001,

};



#endif // CLIENTMSGTYPEDEFINE_HPP_INCLUDED
