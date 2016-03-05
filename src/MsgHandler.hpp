#ifndef LOGINHANDLER_HPP_INCLUDED
#define LOGINHANDLER_HPP_INCLUDED

#include <boost/asio/ip/tcp.hpp>
#include <string>
#include "Handler.hpp"
#include "SQLhandler.hpp"

using namespace boost::asio;
using namespace std;

class MsgHandler: public Handler
{
public:
    MsgHandler (ip::tcp::socket);


    virtual void start () override;
    virtual void process_msg (int, string) override;


private:
    void handle_read_user_info(string);

private:
    SQLhandler m_sql_handler;
};


#endif // LOGINHANDLER_HPP_INCLUDED
