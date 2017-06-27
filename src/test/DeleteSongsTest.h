#ifndef MUSIC_IO_APP_DELETESONGSTEST_H
#define MUSIC_IO_APP_DELETESONGSTEST_H

#include <gtest/gtest.h>
#include "./TestUtils.h"
#include "../main/mongo/MongoClient.h"
#include "../main/server/Server.h"
#include "../main/server/controller/DeleteSongs.h"

class DeleteSongsTest : public ::testing::Test {
protected:
    virtual void SetUp() {
        this->delete_songs = new DeleteSongs(mongo_client);
        mongo_client->drop();
    }

    virtual void TearDown() {
        delete this->delete_songs;
    }

    DeleteSongs *delete_songs;

    void save_song(long song_id, std::string song_name, std::string encoded_content);
};

#endif //MUSIC_IO_APP_DELETESONGSTEST_H
