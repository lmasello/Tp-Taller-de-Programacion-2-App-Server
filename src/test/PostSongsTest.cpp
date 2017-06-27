#include "PostSongsTest.h"

long post_song_id = 1;
std::string post_song_name = "test song name";
std::string post_content = "Song content test";
std::string post_encoded_content = "U29uZyBjb250ZW50IHRlc3QK";

TEST_F (PostSongsTest, should_handle_call) {
    //should handle
    const mg_str method = {"POST", 4};
    const mg_str url = {"/api/songs", 10};
    ASSERT_TRUE(this->post_songs->handles(&method, &url));
}

TEST_F (PostSongsTest, should_not_handle_call) {
    //Wrong http verb
    const mg_str method_1 = {"PUT", 3};
    const mg_str url_1 = {"/api/songs", 10};
    ASSERT_FALSE(this->post_songs->handles(&method_1, &url_1));
}

TEST_F (PostSongsTest, should_not_handle_call_2) {
    //Wrong uri
    const mg_str method_3 = {"POST", 4};
    const mg_str url_3 = {"/api/songs/1.mp3", 16};
    ASSERT_FALSE(this->post_songs->handles(& method_3, &url_3));
}

TEST_F (PostSongsTest, should_save_song) {
    string uri = "/api/songs";
    std::string body = ((json){
            {"id", post_song_id},
            {"name", post_song_name},
            {"content", post_encoded_content}
    }).dump();
    http_response response = this->post_songs->do_process({body, uri});
    ASSERT_EQ (response.status, 201);
}

TEST_F (PostSongsTest, should_not_save_song) {
    this->save_song(post_song_id, post_song_name, post_encoded_content);
    string uri = "/api/songs";
    std::string body = ((json){
            {"id", post_song_id},
            {"name", post_song_name},
            {"content", post_encoded_content}
    }).dump();
    http_response response = this->post_songs->do_process({body, uri});
    ASSERT_EQ (response.status, 409);
}

void PostSongsTest::save_song(long song_id, std::string song_name, std::string encoded_content) {
    auto builder = bsoncxx::builder::stream::document{};
    bsoncxx::document::value doc_value = builder
            << "_id" << song_id
            << "name" << song_name
            << "content" << encoded_content
            << bsoncxx::builder::stream::finalize;
    mongo_client->insert_one(doc_value.view());
}