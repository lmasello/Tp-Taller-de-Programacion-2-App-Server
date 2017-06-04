//
// Created by german on 06/04/17.
//

#ifndef TP_TALLER_DE_PROGRAMACION_2_APP_SERVER_INTERCEPTOR_H
#define TP_TALLER_DE_PROGRAMACION_2_APP_SERVER_INTERCEPTOR_H


class Interceptor {

public:
    virtual void intercept(struct mg_connection *c, int ev, void *p) = 0;

};


#endif //TP_TALLER_DE_PROGRAMACION_2_APP_SERVER_INTERCEPTOR_H
