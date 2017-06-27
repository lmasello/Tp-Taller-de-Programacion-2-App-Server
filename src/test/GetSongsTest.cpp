#include "GetSongsTest.h"

long song_id = 1;
std::string song_name = "test song name";
std::string content = "Song content test";
std::string encoded_content = "U29uZyBjb250ZW50IHRlc3QK";

TEST_F (GetSongsTest, should_handle_call) {
    //should handle
    const mg_str method_1 = {"GET", 3};
    const mg_str url_1 = {"/api/songs/1", 12};
    ASSERT_TRUE(this->get_songs->handles(&method_1, &url_1));
}

TEST_F (GetSongsTest, should_handle_call_with_mp3_extension) {
    //Also with mp3 extension
    const mg_str method_2 = {"GET", 3};
    const mg_str url_2 = {"/api/songs/1.mp3", 16};
    ASSERT_TRUE(get_songs->handles(&method_2, &url_2));
}

TEST_F (GetSongsTest, should_not_handle_call) {
    //Wrong http verb
    const mg_str method_1 = {"PUT", 3};
    const mg_str url_1 = {"/api/songs/1.mp3", 16};
    ASSERT_FALSE(get_songs->handles(&method_1, &url_1));

    const mg_str method_3 = {"POST", 4};
    const mg_str url_3 = {"/api/songs/1.mp3", 16};
    ASSERT_FALSE(get_songs->handles(&method_3, &url_3));
}

TEST_F (GetSongsTest, should_return_song) {
    this->save_song(song_id, song_name, encoded_content);
    http_response response = get_songs->do_process({"", "/api/songs/1"});

    auto parsed_body = json::parse(response.body);
    ASSERT_EQ (parsed_body["id"].get<long>(), song_id);
    ASSERT_EQ (parsed_body["name"].get<std::string>(), song_name);
    ASSERT_EQ (parsed_body["content"].get<std::string>(), encoded_content);
    ASSERT_EQ (response.status, 200);
}

TEST_F (GetSongsTest, should_return_decoded_song) {
    this->save_song(song_id, song_name, encoded_content);
    http_response response = get_songs->do_process({"", "/api/songs/1.mp3"});
    ASSERT_EQ (response.body, content.append("\n"));
    ASSERT_EQ (response.status, 200);
}

TEST_F (GetSongsTest, should_not_found_song) {
    http_response response = get_songs->do_process({"", "/api/songs/1.mp3"});
    ASSERT_EQ (response.status, 404);
}

void GetSongsTest::save_song(long song_id, std::string song_name, std::string encoded_content) {
    auto builder = bsoncxx::builder::stream::document{};
    bsoncxx::document::value doc_value = builder
            << "_id" << song_id
            << "name" << song_name
            << "content" << encoded_content
            << bsoncxx::builder::stream::finalize;
    mongo_client->insert_one(doc_value.view());
}
