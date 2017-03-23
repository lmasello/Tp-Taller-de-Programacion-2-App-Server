//
// Created by german on 23/03/17.
//

#include <iostream>
#include "SumController.h"

void SumController::process(struct mg_connection *c, int ev, void *p) {
    if (ev == MG_EV_HTTP_REQUEST) {
        struct http_message *hm = (struct http_message *) p;

        // We have received an HTTP request. Parsed request is contained in `hm`.
        // Send HTTP reply to the client which shows full original request.
        mg_send_head(c, 200, hm->message.len, "Content-Type: text/plain");
        mg_printf(c, "%.*s", hm->message.len, hm->message.p);
    }

}
bool SumController::handles(const mg_str *method, const mg_str *url) {
    return mg_vcmp(method, "GET") == 0 && mg_vcmp(url, "/api/v1/sum") == 0 ;
}
