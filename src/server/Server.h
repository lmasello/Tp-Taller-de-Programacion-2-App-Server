
#ifndef TP_TALLER_DE_PROGRAMACION_2_APP_SERVER_SERVER_H
#define TP_TALLER_DE_PROGRAMACION_2_APP_SERVER_SERVER_H

#include "../lib/mongoose.h"

class Server {

public:
    Server(const char *port);

    void start();

    void dispatchCall(mg_connection *pConnection, int i, void *pVoid);

private:
    struct mg_mgr mgr;
    struct mg_connection *c;

};


#endif //TP_TALLER_DE_PROGRAMACION_2_APP_SERVER_SERVER_H
