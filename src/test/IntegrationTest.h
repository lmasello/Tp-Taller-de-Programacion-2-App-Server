#ifndef MUSIC_IO_APP_SERVERTEST_H
#define MUSIC_IO_APP_SERVERTEST_H

#include <gtest/gtest.h>
#include <thread>
#include "../main/server/Server.h"
#include "../main/mongo/MongoClient.h"
#include "../main/server/controller/PostSongs.h"
#include "../main/server/controller/GetSongs.h"
#include "../main/lib/moongose/mongoose.h"

#include <bsoncxx/json.hpp>
#include "../main/lib/json/json.hpp"

using json = nlohmann::json;

class IntegrationTest : public ::testing::Test {
public:
    IntegrationTest();

    virtual ~IntegrationTest();

private:
    std::thread server_thread;
};


#endif //MUSIC_IO_APP_SERVERTEST_H
