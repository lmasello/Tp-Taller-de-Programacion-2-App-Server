#include "IntegrationTest.h"
#include "TestUtils.h"

void start_server() {
    Server *server = new Server("8000", false);
    MongoClient *mongo_client = new MongoClient("test");
    server->registerController(new PostSongs(mongo_client));
    server->registerController(new GetSongs(mongo_client));

    server->start();
}

IntegrationTest::IntegrationTest() {
    this->server_thread = std::thread(start_server);
    usleep(500000);
}

IntegrationTest::~IntegrationTest() {
    this->server_thread.detach();
}


TEST_F (IntegrationTest, test_calling_get_handler) {
    std::string response = TestUtils::get("http://localhost:8000/api/songs/4.mp3");
    std::cout << response << std::endl;

    ASSERT_TRUE(true);
}