#include <regex>
#include "GetSongs.h"

GetSongs::GetSongs(MongoClient *mongo_client) {
    this->mongo_client = mongo_client;
}

http_response GetSongs::do_process(http_request request) {
    string song_id = this->get_song_id_from_uri(request.uri);
    optional<value> maybe_result = this->find_song_by_id(std::stol(song_id));

    if(maybe_result) {
        return this->send_song(song_id, maybe_result.value().view());
    }
    return this->send_not_found_response(song_id);
}

optional<value> GetSongs::find_song_by_id(long id) {
    LOG->debug("Get song by id {}", id);
    auto builder = bsoncxx::builder::stream::document{};
    value doc_value = builder << "_id" << id << finalize;
    return this->mongo_client->find_one(doc_value.view());
}

bool GetSongs::handles(const mg_str *method, const mg_str *url) {
    return mg_vcmp(method, "GET") == 0 && this->uri_matches(url);
}

bool GetSongs::uri_matches(const mg_str *mgStr) {
    string endpoint = this->get_uri(string(mgStr->p));
    regex r1(GetSongs::URI_REGEX);
    regex r2(GetSongs::URI_REGEX + "/");
    smatch m;
    return regex_match(endpoint, m, r1) || regex_match(endpoint, m, r2);
}

string GetSongs::get_uri(string uri) {
    return uri.substr(0,uri.find(" "));
}

/**
 * Either matches /api/songs/{song_id} or /api/songs/{song_id}/
 * @param mgStr
 * @return
 */
string GetSongs::get_song_id_from_uri(string uri) {
    string endpoint = this->get_uri(uri);
    smatch m;

    regex r1(GetSongs::URI_REGEX);
    regex r2(GetSongs::URI_REGEX + "/");

    if (regex_match(endpoint, m, r1)) {
        return m[1];
    }

    regex_match(endpoint, m, r2);
    return m[1];
}

http_response GetSongs::send_not_found_response(string song_id) {
    std::string response = ((json){
            {"status", 404},
            {"message", "Can't find song with id " + song_id}
    }).dump();
    string headers = "Content-Type: application/json;charset=UTF-8";
    return http_response {404, response, headers};
}

http_response GetSongs::send_song(string song_id, bsoncxx::document::view view) {
    if (this->is_decoded_request(song_id)) {
        return this->send_decoded_song(view);
    }

    long id = view["_id"].get_int64();
    std::string response = ((json){
            {"id", id},
            {"name", view["name"].get_utf8().value.to_string(),},
            {"content", view["content"].get_utf8().value.to_string()}
    }).dump();
    string headers = "Content-Type: application/json;charset=UTF-8";
    return http_response {200, response, headers};
}

http_response GetSongs::send_decoded_song(bsoncxx::document::view view) {
    string content = this->get_decoded_content(view);
    string headers = this->send_decoded_song_headers(view);
    return http_response {200, content, headers};
}

string GetSongs::get_decoded_content(bsoncxx::document::view view) {
    std::string decoded = base64_decode(view["content"].get_utf8().value.to_string());
}

string GetSongs::send_decoded_song_headers(bsoncxx::document::view view) {
    string headers = string("Content-Type: audio/mpeg\r\n");
    headers.append("Content-Disposition: attachment; filename=\"");
    headers.append(view["name"].get_utf8().value.to_string()).append("\"\r\n");
    headers.append("Connection: keep-alive\r\n");
    headers.append("Accept-Ranges: bytes");
    return headers;
}

bool GetSongs::is_decoded_request(string songId) {
    if (songId.length() < 4) {
        return false;
    }
    string value = songId.substr(songId.length() - 4, songId.length());
    return value.compare(".mp3") == 0;
}
