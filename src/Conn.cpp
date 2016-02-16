
#include "Conn.hpp"

Conn::Conn(connection_ptr ptr_)
  : m_conn(ptr_), m_bInUse(false)
{

}


connection_ptr Conn::get_conn()
{
    return m_conn;
}

void Conn::set_conn(connection_ptr conn_ptr_)
{
    m_conn = conn_ptr_;
}


void Conn::set_use (bool in_use_)
{
    m_bInUse = in_use_;
}

bool Conn::is_use ()
{
    return m_bInUse;
}


void Conn::close_conn()
{
    if (m_conn->isValid())
    {
        m_conn->close();
    }
}


