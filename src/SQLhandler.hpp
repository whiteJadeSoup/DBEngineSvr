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

    bool Validate(connection_ptr, uint64_t, string&);
    bool ReadInfo(connection_ptr, uint64_t, vector<string>&);
private:
};


#endif // SQLHANDLER_HPP_INCLUDED
