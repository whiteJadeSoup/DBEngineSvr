#ifndef MSGSTRUCT_HPP_INCLUDED
#define MSGSTRUCT_HPP_INCLUDED

#include <string>
#include "typeinfo.hpp"


struct Msg_validate
{
    Msg_validate ()
    {

    }

    template <typename Archive>
    void serialize(Archive& ar, const unsigned int version)
    {
        ar & m_id;
        ar & m_passwd;
    }

    UL64 m_id;
    std::string m_passwd;
};


struct Msg_validate_result
{
    Msg_validate_result () :m_bResult(false)
    {

    }

    template <typename Archive>
    void serialize(Archive& ar, const unsigned int version)
    {
        ar & m_bResult;
        ar & m_ip;
        ar & m_port;
    }

    bool m_bResult;
    std::string m_ip;
    std::string m_port;
};


#endif // MSGSTRUCT_HPP_INCLUDED
