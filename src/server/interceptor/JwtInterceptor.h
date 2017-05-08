#ifndef TP_TALLER_DE_PROGRAMACION_2_APP_SERVER_JWTINTERCEPTOR_H
#define TP_TALLER_DE_PROGRAMACION_2_APP_SERVER_JWTINTERCEPTOR_H

#include <string>
#include "Interceptor.h"
#include "../../lib/moongose/mongoose.h"
#include "../../logger/Logger.h"

class JwtInterceptor : public Interceptor {

public:

    void intercept(struct mg_connection *c, int ev, void *p);


private:
    Logger *LOG = new Logger("Jwt Interceptor");
};


#endif //TP_TALLER_DE_PROGRAMACION_2_APP_SERVER_JWTINTERCEPTOR_H
