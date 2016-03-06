#ifndef LOGINHANDLER_HPP_INCLUDED
#define LOGINHANDLER_HPP_INCLUDED

#include <boost/asio/ip/tcp.hpp>
#include <string>
#include "Handler.hpp"
#include "SQLhandler.hpp"

using namespace boost::asio;
using namespace std;

class LoginHandler: public Handler
{
public:
    LoginHandler (ip::tcp::socket);


    virtual void start () override;
    virtual void process_msg (int, string) override;

private:
    void handle_UserValidate(string);


private:
    SQLhandler m_sql_handler;
};


#endif // LOGINHANDLER_HPP_INCLUDED
