#pragma once
#include <iostream>
#include <string>
#include <algorithm>
#include <sstream>

struct HostPort;
struct LoginPassword;

class IFacade {
public:
    virtual void SetHostPort(std::unique_ptr<HostPort> data = nullptr) = 0;
    virtual void SetLoginPassword(std::unique_ptr<LoginPassword>  data = nullptr) = 0;
    virtual ~IFacade() = 0;
};