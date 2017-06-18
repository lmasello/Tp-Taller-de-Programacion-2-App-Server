#ifndef TP_TALLER_DE_PROGRAMACION_2_APP_SERVER_POSTSONGS_H
#define TP_TALLER_DE_PROGRAMACION_2_APP_SERVER_POSTSONGS_H

#include "Controller.h"
#include <cstdint>
#include <iostream>
#include <vector>
#include <bsoncxx/json.hpp>
#include <mongocxx/instance.hpp>
#include <mongocxx/client.hpp>
#include <mongocxx/stdx.hpp>
#include <mongocxx/uri.hpp>
#include <regex>
#include "../../lib/json/json.hpp"
#include "../domain/song.h"
#include "../../mongo/MongoClient.h"
#include "../../logger/Logger.h"

using std::regex;
using std::regex_match;
using std::smatch;
using std::string;
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

class PostSongs : public Controller {
public:
    PostSongs(MongoClient *mongo_client);

    void process(struct mg_connection *c, int ev, void *p);
    bool handles(const mg_str *method, const mg_str *url);

private:
    Logger *LOG = new Logger("POST SONGS", true);
    MongoClient *mongo_client;
    bool exists(long id);
    bool save_song(song_t song);

    string URI_REGEX = "/api/songs";

    bool uri_matches(const mg_str *pStr);

    void send_already_exists_response(song_t song, mg_connection *pConnection);

    void send_created_response(song_t song, mg_connection *pConnection);

    song_t parse_body(string string);
};


#endif //TP_TALLER_DE_PROGRAMACION_2_APP_SERVER_POSTSONGS_H
