#ifndef TP_TALLER_DE_PROGRAMACION_2_APP_SERVER_REQUEST_H
#define TP_TALLER_DE_PROGRAMACION_2_APP_SERVER_REQUEST_H

#include <string>

using std::string;

struct http_request {
    string body;
    string uri;
};

#endif //TP_TALLER_DE_PROGRAMACION_2_APP_SERVER_REQUEST_H
