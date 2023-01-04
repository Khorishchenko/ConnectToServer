#pragma once
#include "IFacade.h"
#include <iostream>
#include <string>
#include <algorithm>
#include <sstream>

struct HostPort;
struct LoginPassword;

std::unique_ptr<HostPort> EnteringPortHost();
std::unique_ptr<LoginPassword> EnteringLoginPass();

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

class Login
{
public:
    Login();
    void Start();


protected:
    void SetHostPort(std::unique_ptr<HostPort> data);
    void SetLoginPassword(std::unique_ptr<LoginPassword> data);


private:
    std::string m_host;
    uint16_t    m_port;
    std::string m_login;
    std::string m_password;
};


