#pragma once
#include "pch.h"
const int STRLEN = 256;
#define MSG_SZ 64

class Socket 
{
public:
    Socket();
    ~Socket();
    void List(char*);
    bool SendData(const char*);
    bool RecvData(char*, int);
    void CloseConnection();
    void GetAndSendMessage(std::string message);
    void ReceiveFile(std::string filename);

protected:
    WSADATA     m_wsaData;
    SOCKET      m_socket;
    SOCKET      m_backup;
    SOCKET      m_acceptSocket;
    sockaddr_in m_address;
};