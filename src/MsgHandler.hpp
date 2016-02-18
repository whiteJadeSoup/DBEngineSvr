#ifndef LOGINHANDLER_HPP_INCLUDED
#define LOGINHANDLER_HPP_INCLUDED

#include <boost/asio/ip/tcp.hpp>
#include "Handler.hpp"
#include "SQLhandler.hpp"

using namespace boost::asio;

class MsgHandler: public Handler
{
public:
    MsgHandler (ip::tcp::socket);


    virtual void start () override;
    virtual void process_msg (int) override;


private:
    void handle_ReadUserInfo();

private:
    SQLhandler m_sql_handler;
};


#endif // LOGINHANDLER_HPP_INCLUDED