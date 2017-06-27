
#include "server/Server.h"
#include "server/controller/PostSongs.h"
#include "server/controller/GetSongs.h"
#include "server/controller/DeleteSongs.h"

int main(void) {

    Server *server = new Server("8000", true);

    MongoClient *mongo_client = new MongoClient("songs");

    server->registerController(new DeleteSongs(mongo_client));
    server->registerController(new PostSongs(mongo_client));
    server->registerController(new GetSongs(mongo_client));
    server->start();

    return 0;
}