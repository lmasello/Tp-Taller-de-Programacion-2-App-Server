#ifndef TP_TALLER_DE_PROGRAMACION_2_APP_SERVER_GETSONGS_H
#define TP_TALLER_DE_PROGRAMACION_2_APP_SERVER_GETSONGS_H

#include "Controller.h"
#include <cstdint>
#include <regex>
#include <iostream>
#include <vector>
#include <bsoncxx/json.hpp>
#include <mongocxx/instance.hpp>
#include <mongocxx/client.hpp>
#include <mongocxx/stdx.hpp>
#include <mongocxx/uri.hpp>
#include "../../lib/json/json.hpp"
#include "../domain/song.h"

using std::string;
using std::regex;
using std::regex_match;
using std::smatch;
using json = nlohmann::json;
using mongocxx::client;
using mongocxx::instance;
using mongocxx::uri;
using mongocxx::options::count;
using bsoncxx::builder::stream::close_array;
using bsoncxx::builder::stream::close_document;
using bsoncxx::builder::stream::document;
using bsoncxx::builder::stream::finalize;
using bsoncxx::builder::stream::open_array;
using bsoncxx::builder::stream::open_document;
using mongocxx::stdx::optional;
using bsoncxx::document::value;

class GetSongs : public Controller {
public:
    GetSongs();

    void process(struct mg_connection *c, int ev, void *p);
    bool handles(const mg_str *method, const mg_str *url);

private:
    mongocxx::client mongoClient;
    mongocxx::database db;
    mongocxx::collection coll;

    optional<value> findSongById(long id);

    string getUri(const mg_str *pStr);
    bool uriMatches(const mg_str *pStr);
};

#endif //TP_TALLER_DE_PROGRAMACION_2_APP_SERVER_GETSONGS_H
