#pragma once
#include "IConnect.h"

class Connect : public IConnect
{
public:
    Connect();
    void ConnectToServer(uint16_t port, std::string host) override;
    void LoginToServer(std::string login, std::string password) override;

protected:


};

