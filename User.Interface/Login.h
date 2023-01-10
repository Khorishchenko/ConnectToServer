#pragma once
#include <iostream>
#include <string>
#include <algorithm>
#include <sstream>

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

class Login : public std::exception
{
public:
    Login();

    void SetHostPort(std::unique_ptr<HostPort> data = nullptr);
    void SetLoginPassword(std::unique_ptr<LoginPassword> data = nullptr);

    ~Login() {}

private:
    std::string m_host;
    uint16_t    m_port;
    std::string m_login;
    std::string m_password;
};