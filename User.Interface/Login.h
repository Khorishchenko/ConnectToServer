#pragma once
#include "IFacade.h"

struct HostPort
{
    std::string host;
    uint16_t    port;
};

struct LoginPassword
{
    std::string login;
    std::string password;
};

class Login : public std::exception, public IFacade
{
public:
    Login();

    void SetHostPort(std::unique_ptr<HostPort> data = nullptr) override;
    void SetLoginPassword(std::unique_ptr<LoginPassword> data = nullptr) override;

    ~Login() {}

private:
    std::string m_host;
    uint16_t    m_port;
    std::string m_login;
    std::string m_password;
};