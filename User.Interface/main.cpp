#include <iostream>
#include "Login.h"
#include "IFacade.h"
#include "Mediator.h"

int main()
{
    std::unique_ptr<Login> startApp(new Login());
    startApp->Start();
}