#include "pch.h"

void ServerSocket::Listen()
{
    //cout<<"LISTEN FOR CLIENT..."<<endl;

    if (listen(m_socket, 1) == SOCKET_ERROR)
    {
        std::cerr << "ServerSocket: Error listening on socket\n";
        system("pause");
        WSACleanup();
        exit(15);
    }

    struct sockaddr_in clientSocket;
    clientSocket.sin_family = AF_INET;
    int c_len = sizeof(clientSocket);


    //std::cout << "ACCEPT CONNECTION..." << std::endl;
    m_acceptSocket = accept(m_backup, (SOCKADDR*)&clientSocket, &c_len);
    //acceptSocket = accept( myBackup, NULL, NULL );
    while (m_acceptSocket == SOCKET_ERROR)
    {
        m_acceptSocket = accept(m_backup, (SOCKADDR*)&clientSocket, &c_len);
        //acceptSocket = accept( myBackup, NULL, NULL );
    }
    m_socket = m_acceptSocket;

    std::cout << "Accept " << std::endl;

    unsigned long ulAddr = clientSocket.sin_addr.s_addr;
    //char *some_addr;
    char* some_addr;
    some_addr = inet_ntoa(clientSocket.sin_addr);
}

void ServerSocket::Bind(int port)
{
    m_address.sin_family = AF_INET;
    m_address.sin_addr.s_addr = inet_addr("0.0.0.0");
    m_address.sin_port = htons(port);

    // std::cout << "BIND TO PORT " << port << std::endl;

    if (bind(m_socket, (SOCKADDR*)&m_address, sizeof(m_address)) == SOCKET_ERROR)
    {
        std::cerr << "ServerSocket: Failed to connect\n";
        system("pause");
        WSACleanup();
        exit(14);
    }
}

void ServerSocket::StartHosting(int port)
{
    Bind(port);
    Listen();
}
