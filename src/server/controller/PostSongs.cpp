#include "PostSongs.h"

PostSongs::PostSongs() {
    mongocxx::instance instance{}; // This should be done only once.
    mongocxx::uri uri("mongodb://localhost:27017");
    this->mongoClient = client(uri);
    this->db = mongoClient["music-io"];
    this->coll = db["songs"];
}

void PostSongs::process(struct mg_connection *c, int ev, void *p) {
    struct http_message *hm = (struct http_message *) p;

    auto parsed_body = json::parse(hm->body.p);
    struct song_t body = {
            parsed_body["id"].get<long>(),
            parsed_body["name"].get<std::string>(),
            parsed_body["content"].get<std::string>()
    };

    if (this->existsSong(body.id)) {
        std::string response = ((json){
                {"status", 409},
                {"message", "Song with id " + std::to_string(body.id) + " already exists"}
        }).dump();

        mg_send_head(c, 409, response.length(), "Content-Type: application/json;charset=UTF-8");
        mg_printf(c, "%s", response.c_str());
    } else {
        this->saveSong(body);

        std::string response = ((json){
                {"status", 201},
                {"message", "Song with id " + std::to_string(body.id) + " created"}
        }).dump();

        mg_send_head(c, 201, response.length(), "Content-Type: application/json;charset=UTF-8");
        mg_printf(c, "%s", response.c_str());
    }
}

bool PostSongs::existsSong(long id) {
    auto builder = bsoncxx::builder::stream::document{};
    value doc_value = builder << "_id" << id << finalize;

    optional<value> maybe_result = this->coll.find_one(doc_value.view());

    if(maybe_result)
        return true;

    return false;
}

bool PostSongs::saveSong(song_t song) {

    auto builder = bsoncxx::builder::stream::document{};
    bsoncxx::document::value doc_value = builder
            << "_id" << song.id
            << "name" << song.name
            << "content" << song.content
            << bsoncxx::builder::stream::finalize;

    bsoncxx::document::view view = doc_value.view();
    mongocxx::stdx::optional<mongocxx::result::insert_one> result = coll.insert_one(view);
    return false;
}

bool PostSongs::handles(const mg_str *method, const mg_str *url) {
    return mg_vcmp(method, "POST") == 0 && mg_vcmp(url, "/api/songs") == 0 ;
}
