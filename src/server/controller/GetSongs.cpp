#include <regex>
#include "GetSongs.h"

GetSongs::GetSongs(MongoClient *mongo_client) {
    this->mongo_client = mongo_client;
}

void GetSongs::process(struct mg_connection *c, int ev, void *p) {
    struct http_message *hm = (struct http_message *) p;

    string song_id = this->get_song_id_from_uri(&hm->uri);
    optional<value> maybe_result = this->find_song_by_id(std::stol(song_id));

    if(maybe_result) {
        this->send_song(maybe_result.value().view(), c);
        return;
    }
    this->send_not_found_response(song_id, c);
}

optional<value> GetSongs::find_song_by_id(long id) {
    auto builder = bsoncxx::builder::stream::document{};
    value doc_value = builder << "_id" << id << finalize;
    return this->mongo_client->find_one(doc_value.view());
}

bool GetSongs::handles(const mg_str *method, const mg_str *url) {
    return mg_vcmp(method, "GET") == 0 && this->uri_matches(url);
}

bool GetSongs::uri_matches(const mg_str *mgStr) {
    string endpoint = this->get_uri(mgStr);
    regex r1(GetSongs::URI_REGEX);
    regex r2(GetSongs::URI_REGEX + "/");
    smatch m;
    return regex_match(endpoint, m, r1) || regex_match(endpoint, m, r2);
}

string GetSongs::get_uri(const mg_str *mgStr) {
    string uri = string(mgStr->p);
    return uri.substr(0,uri.find(" "));
}

/**
 * Either matches /api/songs/{song_id} or /api/songs/{song_id}/
 * @param mgStr
 * @return
 */
string GetSongs::get_song_id_from_uri(mg_str *mgStr) {
    string endpoint = this->get_uri(mgStr);
    smatch m;

    regex r1(GetSongs::URI_REGEX);
    regex r2(GetSongs::URI_REGEX + "/");

    if (regex_match(endpoint, m, r1)) {
        return m[1];
    }

    regex_match(endpoint, m, r2);
    return m[1];
}

void GetSongs::send_not_found_response(string song_id, mg_connection *c) {
    std::string response = ((json){
            {"status", 404},
            {"message", "Can't find song with id " + song_id}
    }).dump();
    mg_send_head(c, 404, response.length(), "Content-Type: application/json;charset=UTF-8");
    mg_printf(c, "%s", response.c_str());

}

void GetSongs::send_song(bsoncxx::document::view view, mg_connection *c) {
    long id = view["_id"].get_int64();
    std::string response = ((json){
            {"id", id},
            {"name", view["name"].get_utf8().value.to_string(),},
            {"content", view["content"].get_utf8().value.to_string()}
    }).dump();
    mg_send_head(c, 200, response.length(), "Content-Type: application/json;charset=UTF-8");
    mg_printf(c, "%s", response.c_str());
}





