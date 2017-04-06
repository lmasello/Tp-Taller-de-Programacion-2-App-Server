#include <iostream>
#include "server/Server.h"
#include "SumController.h"
#include "TestController.h"
#include "MongoController.h"
#include "./logger/Logger.h"

int main(void) {

    Logger *LOG = new Logger("Main class");

    LOG->error("Simple log error");
    LOG->error("{} log error", "Not that simple");
    LOG->warn("{} {} {}", "Warning", "log", "line");
    LOG->info("{} {} {}", "Info", "log", "line");
    LOG->debug("{} {} {} {}", "Info", "log", "line", "Should not be printed");

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