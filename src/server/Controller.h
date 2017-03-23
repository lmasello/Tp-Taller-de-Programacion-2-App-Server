
#ifndef TP_TALLER_DE_PROGRAMACION_2_APP_SERVER_CONTROLLER_H
#define TP_TALLER_DE_PROGRAMACION_2_APP_SERVER_CONTROLLER_H

#include "../lib/mongoose.h"

class Controller {

public:

    virtual void process(struct mg_connection *c, int ev, void *p) = 0;

    virtual bool handles(const mg_str *method, const mg_str *url) = 0;

};


#endif //TP_TALLER_DE_PROGRAMACION_2_APP_SERVER_CONTROLLER_H
