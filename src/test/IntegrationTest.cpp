#include "IntegrationTest.h"
#include "TestUtils.h"

bool is_started = false;

void start_server() {
    if (is_started) {
        return;
    }
    Server *server = new Server("8000", true);
    MongoClient *mongo_client = new MongoClient("test");
    server->registerController(new PostSongs(mongo_client));
    server->registerController(new GetSongs(mongo_client));
    is_started = true;
    server->start();
}

IntegrationTest::IntegrationTest() {
    std::cout << "Constructor entrando" << std::endl;
    this->server_thread = std::thread(start_server);
    usleep(500000);
    //this->server_thread.detach();
    std::cout << "Constructor saliendo" << std::endl;
}

IntegrationTest::~IntegrationTest() {
    std::cout << "DESTRUCTOR entrando" << std::endl;
    //this->server_thread.detach();
    std::cout << "DESTRUCTOR saliendo" << std::endl;

}



static string base_url = "http://localhost:8000";
static string non_existent_endpoint = base_url + "/api/endpoint";
static string songs_endpoint = base_url + "/api/songs";

TEST_F (IntegrationTest, should_answer_not_found) {
    auto parsed_body = json::parse(TestUtils::get(non_existent_endpoint));
    ASSERT_EQ (parsed_body["status"].get<long>(), 404);
    ASSERT_EQ (parsed_body["error"].get<std::string>(), "Not Found");
}


TEST (IntegrationTest, should_create_song) {
    std::string content = "dGVzdCBjb250ZW50"; //"test content" base64-encoded

    std::string song = ((json){
            {"id", 1},
            {"name", "test song"},
            {"content", content}
    }).dump();
    auto parsed_body = json::parse(TestUtils::post(songs_endpoint, song));
    ASSERT_EQ (parsed_body["status"].get<long>(), 404);
    ASSERT_EQ (parsed_body["error"].get<std::string>(), "Not Found");
}



/*
TEST_F (IntegrationTest, test_calling_get_handler) {
    std::string response = TestUtils::get("http://localhost:8000/api/songs/4.mp3");
    std::cout << response << std::endl;

    ASSERT_TRUE(true);
}*/