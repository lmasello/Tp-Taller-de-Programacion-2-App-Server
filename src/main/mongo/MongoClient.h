#ifndef TP_TALLER_DE_PROGRAMACION_2_APP_SERVER_MONGOCLIENT_H
#define TP_TALLER_DE_PROGRAMACION_2_APP_SERVER_MONGOCLIENT_H

#include <mongocxx/client.hpp>
#include <mongocxx/instance.hpp>

using mongocxx::client;
using mongocxx::instance;
using mongocxx::uri;
using mongocxx::options::count;
using bsoncxx::builder::stream::close_array;
using bsoncxx::builder::stream::close_document;
using bsoncxx::builder::stream::document;
using bsoncxx::builder::stream::finalize;
using bsoncxx::builder::stream::open_array;
using bsoncxx::builder::stream::open_document;
using mongocxx::stdx::optional;
using bsoncxx::document::value;

class MongoClient {

public:

    MongoClient(std::string collection);

    bool exists_song(long id);

    optional<mongocxx::result::insert_one> insert_one(bsoncxx::document::view view);

    optional<value> find_one(bsoncxx::document::view view);

private:
    mongocxx::client mongo_client;
    mongocxx::database db;
    mongocxx::collection coll;

};


#endif //TP_TALLER_DE_PROGRAMACION_2_APP_SERVER_MONGOCLIENT_H
