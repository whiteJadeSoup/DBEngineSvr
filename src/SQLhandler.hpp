#ifndef SQLHANDLER_HPP_INCLUDED
#define SQLHANDLER_HPP_INCLUDED

#include <memory>
#include <string>
#include <vector>
#include <google/protobuf/message.h>
#include <mysql_connection.h>


using namespace std;
typedef shared_ptr<sql::Connection> db_connect_ptr;
typedef shared_ptr<google::protobuf::Message> pb_message_ptr;


class SQLhandler
{
public:
    // 验证用户登陆
    bool validate(db_connect_ptr, int64_t, string&);
    // 读取用户信息
    bool read_info(db_connect_ptr, int64_t, vector<string>&);
    //  读取联系信息
    bool read_contacts(db_connect_ptr, int64_t, vector<string>&);
    // 保存离线消息
    bool save_offline_message(db_connect_ptr, vector<string>&);
    // 保存频道离线消息
    bool save_channel_offline_message(db_connect_ptr, vector<string>&);
    // 读取离线消息
    bool read_offline_message(db_connect_ptr, int64_t, vector<string>&);
    // 读取频道离线消息
    bool read_channel_offline_message(db_connect_ptr, int64_t, vector<string>&);
    // 将离线消息改为历史消息
    bool save_to_history(db_connect_ptr conn_, int64_t, vector<string>&);
    // 保存历史消息
    bool save_channel_history(db_connect_ptr, vector<string>&);
    // 读取频道信息
    bool read_channels(db_connect_ptr, vector<string>&);
    // 加入频道
    bool join_channel(db_connect_ptr, vector<string>&, vector<string>&);
    // 离开频道
    bool exit_channel(db_connect_ptr, vector<string>&, vector<string>&);




private:
    string GetString(istream*);
};


#endif // SQLHANDLER_HPP_INCLUDED
