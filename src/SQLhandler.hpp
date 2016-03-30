#ifndef SQLHANDLER_HPP_INCLUDED
#define SQLHANDLER_HPP_INCLUDED

#include <memory>
#include <string>
#include <vector>
#include <mysql_connection.h>


using namespace std;
typedef shared_ptr<sql::Connection> connection_ptr;

class SQLhandler
{
public:
    // 验证用户登陆
    bool validate(connection_ptr, int64_t, string&);
    // 读取用户信息
    bool read_info(connection_ptr, int64_t, vector<string>&);
    //  读取联系信息
    bool read_contacts(connection_ptr, int64_t, vector<string>&);

private:
};


#endif // SQLHANDLER_HPP_INCLUDED
