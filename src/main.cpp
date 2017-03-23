#include <iostream>
#include "server/Server.h"

int main(void) {

    Server *server = new Server("8000");
    server->start();

    return 0;
}