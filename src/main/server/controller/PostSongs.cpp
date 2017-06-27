#include "PostSongs.h"

PostSongs::PostSongs(MongoClient *mongo_client) {
    this->mongo_client = mongo_client;
}

http_response PostSongs::do_process(http_request request) {
    struct song_t body = this->parse_body(request.body);

    if (this->exists(body.id)) {
        return this->send_already_exists_response(body);
    } else {
        this->save_song(body);
        return this->send_created_response(body);
    }
}

bool PostSongs::exists(long id) {
    auto builder = bsoncxx::builder::stream::document{};
    value doc_value = builder << "_id" << id << finalize;

    optional<value> maybe_result = this->mongo_client->find_one(doc_value.view());

    if(maybe_result)
        return true;

    return false;
}

bool PostSongs::save_song(song_t song) {
    LOG->info("Creating new song {} id: {}", song.name, song.id);
    auto builder = bsoncxx::builder::stream::document{};
    bsoncxx::document::value doc_value = builder
            << "_id" << song.id
            << "name" << song.name
            << "content" << song.content
            << bsoncxx::builder::stream::finalize;

    bsoncxx::document::view view = doc_value.view();
    mongocxx::stdx::optional<mongocxx::result::insert_one> result = this->mongo_client->insert_one(view);
    return false;
}

bool PostSongs::handles(const mg_str *method, const mg_str *url) {
    return mg_vcmp(method, "POST") == 0 && this->uri_matches(url);
}

bool PostSongs::uri_matches(const mg_str *mgStr) {
    string uri = string(mgStr->p);
    string endpoint = uri.substr(0,uri.find(" "));

    regex r1(PostSongs::URI_REGEX);
    regex r2(PostSongs::URI_REGEX + "/");

    smatch m;
    return regex_match(endpoint, m, r1) || regex_match(endpoint, m, r2);
}

http_response PostSongs::send_already_exists_response(song_t song) {
    std::string response = ((json){
            {"status", 409},
            {"message", "Song with id " + std::to_string(song.id) + " already exists"}
    }).dump();
    string headers = "Content-Type: application/json;charset=UTF-8";
    return http_response {409, response, headers};
}

http_response PostSongs::send_created_response(song_t song) {
    std::string response = ((json){
            {"status", 201},
            {"message", "Song with id " + std::to_string(song.id) + " created"}
    }).dump();
    string headers = "Content-Type: application/json;charset=UTF-8";
    return http_response {201, response, headers};
}

song_t PostSongs::parse_body(string json) {
    auto parsed_body = json::parse(json);
    return {
            parsed_body["id"].get<long>(),
            parsed_body["name"].get<std::string>(),
            parsed_body["content"].get<std::string>()
    };
}
