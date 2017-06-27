
#ifndef TP_TALLER_DE_PROGRAMACION_2_APP_SERVER_CONTROLLER_H
#define TP_TALLER_DE_PROGRAMACION_2_APP_SERVER_CONTROLLER_H

#include "../../lib/moongose/mongoose.h"
#include "../domain/http_response.h"
#include "../domain/http_request.h"

using namespace std;

class Controller {

public:

    void process(struct mg_connection *c, int ev, void *p);

    virtual http_response do_process(http_request request) = 0;

    virtual bool handles(const mg_str *method, const mg_str *url) = 0;

private:
    string get_uri(const mg_str *mgStr);

};


#endif //TP_TALLER_DE_PROGRAMACION_2_APP_SERVER_CONTROLLER_H
