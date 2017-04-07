#include "SongsController.h"

void MongoController::process(struct mg_connection *c, int ev, void *p) {
    if (ev == MG_EV_HTTP_REQUEST) {
        struct http_message *hm = (struct http_message *) p;

        mongocxx::instance instance{}; // This should be done only once.
        mongocxx::uri uri("mongodb://localhost:27017");
        mongocxx::client client(uri);

        mongocxx::database db = client["testdb"];
        mongocxx::collection coll = db["testcollection"];

        auto builder = bsoncxx::builder::stream::document{};
        bsoncxx::document::value doc_value = builder
                << "name" << "MongoDB"
                << "type" << "database"
                << "count" << 1
                << "versions" << bsoncxx::builder::stream::open_array
                << "v3.2" << "v3.0" << "v2.6"
                << close_array
                << "info" << bsoncxx::builder::stream::open_document
                << "x" << 203
                << "y" << 102
                << bsoncxx::builder::stream::close_document
                << bsoncxx::builder::stream::finalize;

        bsoncxx::document::view view = doc_value.view();

        bsoncxx::document::element element = view["name"];
        if(element.type() != bsoncxx::type::k_utf8) {
            // Error
        }
        std::string name = element.get_utf8().value.to_string();

        mongocxx::stdx::optional<mongocxx::result::insert_one> result =
                coll.insert_one(view);

        // We have received an HTTP request. Parsed request is contained in `hm`.
        // Send HTTP reply to the client which shows full original request.
        mg_send_head(c, 200, hm->message.len, "Content-Type: text/plain");
        mg_printf(c, "%.*s", hm->message.len, hm->message.p);
    }

}
bool MongoController::handles(const mg_str *method, const mg_str *url) {
    return mg_vcmp(method, "POST") == 0 && mg_vcmp(url, "/api/mongo") == 0 ;
}
