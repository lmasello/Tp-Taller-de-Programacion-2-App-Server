
#include <iostream>
#include <algorithm>
#include "Server.h"


void http_event_handler(struct mg_connection *c, int ev, void *p) {
    //Only dispatch events when its an http request
    if (ev == MG_EV_HTTP_REQUEST) {
        ((Server *) c->mgr->user_data)->dispatchCall(c, ev, p);
    }
}

Server::Server(const char *port) {
    struct mg_connection *c;
    mg_mgr_init(&mgr, this);
    c = mg_bind(&mgr, port, http_event_handler);
    mg_set_protocol_http_websocket(c);
}

void Server::registerController(Controller *controller) {
    controllers.push_back(controller);
}

void Server::start() {
    for (;;) {
        mg_mgr_poll(&mgr, 1000);
    }
}



void Server::dispatchCall(struct mg_connection *c, int ev, void *ev_data) {

    struct http_message *hm = (struct http_message *) ev_data;

    for(Controller *controller : this->controllers) {
        if (controller->handles(&hm->method, &hm->uri)) {
            std::cout << "Handles!";
            controller->process(c, ev, ev_data);
            return;
        }
    }
    mg_http_send_error(c, 500, "No controller found");
}

