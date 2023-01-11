#pragma once
#include <string>

class ISocket
{
public:
    virtual ~ISocket() = 0;
    virtual void List(char*) = 0;
    virtual bool SendData(const char*) = 0;
    virtual bool RecvData(char*, int) = 0;
    virtual void CloseConnection() = 0;
    virtual void GetAndSendMessage(std::string) = 0;
    virtual void ReceiveFile(std::string) = 0;
};