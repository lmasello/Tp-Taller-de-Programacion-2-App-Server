#include "DeleteSongsTest.h"

long delete_song_id = 1;
std::string delete_song_name = "test song name";
std::string delete_content = "Song content test";
std::string delete_encoded_content = "U29uZyBjb250ZW50IHRlc3QK";

TEST_F (DeleteSongsTest, should_handle_call) {
    //should handle
    const mg_str method_1 = {"DELETE", 6};
    const mg_str url_1 = {"/api/songs/1", 12};
    ASSERT_TRUE(this->delete_songs->handles(&method_1, &url_1));
}

TEST_F (DeleteSongsTest, should_not_handle_call) {
    //Wrong http verb
    const mg_str method_1 = {"PUT", 3};
    const mg_str url_1 = {"/api/songs/1.mp3", 16};
    ASSERT_FALSE(this->delete_songs->handles(&method_1, &url_1));

    const mg_str method_3 = {"POST", 4};
    const mg_str url_3 = {"/api/songs/1.mp3", 16};
    ASSERT_FALSE(this->delete_songs->handles(&method_3, &url_3));
}

TEST_F (DeleteSongsTest, should_delete_song) {
    this->save_song(delete_song_id, delete_song_name, delete_encoded_content);
    http_response response = this->delete_songs->do_process({"", "/api/songs/1"});
    ASSERT_EQ (response.status, 200);
}

TEST_F (DeleteSongsTest, should_not_found_song) {
    http_response response = this->delete_songs->do_process({"", "/api/songs/1.mp3"});
    ASSERT_EQ (response.status, 404);
}

void DeleteSongsTest::save_song(long song_id, std::string song_name, std::string encoded_content) {
    auto builder = bsoncxx::builder::stream::document{};
    bsoncxx::document::value doc_value = builder
            << "_id" << song_id
            << "name" << song_name
            << "content" << encoded_content
            << bsoncxx::builder::stream::finalize;
    mongo_client->insert_one(doc_value.view());
}
