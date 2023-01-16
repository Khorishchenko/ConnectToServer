#include <iostream>
#include <chrono>
#include "Login.h"
#include "pch.h"
#include <vector>

#define ASIO_STANDALONE
constexpr auto HOST = "93.184.216.34";
constexpr auto HOST_NAME = "example.com";

#include <asio.hpp>
#include <asio/ts/buffer.hpp>
#include <asio/ts/internet.hpp>

std::unique_ptr<HostPort> EnteringPortHost();
std::unique_ptr<LoginPassword> EnteringLoginPass();
void ReceiveAndHandelMassege(ClientSocket& sock);


std::vector<char> vBuffer(1 * 1024);
void GrabSomeData(asio::ip::tcp::socket& socket) {

    socket.async_read_some(asio::buffer(vBuffer.data(), vBuffer.size()),
        [&](std::error_code ec, std::size_t lenght)
        {
            if (!ec)
            {
                std::cout << "\n\n Read " << lenght << "bytes \n\n";

                for (int i = 0; i < lenght; i++)
                    std::cout << vBuffer[i];

                GrabSomeData(socket);
            }
        }
    );
}

int main()
{
    Login            login;
    asio::error_code ec;

    asio::io_context context;
    asio::io_context::work idleWork(context);

    std::thread thcContext = std::thread([&] {context.run(); });

    std::cout << "Enter an IP address and port of server: " << std::endl;
    login.SetHostPort(EnteringPortHost());

    asio::ip::tcp::endpoint endpoint(asio::ip::make_address(login.GetHost(), ec), login.GetPort());
    asio::ip::tcp::socket socket(context);

    socket.connect(endpoint, ec);
    if (!ec) {
        std::cout << " Connect " << std::endl;
    }
    else {
        std::cout << " Failed to connect " << ec.message() << std::endl;
    }

    if (socket.is_open()) 
    {
        GrabSomeData(socket);

        std::string sRequest =
            "GET /index.html HTTPS/1.1/\r\n"
            "Host: AprioritLLC\r\n"
            "Connection: close\r\n\r\n";

        socket.write_some(asio::buffer(sRequest.data(), sRequest.size()), ec);

        using namespace std::chrono_literals;
        std::this_thread::sleep_for(2000ms);
    }

    system("pause");

    
    //ClientSocket    sockClient;
    //char            recMessage[STRLEN];

    //try
    //{
    //    std::cout << "Enter an IP address and port of server: " << std::endl;
    //    login.SetHostPort(EnteringPortHost());

    //    std::cout << "ATTEMPTING TO CONNECT..." << std::endl << std::endl;
    //    sockClient.ConnectToServer(login.GetHost().c_str(), login.GetPort());

    //    //Recieve message from server (authentication request)
    //    ReceiveAndHandelMassege(sockClient);

    //    std::cout << "Enter an Login and password of server: " << std::endl;
    //    login.SetLoginPassword(EnteringLoginPass());

    //    //send request to server (login)
    //    sockClient.GetAndSendMessage(login.GetLogin());

    //    //Recieve message from server (authentication request)
    //    ReceiveAndHandelMassege(sockClient);

    //    //send request to server (password)
    //    sockClient.GetAndSendMessage(login.GetPassword());

    //    //Recieve message from server (authentication request)
    //    ReceiveAndHandelMassege(sockClient);
    //}
    //catch (const std::exception& ex)
    //{
    //    std::cout << ex.what() << std::endl;
    //    return -1;
    //}

    //while (true) {

    //    ReceiveAndHandelMassege(sockClient);

    //    std::string command;
    //    std::cout << "Please enter the command: ";
    //    std::getline(std::cin, command);

    //    sockClient.GetAndSendMessage(command);

    //    //server responds to selected action
    //    sockClient.RecvData(recMessage, STRLEN);

    //    //if quit is entered, server sends "Goodbye"
    //    std::string temp = recMessage;
    //    if (temp == "INVALID ENTRY")
    //    {
    //        std::cout << recMessage << std::endl;
    //    }
    //    else if (temp == "Goodbye")
    //    {
    //        sockClient.CloseConnection();
    //        std::cout << std::endl << "\t***DISCONNECTED" << std::endl;
    //        system("pause");
    //        return 0;
    //    }
    //    else if (temp == "List")
    //    {
    //        sockClient.List(recMessage);
    //    }
    //}

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
    char recMessage[STRLEN]{};
    socket.RecvData(recMessage, STRLEN);

    std::string temp = recMessage;
    if (temp == "\t***INVALID CREDENTIALS****\nDISCONNECTING")
    {
        socket.CloseConnection();
        throw std::runtime_error("\t***INVALID CREDENTIALS****\nDISCONNECTING");
    }

    std::cout << recMessage;
}