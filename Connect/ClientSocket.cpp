#include "pch.h"

void ClientSocket::ConnectToServer(const char* ipAddress, int port)
{
    m_address.sin_family = AF_INET;
    m_address.sin_addr.s_addr = inet_addr(ipAddress);
    // inet_pton(AF_INET, ipAddress, &m_address.sin_addr);
    m_address.sin_port = htons(port);

    // std::cout << "CONNECTED..." << std::endl;

    if (connect(m_socket, (SOCKADDR*)&m_address, sizeof(m_address)) == SOCKET_ERROR)
    {
        std::cerr << "ClientSocket: Failed to connect\n";
        system("pause");
        WSACleanup();
        exit(13);
    }
}
