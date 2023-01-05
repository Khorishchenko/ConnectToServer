#pragma once
#include <iostream>

class BaseComponent;
class Mediator {
public:
    virtual void Notify(BaseComponent* sender, std::string event) const = 0;
};