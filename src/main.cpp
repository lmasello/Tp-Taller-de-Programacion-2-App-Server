#include <iostream>
#include "server/Server.h"
#include "SumController.h"
#include "TestController.h"
#include "MongoController.h"

int main(void) {
    Controller *sumController = new SumController();
    Controller *testController = new TestController();
    Controller *mongoController = new MongoController();

    Server *server = new Server("8000");
    server->registerController(sumController);
    server->registerController(testController);
    server->registerController(mongoController);
    server->start();

    return 0;
}