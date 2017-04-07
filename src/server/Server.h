
#ifndef TP_TALLER_DE_PROGRAMACION_2_APP_SERVER_SERVER_H
#define TP_TALLER_DE_PROGRAMACION_2_APP_SERVER_SERVER_H

#include <vector>
#include "../lib/mongoose.h"
#include "controller/Controller.h"
#include "interceptor/Interceptor.h"
#include "interceptor/JwtInterceptor.h"

class Server {

public:
    Server(const char *port);

    void start();

    void dispatchCall(struct mg_connection *c, int ev, void *p);

    void registerController(Controller *controller);
    void registerInterceptor(Interceptor *interceptor);

private:
    struct mg_mgr mgr;
    struct mg_connection *c;
    std::vector<Controller *> controllers;
    std::vector<Interceptor *> interceptors;

    void sendNotFoundResponse(mg_connection *pConnection);
};


#endif //TP_TALLER_DE_PROGRAMACION_2_APP_SERVER_SERVER_H
