#ifndef SQLHANDLER_HPP_INCLUDED
#define SQLHANDLER_HPP_INCLUDED

#include <memory>
#include <string>
#include <vector>
#include <mysql_connection.h>


using namespace std;
typedef shared_ptr<sql::Connection> db_connect_ptr;

class SQLhandler
{
public:
    // 验证用户登陆
    bool validate(db_connect_ptr, int64_t, string&);
    // 读取用户信息
    bool read_info(db_connect_ptr, int64_t, vector<string>&);
    //  读取联系信息
    bool read_contacts(db_connect_ptr, int64_t, vector<string>&);

private:
};


#endif // SQLHANDLER_HPP_INCLUDED
