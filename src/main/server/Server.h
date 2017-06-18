
#ifndef TP_TALLER_DE_PROGRAMACION_2_APP_SERVER_SERVER_H
#define TP_TALLER_DE_PROGRAMACION_2_APP_SERVER_SERVER_H

#include <vector>
#include "../lib/moongose/mongoose.h"
#include "../lib/json/json.hpp"
#include "controller/Controller.h"
#include "../logger/Logger.h"

using std::string;
using json = nlohmann::json;

class Server {

public:
    Server(const char *port, bool debug);

    virtual ~Server();

    void start();

    void dispatchCall(struct mg_connection *c, int ev, void *p);

    void registerController(Controller *controller);

private:
    Logger *LOG;

    struct mg_mgr mgr;
    struct mg_connection *c;
    std::vector<Controller *> controllers;

    void sendNotFoundResponse(mg_connection *pConnection, http_message* hm);
};


#endif //TP_TALLER_DE_PROGRAMACION_2_APP_SERVER_SERVER_H
