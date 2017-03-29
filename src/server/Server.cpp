
#include <iostream>
#include <algorithm>
#include "Server.h"


void http_event_handler(struct mg_connection *c, int ev, void *p) {
    //Only dispatch events when its an http request
    if (ev == MG_EV_HTTP_REQUEST) {
        ((Server *) c->mgr->user_data)->dispatchCall(c, ev, p);
    }
}

const char *mg_status_message(int status_code) {
    switch (status_code) {
        case 206:
            return "Partial Content";
        case 301:
            return "Moved";
        case 302:
            return "Found";
        case 400:
            return "Bad Request";
        case 401:
            return "Unauthorized";
        case 403:
            return "Forbidden";
        case 404:
            return "Not Found";
        case 416:
            return "Requested Range Not Satisfiable";
        case 418:
            return "I'm a teapot";
        case 500:
            return "Internal Server Error";
        case 502:
            return "Bad Gateway";
        case 503:
            return "Service Unavailable";

        default:
            return "OK";
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

    this->sendNotFoundResponse(c);

}

void Server::sendNotFoundResponse(mg_connection *nc) {
    char *message = (char *) "{\"status\": 404}";
    mg_send_head(nc, 404, 0, "Content-Type: application/json;charset=UTF-8");
    mg_printf(nc, "%.*s", strlen(message), message);

    nc->flags |= MG_F_SEND_AND_CLOSE;
    /*
     * {
        "timestamp": 1490305212144,
                "status": 404,
                "error": "Not Found",
                "message": "Not Found",
                "path": "/api/idm/falop"
    }
     *
     * */
}

