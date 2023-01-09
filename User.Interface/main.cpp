#include <iostream>
#include "Login.h"
#include "IConnect.h"

std::unique_ptr<HostPort> EnteringPortHost();
std::unique_ptr<LoginPassword> EnteringLoginPass();

int main()
{
    std::unique_ptr<Login> facade(new Login());
    
    try
    {
        facade->SetHostPort(EnteringPortHost());
        std::cout << "Connect to server is Ok...." << std::endl;

        facade->SetLoginPassword(EnteringLoginPass());
    }
    catch (const std::exception& ex)
    {
        std::cout << ex.what() << std::endl;
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
