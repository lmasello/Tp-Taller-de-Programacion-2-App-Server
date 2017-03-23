#include "TestController.h"

void TestController::process(struct mg_connection *c, int ev, void *p) {
    mg_http_send_error(c, 502, "Este endpoint no se puede usar");

}
bool TestController::handles(const mg_str *method, const mg_str *url) {
    return mg_vcmp(method, "POST") == 0 && mg_vcmp(url, "/api/v1/sum") == 0 ;
}