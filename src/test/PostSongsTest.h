#ifndef MUSIC_IO_APP_POSTSONGSTEST_H
#define MUSIC_IO_APP_POSTSONGSTEST_H

#include <gtest/gtest.h>
#include "../main/mongo/MongoClient.h"
#include "../main/server/Server.h"
#include "../main/server/controller/PostSongs.h"

class PostSongsTest : public ::testing::Test {
public:
    PostSongsTest();
    virtual ~PostSongsTest();
};


#endif //MUSIC_IO_APP_POSTSONGSTEST_H
