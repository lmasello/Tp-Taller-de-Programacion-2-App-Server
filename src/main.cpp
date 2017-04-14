
#include "server/Server.h"
#include "server/controller/PostSongs.h"
#include "server/controller/GetSongs.h"

int main(void) {

    Server *server = new Server("8000");
    server->registerController(new PostSongs());
    server->registerController(new GetSongs());
    server->start();

    return 0;
}