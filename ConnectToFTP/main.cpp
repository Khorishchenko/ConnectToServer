#include <iostream>
#include "Login.h"
#include "pch.h"

std::unique_ptr<HostPort> EnteringPortHost();
std::unique_ptr<LoginPassword> EnteringLoginPass();
void ReceiveAndHandelMassege(ClientSocket& sock);

int main()
{
    Login           login;
    ClientSocket    sockClient;
    char            recMessage[STRLEN];

    try
    {
        std::cout << "Enter an IP address and port of server: " << std::endl;
        login.SetHostPort(EnteringPortHost());

        std::cout << "ATTEMPTING TO CONNECT..." << std::endl << std::endl;
        sockClient.ConnectToServer(login.GetHost().c_str(), login.GetPort());

        //Recieve message from server (authentication request)
        ReceiveAndHandelMassege(sockClient);

        std::cout << "Enter an Login and password of server: " << std::endl;
        login.SetLoginPassword(EnteringLoginPass());

        //send request to server (login)
        sockClient.GetAndSendMessage(login.GetLogin());

        //Recieve message from server (authentication request)
        ReceiveAndHandelMassege(sockClient);

        //send request to server (password)
        sockClient.GetAndSendMessage(login.GetPassword());

        //Recieve message from server (authentication request)
        ReceiveAndHandelMassege(sockClient);
    }
    catch (const std::exception& ex)
    {
        std::cout << ex.what() << std::endl;
        return -1;
    }

    while (true) {

        ReceiveAndHandelMassege(sockClient);

        std::string command;
        std::cout << "Please enter the command: ";
        std::getline(std::cin, command);

        sockClient.GetAndSendMessage(command);

        //server responds to selected action
        sockClient.RecvData(recMessage, STRLEN);

        //if quit is entered, server sends "Goodbye"
        std::string temp = recMessage;
        if (temp == "INVALID ENTRY")
        {
            std::cout << recMessage << std::endl;
        }
        else if (temp == "Goodbye")
        {
            sockClient.CloseConnection();
            std::cout << std::endl << "\t***DISCONNECTED" << std::endl;
            system("pause");
            return 0;
        }
        else if (temp == "List")
        {
            sockClient.List(recMessage);
        }
    }

    return 0;
}


std::unique_ptr<HostPort> EnteringPortHost()
{
    std::unique_ptr<HostPort> data(new HostPort);

    do {
        std::cout << "Enter host: ";
        std::getline(std::cin, data->host);

    } while (data->host.empty());

    std::string buffer = "";
    while (true) {
        std::cout << "Enter Port: ";

        std::getline(std::cin, buffer);

        std::stringstream myStream(buffer);
        if ((myStream >> data->port))
            break;
        std::cout << "Invalid input, please try again..." << std::endl;
    }
    std::cin.clear();

    return std::move(data);
}

std::unique_ptr<LoginPassword> EnteringLoginPass()
{
    std::unique_ptr<LoginPassword> data(new LoginPassword);

    do {
        std::cout << "Enter login: ";
        std::getline(std::cin, data->login);

    } while (data->login.empty());

    do {
        std::cout << "Enter password: ";
        std::getline(std::cin, data->password);

    } while (data->password.empty());

    return std::move(data);
}

void ReceiveAndHandelMassege(ClientSocket& socket)
{
    char recMessage[STRLEN];
    socket.RecvData(recMessage, STRLEN);

    std::string temp = recMessage;
    if (temp == "\t***INVALID CREDENTIALS****\nDISCONNECTING")
    {
        socket.CloseConnection();
        throw std::runtime_error("\t***INVALID CREDENTIALS****\nDISCONNECTING");
    }

    std::cout << recMessage;
}