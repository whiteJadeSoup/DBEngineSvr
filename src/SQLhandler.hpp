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

    bool validate(connection_ptr, int64_t, string&);
    bool read_info(connection_ptr, int64_t, vector<string>&);
private:
};


#endif // SQLHANDLER_HPP_INCLUDED
