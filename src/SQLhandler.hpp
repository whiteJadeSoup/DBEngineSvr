#ifndef SQLHANDLER_HPP_INCLUDED
#define SQLHANDLER_HPP_INCLUDED

#include <memory>
#include <string>
#include <mysql_connection.h>

#include "typeinfo.hpp"

typedef std::shared_ptr<sql::Connection> connection_ptr;

class SQLhandler
{
public:

    bool Validate(connection_ptr, UL64, std::string&);
private:
};


#endif // SQLHANDLER_HPP_INCLUDED
