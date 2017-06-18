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

    http_response do_process(http_request request);
    bool handles(const mg_str *method, const mg_str *url);

private:
    Logger *LOG = new Logger("GET SONGS", true);
    MongoClient *mongo_client;
    optional<value> find_song_by_id(long id);
    string get_uri(string uri);
    bool uri_matches(const mg_str *pStr);

    string get_song_id_from_uri(string uri);

    string URI_REGEX = "/api/songs/(.*)";

    http_response send_not_found_response(string basic_string);

    bool is_decoded_request(string pStr);

    http_response send_song(string id, bsoncxx::document::view view);

    http_response send_decoded_song(bsoncxx::document::view view);

    string get_decoded_content(bsoncxx::document::view view);

    string send_decoded_song_headers(bsoncxx::document::view view);
};

#endif //TP_TALLER_DE_PROGRAMACION_2_APP_SERVER_GETSONGS_H
