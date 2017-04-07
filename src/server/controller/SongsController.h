//
// Created by german on 31/03/17.
//

#ifndef TP_TALLER_DE_PROGRAMACION_2_APP_SERVER_MONGOCONTROLLER_H
#define TP_TALLER_DE_PROGRAMACION_2_APP_SERVER_MONGOCONTROLLER_H

#include "Controller.h"
#include <cstdint>
#include <iostream>
#include <vector>
#include <bsoncxx/json.hpp>
#include <mongocxx/instance.hpp>
#include <mongocxx/client.hpp>
#include <mongocxx/stdx.hpp>
#include <mongocxx/uri.hpp>
#include "../../lib/json/json.hpp"

using std::string;
using json = nlohmann::json;
using mongocxx::client;
using mongocxx::instance;
using mongocxx::uri;
using bsoncxx::builder::stream::close_array;
using bsoncxx::builder::stream::close_document;
using bsoncxx::builder::stream::document;
using bsoncxx::builder::stream::finalize;
using bsoncxx::builder::stream::open_array;
using bsoncxx::builder::stream::open_document;

class SongsController : public Controller {
public:
    SongsController();

    void process(struct mg_connection *c, int ev, void *p);
    bool handles(const mg_str *method, const mg_str *url);

    struct body_type {
        long id;
        string name;
        string content;
    };

private:
    mongocxx::client mongoClient;
    mongocxx::database db;
    mongocxx::collection coll;
};


#endif //TP_TALLER_DE_PROGRAMACION_2_APP_SERVER_MONGOCONTROLLER_H
