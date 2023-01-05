#pragma once
#include <iostream>
#include <string>

class IConnect
{
public:
    virtual void ConnectToServer(uint16_t port, std::string host) = 0;
    virtual void LoginToServer(std::string login, std::string password) = 0;
    virtual ~IConnect() = 0;
};