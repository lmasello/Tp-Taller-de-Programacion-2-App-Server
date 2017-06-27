#ifndef MUSIC_IO_APP_DELETESONGS_H
#define MUSIC_IO_APP_DELETESONGS_H

#include <regex>
#include "Controller.h"
#include "../../mongo/MongoClient.h"
#include "../../logger/Logger.h"
#include "../../lib/json/json.hpp"

using std::string;
using std::regex;
using std::regex_match;
using std::smatch;

using json = nlohmann::json;

class DeleteSongs : public Controller {

public:
    DeleteSongs(MongoClient *mongoClient);

    http_response do_process(http_request request);
    bool handles(const mg_str *method, const mg_str *url);

private:
    Logger *LOG = new Logger("DELETE SONGS", true);
    MongoClient *mongo_client;

    http_response delete_song(bsoncxx::document::view view);
    http_response send_not_found_response(string basic_string);
    optional<value> find_song_by_id(long id);
    string get_uri(string uri);

    bool uri_matches(const mg_str *pStr);

    string get_song_id_from_uri(string uri);

    string URI_REGEX = "/api/songs/(.*)";
};


#endif //MUSIC_IO_APP_DELETESONGS_H
