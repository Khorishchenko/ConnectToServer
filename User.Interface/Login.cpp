#include "Login.h"

std::unique_ptr<HostPort> EnteringPortHost()
{
    std::unique_ptr<HostPort> data(new HostPort);

    do {
        std::cout << "Enter host: ";
        std::getline(std::cin, data->host);

    } while (data->host.empty());

    int invalidPort = 0;
    std::string buffer = "";

    data->port = invalidPort;
   
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

Login::Login() : m_host(""), m_port(NULL), m_login(""), m_password("")
{
}

void Login::Start()
{
    SetHostPort(EnteringPortHost());
    std::cout << "Connect to server is Ok...." << std::endl;

    SetLoginPassword(EnteringLoginPass());
}

void Login::SetHostPort(std::unique_ptr<HostPort> data)
{
    if (data != nullptr) {
        m_host = data->host;
        m_port = data->port;
    }
}

void Login::SetLoginPassword(std::unique_ptr<LoginPassword> data)
{
    if (data != nullptr) {
        m_login = data->login;
        m_password = data->password;
    }
}