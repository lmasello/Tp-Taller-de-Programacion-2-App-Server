#include <iostream>
#include "TestUtils.h"

static int s_exit_flag = 0;
static string response;

static void copy_response (http_message *hm) {
    response = std::string(hm->body.p);
}

static void ev_handler(struct mg_connection *nc, int ev, void *ev_data) {
    struct http_message *hm = (struct http_message *) ev_data;
    switch (ev) {
        case MG_EV_CONNECT:
            if (*(int *) ev_data != 0) {
                fprintf(stderr, "connect() failed: %s\n", strerror(*(int *) ev_data));
                s_exit_flag = 1;
            }
            break;
        case MG_EV_HTTP_REPLY:
            nc->flags |= MG_F_CLOSE_IMMEDIATELY;
            copy_response(hm);
            s_exit_flag = 1;
            break;
        case MG_EV_CLOSE:
            if (s_exit_flag == 0) {
                printf("Server closed connection\n");
                s_exit_flag = 1;
            }
            break;
        default:
            break;
    }
}

string TestUtils::get(string uri) {
    struct mg_mgr mgr;
    mg_mgr_init(&mgr, NULL);
    mg_connect_http(&mgr, ev_handler, uri.c_str(), NULL, NULL);
    while (s_exit_flag == 0) {
        mg_mgr_poll(&mgr, 1000);
    }
    mg_mgr_free(&mgr);
    return response;
}
