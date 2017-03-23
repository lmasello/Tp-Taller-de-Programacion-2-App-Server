#include <iostream>
#include "server/Server.h"
#include "SumController.h"
#include "TestController.h"

int main(void) {
    Controller *sumController = new SumController();
    Controller *testController = new TestController();

    Server *server = new Server("8000");
    server->registerController(sumController);
    server->registerController(testController);
    server->start();

    return 0;
}