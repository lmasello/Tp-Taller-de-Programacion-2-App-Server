
#ifndef TP_TALLER_DE_PROGRAMACION_2_APP_SERVER_SERVER_H
#define TP_TALLER_DE_PROGRAMACION_2_APP_SERVER_SERVER_H

#include <vector>
#include "../lib/mongoose.h"
#include "Controller.h"

class Server {

public:
    Server(const char *port);

    void start();

    void dispatchCall(struct mg_connection *c, int ev, void *p);

    void registerController(Controller *controller);

private:
    struct mg_mgr mgr;
    struct mg_connection *c;
    std::vector<Controller *> controllers;

    void sendNotFoundResponse(mg_connection *pConnection);
};


#endif //TP_TALLER_DE_PROGRAMACION_2_APP_SERVER_SERVER_H
