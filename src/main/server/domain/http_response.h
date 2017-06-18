#ifndef TP_TALLER_DE_PROGRAMACION_2_APP_SERVER_RESPONSE_H
#define TP_TALLER_DE_PROGRAMACION_2_APP_SERVER_RESPONSE_H

#include <string>

using std::string;

struct http_response {
    int status;
    string body;
    string headers;
};

#endif //TP_TALLER_DE_PROGRAMACION_2_APP_SERVER_RESPONSE_H
