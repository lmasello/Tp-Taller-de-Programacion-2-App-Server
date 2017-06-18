#include "GetSongsTest.h"

static MongoClient *mongo_client = new MongoClient("test");

TEST (get_songs_controller, should_handle_call) {
    GetSongs *get_songs = new GetSongs(mongo_client);

    //should handle
    const mg_str method_1 = {"GET", 3};
    const mg_str url_1 = {"/api/songs/1", 12};
    ASSERT_TRUE( get_songs->handles(&method_1, &url_1) );
}


TEST (get_songs_controller, should_handle_call_with_mp3_extension) {
    GetSongs *get_songs = new GetSongs(mongo_client);

    //Also with mp3 extension
    const mg_str method_2 = {"GET", 3};
    const mg_str url_2 = {"/api/songs/1.mp3", 16};
    ASSERT_TRUE( get_songs->handles(&method_2, &url_2) );
}

TEST (get_songs_controller, should_not_handle_call) {
    GetSongs *get_songs = new GetSongs(mongo_client);

    //Wrong http verb
    const mg_str method_1 = {"PUT", 3};
    const mg_str url_1 = {"/api/songs/1.mp3", 16};
    ASSERT_FALSE( get_songs->handles(&method_1, &url_1) );

    const mg_str method_3 = {"POST", 4};
    const mg_str url_3 = {"/api/songs/1.mp3", 16};
    ASSERT_FALSE( get_songs->handles(&method_3, &url_3) );
}
