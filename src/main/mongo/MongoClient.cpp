#include "MongoClient.h"

MongoClient::MongoClient(std::string collection) {
    mongocxx::instance instance{}; // This should be done only once.
    mongocxx::uri uri("mongodb://localhost:27017");
    this->mongo_client = client(uri);
    this->db = mongo_client["music-io"];
    this->coll = db[collection];
}

optional<mongocxx::result::insert_one> MongoClient::insert_one(bsoncxx::document::view view) {
    return this->coll.insert_one(view);
}

optional<value> MongoClient::find_one(bsoncxx::document::view view) {
    return this->coll.find_one(view);
}

optional<mongocxx::result::delete_result> MongoClient::delete_one(bsoncxx::document::view view) {
    return this->coll.delete_one(view);
}

void MongoClient::drop() {
    this->coll.drop();
}
