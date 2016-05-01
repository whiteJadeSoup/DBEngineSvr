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
    READ_INFO                               = 5000,

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
     FETCH_CONTACTS                         = 5001,

    /*
     * 请求离线消息
     * @parm    user_id
     * @return  int 总消息数,
     *          循环
     *          [
     *              int     id,         // 发送者id
     *              string  content,       // 内容
     *          ]
     */
     FETCH_OFFLINE_MESSAGE                  = 5002,

     /*
      *  保存历史信息
      */
     SAVE_TO_HISTORY                        = 5003,

     /*
      *  保存频道聊天历史信息
      */
     SAVE_CHANNEL_HISTORY                   = 5004,

     FETCH_CHANNEL_OFFLINE_MESSAGE          = 5005,


     /*
      * 读取频道信息
      */
     FETCH_CHANNELS                         = 5010,

     /*
      * 请求加入频道
      */
     JOIN_CHANNEL                           = 5011,
     /*
      * 请求频道里玩家信息
      */
     CHANNEL_USER_UPDATE                    = 5012,
     /*
      * 请求离开频道
      */
     EXIT_CHANNEL                           = 5013,
};




// 数据库服务器与路由服务器消息定义
enum class R2D
{
    /*
     *  添加一条离线消息
     * @parm send_id    : 发送者id
     * @parm recv_id    : 接受者id
     * @parm content    : 聊天内容
     */

    ADD_OFFLINE_MESSAGE     = 4000,

    /*
     *  添加一条或者多条频道离线消息
     */
    ADD_OFFLINE_CHANNEL_MSG = 4001,

};




#endif // CLIENTMSGTYPEDEFINE_HPP_INCLUDED
