#include "Controller.h"

void Controller::process(struct mg_connection *c, int ev, void *p) {
    struct http_message *hm = (struct http_message *) p;

    string body = string(hm->body.p).substr(0, hm->body.len);
    string uri = this->get_uri(&hm->uri);
    struct http_request request = {body, uri};
    struct http_response response = this->do_process(request);

    mg_send_head(c, response.status, response.body.length(), response.headers.c_str());
    mg_send(c, (void*) response.body.c_str(), (int) response.body.length());
}

string Controller::get_uri(const mg_str *mgStr) {
    string uri = string(mgStr->p);
    return uri.substr(0,uri.find(" "));
}
