#ifndef MSGSTRUCT_HPP_INCLUDED
#define MSGSTRUCT_HPP_INCLUDED

#include <string>



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

    uint64_t m_id;
    std::string m_passwd;
};


struct Msg_validate_result
{
    Msg_validate_result () :m_bResult(false), m_ulUserId(0)
    {

    }

    template <typename Archive>
    void serialize(Archive& ar, const unsigned int version)
    {
        ar & m_bResult;
        ar & m_ulUserId;
    }

    bool m_bResult;
    uint64_t m_ulUserId;
};


struct Msg_user_info
{
    Msg_user_info ()
    {

    }

    template <typename Archive>
    void serialize(Archive& ar, const unsigned int version)
    {
        ar & m_nId;
        ar & m_strName;
        ar & m_strNickName;
    }

    int64_t m_nId;
    string m_strName;
    string m_strNickName;
};


struct Msg_login_id
{

    Msg_login_id (): m_nId(0)
    {

    }

    template <typename Archive>
    void serialize(Archive& ar, const unsigned int version)
    {
        ar & m_nId;
    }

    int64_t  m_nId;
};

#endif // MSGSTRUCT_HPP_INCLUDED
