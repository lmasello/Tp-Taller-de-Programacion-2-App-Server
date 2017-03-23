
#include <iostream>
#include "Server.h"


void http_event_handler(struct mg_connection *c, int ev, void *p) {
    //Only dispatch events when its an http request
    if (ev == MG_EV_HTTP_REQUEST) {
        Server *server = (Server *) c->mgr->user_data;
        server->dispatchCall(c, ev, p);
    }
}

Server::Server(const char *port) {
    struct mg_connection *c;
    mg_mgr_init(&mgr, this);
    c = mg_bind(&mgr, port, http_event_handler);
    mg_set_protocol_http_websocket(c);

}

void Server::start() {
    for (;;) {
        mg_mgr_poll(&mgr, 1000);
    }
}

void Server::dispatchCall(struct mg_connection *c, int ev, void *p) {
    struct http_message *hm = (struct http_message *) p;
    // We have received an HTTP request. Parsed request is contained in `hm`.
    // Send HTTP reply to the client which shows full original request.
    mg_send_head(c, 201, hm->message.len, "Content-Type: text/plain");
    mg_printf(c, "%.*s", hm->message.len, hm->message.p);
}

