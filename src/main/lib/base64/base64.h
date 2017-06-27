#ifndef TP_TALLER_DE_PROGRAMACION_2_APP_SERVER_BASE64_H
#define TP_TALLER_DE_PROGRAMACION_2_APP_SERVER_BASE64_H


#include <string>

std::string base64_encode(unsigned char const* , unsigned int len);
std::string base64_decode(std::string const& s);


#endif //TP_TALLER_DE_PROGRAMACION_2_APP_SERVER_BASE64_H
