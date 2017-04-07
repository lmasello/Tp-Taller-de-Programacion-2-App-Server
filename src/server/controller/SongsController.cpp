#include "SongsController.h"

SongsController::SongsController() {
    mongocxx::instance instance{}; // This should be done only once.
    mongocxx::uri uri("mongodb://localhost:27017");
    this->mongoClient = client(uri);
    this->db = mongoClient["music-io"];
    this->coll = db["songs"];
}

void SongsController::process(struct mg_connection *c, int ev, void *p) {
    struct http_message *hm = (struct http_message *) p;

    auto parsed_body = json::parse(hm->body.p);
    struct body_type body = {
            parsed_body["id"].get<long>(),
            parsed_body["name"].get<std::string>(),
            parsed_body["content"].get<std::string>()
    };

    auto builder = bsoncxx::builder::stream::document{};
    bsoncxx::document::value doc_value = builder
            << "_id" << body.id
            << "name" << body.name
            << "content" << body.content
            << bsoncxx::builder::stream::finalize;

    bsoncxx::document::view view = doc_value.view();
    mongocxx::stdx::optional<mongocxx::result::insert_one> result = coll.insert_one(view);

    mg_send_head(c, 201, 0, "Content-Type: application/json;charset=UTF-8");
}

bool SongsController::handles(const mg_str *method, const mg_str *url) {
    return mg_vcmp(method, "POST") == 0 && mg_vcmp(url, "/api/songs") == 0 ;
}
