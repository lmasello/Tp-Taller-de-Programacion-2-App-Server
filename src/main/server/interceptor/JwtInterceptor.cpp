#include "JwtInterceptor.h"

void JwtInterceptor::intercept(struct mg_connection *c, int ev, void *p) {
    struct http_message *hm = (struct http_message *) p;
    mg_str *authorizationHeader = mg_get_http_header(hm, "Authorization");

    if (authorizationHeader == NULL) {
        return;
    } else {
        string value = std::string(authorizationHeader->p);
        LOG->debug("Authorized request to {}", hm->uri.p);

        //TODO implement jwt validation
    }
}
