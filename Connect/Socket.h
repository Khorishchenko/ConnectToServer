#pragma once
#include "pch.h"

const int STRLEN = 256;

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
    bool ReceiveFile(std::string filename);

protected:
    WSADATA m_wsaData;
    SOCKET m_socket;
    SOCKET m_backup;
    SOCKET m_acceptSocket;
    sockaddr_in m_address;
};


class ServerSocket : public Socket
{
public:
    void Listen();
    void Bind(int port);
    void StartHosting(int port);
};


class ClientSocket : public Socket
{
public:
    void ConnectToServer(const char* ipAddress, int port);
};

