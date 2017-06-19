#ifndef MUSIC_IO_APP_TESTUTILS_H
#define MUSIC_IO_APP_TESTUTILS_H


#include <string>
#include "../main/lib/moongose/mongoose.h"
#include "../main/mongo/MongoClient.h"

using namespace std;

static MongoClient *mongo_client = new MongoClient("test");

class TestUtils {
public:
    static string get(string uri);
    static string post(string uri, string body);
};


#endif //MUSIC_IO_APP_TESTUTILS_H
