#include "PostSongsTest.h"

static MongoClient *mongo_client = new MongoClient("test");

TEST (post_songs_controller, should_handle_call) {
    PostSongs *post_songs = new PostSongs(mongo_client);

    //should handle
    const mg_str method = {"POST", 4};
    const mg_str url = {"/api/songs", 10};
    ASSERT_TRUE( post_songs->handles(&method, &url) );
}

TEST (post_songs_controller, should_not_handle_call) {
    PostSongs *get_songs = new PostSongs(mongo_client);

    //Wrong http verb
    const mg_str method_1 = {"PUT", 3};
    const mg_str url_1 = {"/api/songs", 10};
    ASSERT_FALSE( get_songs->handles(&method_1, &url_1) );

    //Wrong uri
    const mg_str method_3 = {"POST", 4};
    const mg_str url_3 = {"/api/songs/1.mp3", 16};
    ASSERT_FALSE( get_songs->handles(& method_3, &url_3) );
}