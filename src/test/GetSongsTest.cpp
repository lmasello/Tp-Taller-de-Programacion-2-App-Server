#include "GetSongsTest.h"

#include "../main/server/Server.h"
#include "../main/server/controller/GetSongs.h"

GetSongsTest::GetSongsTest() {
}

TEST (GetSongController, handlesCall) {
    MongoClient* mongo_client = new MongoClient();
    GetSongs *get_songs = new GetSongs(mongo_client);

    const mg_str method = {"GET", 3};
    const mg_str url = {"/api/songs/1.mp3", 16};

    ASSERT_TRUE( get_songs->handles(&method, &url) );
}
