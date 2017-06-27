#ifndef TP_TALLER_DE_PROGRAMACION_2_APP_SERVER_GETSONGSTEST_H
#define TP_TALLER_DE_PROGRAMACION_2_APP_SERVER_GETSONGSTEST_H

#include <gtest/gtest.h>
#include "./TestUtils.h"
#include "../main/mongo/MongoClient.h"
#include "../main/server/Server.h"
#include "../main/server/controller/GetSongs.h"

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

class GetSongsTest : public ::testing::Test {
protected:
    virtual void SetUp() {
        this->get_songs = new GetSongs(mongo_client);
        mongo_client->drop();
    }

    virtual void TearDown() {
        delete this->get_songs;
    }

    GetSongs *get_songs;

    void save_song(long song_id, std::string song_name, std::string encoded_content);
};


#endif //TP_TALLER_DE_PROGRAMACION_2_APP_SERVER_GETSONGSTEST_H
