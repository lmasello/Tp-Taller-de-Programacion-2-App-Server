#include <iostream>
#include <algorithm>
#include "Server.h"


void http_event_handler(struct mg_connection *c, int ev, void *p) {
    //Only dispatch events when its an http request
    if (ev == MG_EV_HTTP_REQUEST) {
        ((Server *) c->mgr->user_data)->dispatchCall(c, ev, p);
    }
}

Server::Server(const char *port, bool debug) {
    LOG = new Logger("Server", debug);
    LOG->info("Building new server on port {}", port);

    struct mg_connection *c;
    mg_mgr_init(&mgr, this);
    c = mg_bind(&mgr, port, http_event_handler);
    if (c == NULL) {
        LOG->error("Can not bind port {} to server. Shutting down!", port);
        exit(1);
    }
    mg_set_protocol_http_websocket(c);
}

Server::~Server() {
    delete LOG;
    for(Controller *controller : this->controllers) {
        delete controller;
    }
    delete c;
}

void Server::registerController(Controller *controller) {
    LOG->info("Registering new controller");
    this->controllers.push_back(controller);
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
            controller->process(c, ev, ev_data);
            return;
        }
    }

    this->sendNotFoundResponse(c, hm);

}

void Server::sendNotFoundResponse(mg_connection *nc, http_message *hm) {
    string uri = string(hm->uri.p);
    std::size_t pos = uri.find(" ");

    std::string body = ((json){
            {"status", 404},
            {"error", "Not Found"},
            {"path", uri.substr(0,pos)}
    }).dump();

    mg_send_head(nc, 404, body.length(), "Content-Type: application/json;charset=UTF-8");
    mg_printf(nc, "%s", body.c_str());

    nc->flags |= MG_F_SEND_AND_CLOSE;
}

