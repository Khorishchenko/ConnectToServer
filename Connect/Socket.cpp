#include "pch.h"
#include "Socket.h"

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
    int i = recv(m_socket, buffer, size, 0);
    buffer[i] = '\0';
    return true;
}

void Socket::CloseConnection()
{
    closesocket(m_socket);
    m_socket = m_backup;
}

void Socket::GetAndSendMessage()
{
    char message[STRLEN];

    std::cin.ignore();
    std::cout << "Send > ";
    std::cin.get(message, STRLEN);
    SendData(message);
}

bool Socket::ReceiveFile(std::string fileName)
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

void ServerSocket::StartHosting(int port)
{
    Bind(port);
    Listen();
}


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

    //cout<<"BIND TO PORT "<<port<<endl;

    if (bind(m_socket, (SOCKADDR*)&m_address, sizeof(m_address)) == SOCKET_ERROR)
    {
        std::cerr << "ServerSocket: Failed to connect\n";
        system("pause");
        WSACleanup();
        exit(14);
    }
}

void ClientSocket::ConnectToServer(const char* ipAddress, int port)
{
    m_address.sin_family = AF_INET;
    m_address.sin_addr.s_addr = inet_addr(ipAddress);
    m_address.sin_port = htons(port);

    //cout<<"CONNECTED"<<endl;

    if (connect(m_socket, (SOCKADDR*)&m_address, sizeof(m_address)) == SOCKET_ERROR)
    {
        std::cerr << "ClientSocket: Failed to connect\n";
        system("pause");
        WSACleanup();
        exit(13);
    }
}