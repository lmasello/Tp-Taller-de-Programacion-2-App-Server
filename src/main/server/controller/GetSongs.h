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
#include "../../mongo/MongoClient.h"
#include "../../logger/Logger.h"
#include "../../lib/base64/base64.h"

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
    GetSongs(MongoClient *mongoClient);

    void process(struct mg_connection *c, int ev, void *p);
    bool handles(const mg_str *method, const mg_str *url);

private:
    Logger *LOG = new Logger("GET SONGS", true);
    MongoClient *mongo_client;
    optional<value> find_song_by_id(long id);
    string get_uri(const mg_str *pStr);
    bool uri_matches(const mg_str *pStr);

    string get_song_id_from_uri(mg_str *pStr);

    string URI_REGEX = "/api/songs/(.*)";

    void send_not_found_response(string basic_string, mg_connection *pConnection);

    void send_song(bsoncxx::document::view view, mg_connection *pConnection);

    bool is_decoded_request(string pStr);

    void send_decoded_song(bsoncxx::document::view view, mg_connection *pConnection);
};

#endif //TP_TALLER_DE_PROGRAMACION_2_APP_SERVER_GETSONGS_H
