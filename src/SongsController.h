//
// Created by german on 31/03/17.
//

#ifndef TP_TALLER_DE_PROGRAMACION_2_APP_SERVER_MONGOCONTROLLER_H
#define TP_TALLER_DE_PROGRAMACION_2_APP_SERVER_MONGOCONTROLLER_H

#include "server/controller/Controller.h"
#include <cstdint>
#include <iostream>
#include <vector>
#include <bsoncxx/json.hpp>
#include <mongocxx/instance.hpp>
#include <mongocxx/client.hpp>
#include <mongocxx/stdx.hpp>
#include <mongocxx/uri.hpp>

using bsoncxx::builder::stream::close_array;
using bsoncxx::builder::stream::close_document;
using bsoncxx::builder::stream::document;
using bsoncxx::builder::stream::finalize;
using bsoncxx::builder::stream::open_array;
using bsoncxx::builder::stream::open_document;

class MongoController : public Controller {
public:
    void process(struct mg_connection *c, int ev, void *p);
    bool handles(const mg_str *method, const mg_str *url);

};


#endif //TP_TALLER_DE_PROGRAMACION_2_APP_SERVER_MONGOCONTROLLER_H
