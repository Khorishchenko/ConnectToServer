#include "pch.h"

Socket::Socket()
{
    if (WSAStartup(MAKEWORD(2, 2), &m_wsaData) != NO_ERROR)
    {
        std::cerr << "Socket Initialization: Error with WSAStartup\n";
        system("pause");
        WSACleanup();
        exit(10);
    }

    //Create a socket
    m_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    if (m_socket == INVALID_SOCKET)
    {
        std::cerr << "Socket Initialization: Error creating socket" << std::endl;
        system("pause");
        WSACleanup();
        exit(11);
    }

    m_backup = m_socket;
}

Socket::~Socket()
{
    WSACleanup();
}

void Socket::List(char* recMessage)
{
    RecvData(recMessage, STRLEN);
    std::string temp = recMessage;

    if (temp != "***No files in directory") {
        int num = atoi(recMessage);
        for (int i = 0; i < num; i++)
        {
            RecvData(recMessage, STRLEN);
            std::cout << std::endl << "\t" << recMessage;
        }
        std::cout << std::endl << std::endl;
    }
}

bool Socket::SendData(const char* buffer)
{
    send(m_socket, buffer, strlen(buffer), 0);
    return true;
}

bool Socket::RecvData(char* buffer, int size)
{
    int i = recv(m_socket, buffer, MSG_SZ, MSG_WAITALL);
    return true;
}

void Socket::CloseConnection()
{
    closesocket(m_socket);
    m_socket = m_backup;
}

void Socket::GetAndSendMessage(std::string message)
{
    SendData(message.c_str());
}

void Socket::ReceiveFile(std::string fileName)
{
    char recMessage[STRLEN];
 
    SendData(fileName.c_str());
    RecvData(recMessage, STRLEN);

    std::string temp = recMessage;
    if (temp == "fail") 
    {
        std::cerr << "\tFile does not exist" << std::endl;
    }
    else if (temp == "okay") 
    {
        std::ofstream fout;
        fout.open(fileName.c_str());

        RecvData(recMessage, STRLEN);
        //cout << "..." << recMessage << endl;

        std::string txt(recMessage);
        while (txt != "EOFEOFEOFEOFEOFEOF") 
        {
            fout << txt << std::endl;
            RecvData(recMessage, STRLEN);
            txt = recMessage;
        }
        fout.close();
    }
}