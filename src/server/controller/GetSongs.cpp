#include <regex>
#include "GetSongs.h"

GetSongs::GetSongs() {
    mongocxx::instance instance{}; // This should be done only once.
    mongocxx::uri uri("mongodb://localhost:27017");
    this->mongoClient = client(uri);
    this->db = mongoClient["music-io"];
    this->coll = db["songs"];
}

void GetSongs::process(struct mg_connection *c, int ev, void *p) {
    struct http_message *hm = (struct http_message *) p;


    string endpoint = this->getUri(&hm->uri);

    std::string foo("{foo}");
    std::regex r("/api/songs/(.*)/");
    std::smatch m;
    bool result = std::regex_match(endpoint, m, r); // result returns true

    std::cout << m[0] << std::endl; // prints: {foo}
    std::cout << m[1] << std::endl; // prints: {foo} instead of just foo as I would expect





    auto parsed_body = json::parse(hm->body.p);
    struct song_t body = {
            parsed_body["id"].get<long>()
    };

    optional<value> maybe_result = this->findSongById(body.id);

    if(maybe_result) {

        bsoncxx::document::view result = maybe_result.value().view();

        bsoncxx::document::element _id = result["_id"];
        bsoncxx::document::element name = result["name"];
        bsoncxx::document::element content = result["content"];
        struct song_t song = {
                _id.get_int64(),
                name.get_utf8().value.to_string(),
                content.get_utf8().value.to_string()
        };

        std::string response = ((json){
                {"id", song.id},
                {"name", song.name},
                {"content", song.content}
        }).dump();

        mg_send_head(c, 200, response.length(), "Content-Type: application/json;charset=UTF-8");
        mg_printf(c, "%s", response.c_str());

    } else {
        std::string response = ((json){
                {"status", 404},
                {"message", "Can't find song with id " + std::to_string(body.id)}
        }).dump();

        mg_send_head(c, 404, response.length(), "Content-Type: application/json;charset=UTF-8");
        mg_printf(c, "%s", response.c_str());
    }

}

optional<value> GetSongs::findSongById(long id) {
    auto builder = bsoncxx::builder::stream::document{};
    value doc_value = builder << "_id" << id << finalize;

    return this->coll.find_one(doc_value.view());
}

bool GetSongs::handles(const mg_str *method, const mg_str *url) {
    return mg_vcmp(method, "GET") == 0 && this->uriMatches(url);
}

bool GetSongs::uriMatches(const mg_str *mgStr) {
    string endpoint = this->getUri(mgStr);
    regex r1("/api/songs/(.*)/");
    regex r2("/api/songs/(.*)");

    smatch m;
    return regex_match(endpoint, m, r1) || regex_match(endpoint, m, r2);

}

string GetSongs::getUri(const mg_str *mgStr) {
    string uri = string(mgStr->p);
    return uri.substr(0,uri.find(" "));
}



