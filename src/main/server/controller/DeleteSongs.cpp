#include "DeleteSongs.h"
#include "GetSongs.h"

DeleteSongs::DeleteSongs(MongoClient *mongo_client) {
    this->mongo_client = mongo_client;
}

http_response DeleteSongs::do_process(http_request request) {
    string song_id = this->get_song_id_from_uri(request.uri);
    optional<value> maybe_result = this->find_song_by_id(std::stol(song_id));
    if(maybe_result) {
        return this->delete_song(maybe_result.value().view());
    }
    return this->send_not_found_response(song_id);
}

optional<value> DeleteSongs::find_song_by_id(long id) {
    LOG->debug("Get song by id {}", id);
    auto builder = bsoncxx::builder::stream::document{};
    value doc_value = builder << "_id" << id << finalize;
    return this->mongo_client->find_one(doc_value.view());
}

string DeleteSongs::get_song_id_from_uri(string uri) {
    string endpoint = this->get_uri(uri);
    smatch m;

    regex r1(DeleteSongs::URI_REGEX);
    regex r2(DeleteSongs::URI_REGEX + "/");

    if (regex_match(endpoint, m, r1)) {
        return m[1];
    }

    regex_match(endpoint, m, r2);
    return m[1];
}

bool DeleteSongs::handles(const mg_str *method, const mg_str *url) {
    return mg_vcmp(method, "DELETE") == 0 && this->uri_matches(url);
}

bool DeleteSongs::uri_matches(const mg_str *mgStr) {
    string endpoint = this->get_uri(string(mgStr->p));
    regex r1(DeleteSongs::URI_REGEX);
    regex r2(DeleteSongs::URI_REGEX + "/");
    smatch m;
    return regex_match(endpoint, m, r1) || regex_match(endpoint, m, r2);
}

string DeleteSongs::get_uri(string uri) {
    return uri.substr(0,uri.find(" "));
}

http_response DeleteSongs::send_not_found_response(string song_id) {
    std::string response = ((json){
            {"status", 404},
            {"message", "Can't find song with id " + song_id}
    }).dump();
    string headers = "Content-Type: application/json;charset=UTF-8";
    return http_response {404, response, headers};
}

http_response DeleteSongs::delete_song(bsoncxx::document::view view) {
    this->mongo_client->delete_one(view);
    return http_response {200, "", "Content-Type: application/json;charset=UTF-8"};
}