#include "Login.h"

std::unique_ptr<HostPort> EnteringPortHost()
{
    int invalidPort = 0;
    std::unique_ptr<HostPort> data(new HostPort);

    data->port = invalidPort;
    do {
        std::cout << "Enter Port: ";
        std::cin >> data->port;
        std::cin.ignore('\n', 1000);

    } while (data->port == invalidPort);

    do {
        std::cout << "Enter host: ";
        std::getline(std::cin, data->host);

    } while (data->host.empty());

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
        m_host = data->login;
        m_password = data->password;
    }
}