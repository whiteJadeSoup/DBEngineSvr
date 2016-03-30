#ifndef MSGSTRUCT_HPP_INCLUDED
#define MSGSTRUCT_HPP_INCLUDED

#include <string>
#include <boost/serialization/vector.hpp>


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


struct MSG_LOGIN_ID
{

    MSG_LOGIN_ID (): m_nId(0)
    {

    }

    template <typename Archive>
    void serialize(Archive& ar, const unsigned int version)
    {
        ar & m_nId;
    }

    int64_t  m_nId;
};



struct USER
{
    int64_t     m_user_id;      // id
    string      m_name;         // 姓名
    string      m_nick_name;    // 昵称

    template <typename Archive>
    void serialize(Archive& ar, const unsigned int version)
    {
        ar & m_user_id;
        ar & m_name;
        ar & m_nick_name;
    }

};

struct MSG_CONTACTS
{
    MSG_CONTACTS() :m_req_id(0)
    {

    }

    int64_t             m_req_id;       // 请求者id
    std::vector<USER>   m_contacts;


    template< typename Archive>
    void serialize(Archive& ar, const unsigned int version)
    {
        ar & m_req_id;
        ar & m_contacts;
    }
};
















#endif // MSGSTRUCT_HPP_INCLUDED
