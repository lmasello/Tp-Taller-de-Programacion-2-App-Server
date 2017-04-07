
#include "server/Server.h"
#include "server/controller/SongsController.h"

int main(void) {

    Server *server = new Server("8000");
    server->registerController(new SongsController());
    server->start();

    return 0;
}