//
// Created by german on 23/03/17.
//

#ifndef TP_TALLER_DE_PROGRAMACION_2_APP_SERVER_TESTCONTROLLER_H
#define TP_TALLER_DE_PROGRAMACION_2_APP_SERVER_TESTCONTROLLER_H


#include "server/Controller.h"

class TestController : public Controller {

public:
    virtual void process(struct mg_connection *c, int ev, void *p);

    virtual bool handles(const mg_str *method, const mg_str *url);
};


#endif //TP_TALLER_DE_PROGRAMACION_2_APP_SERVER_TESTCONTROLLER_H
