#include "Login.h"

Login::Login() : m_host(""), m_port(NULL), m_login(""), m_password("")
{
}

Login::~Login()
{
}

void Login::SetHostPort(std::unique_ptr<HostPort> data)
{
    if (data != nullptr) {
        m_host = data->host;
        m_port = data->port;
    }
    else {
        throw std::runtime_error("Error invalid value host/port");
    }
}

void Login::SetLoginPassword(std::unique_ptr<LoginPassword> data)
{
    if (data != nullptr) {
        m_login = data->login;
        m_password = data->password;
    }
    else {
        throw std::runtime_error("Error invalid value login/password");
    }
}

uint16_t Login::GetPort() const
{
    return m_port;
}

std::string Login::GetHost() const
{
    return m_host;
}

std::string Login::GetPassword() const
{
    return m_password;
}

std::string Login::GetLogin() const
{
    return m_login;
}