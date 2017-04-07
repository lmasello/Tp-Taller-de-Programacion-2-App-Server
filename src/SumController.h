//
// Created by german on 23/03/17.
//

#ifndef TP_TALLER_DE_PROGRAMACION_2_APP_SERVER_MYCONTROLLER_H
#define TP_TALLER_DE_PROGRAMACION_2_APP_SERVER_MYCONTROLLER_H


#include "server/controller/Controller.h"

class SumController : public Controller {
public:
    void process(struct mg_connection *c, int ev, void *p);
    bool handles(const mg_str *method, const mg_str *url);

};


#endif //TP_TALLER_DE_PROGRAMACION_2_APP_SERVER_MYCONTROLLER_H
