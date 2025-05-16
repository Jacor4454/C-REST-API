#include <gtest/gtest.h>

#include "../src/http_server/http_server.h"
#include "../src/http_server/APIresponces/File.h"

namespace my {
namespace project {
namespace {

// The fixture for testing class Foo.
class HTTPTest : public testing::Test {
    protected:
    // You can remove any or all of the following functions if their bodies would
    // be empty.

    HTTPTest() {
        // You can do set-up work for each test here.
    }

    ~HTTPTest() override {
        // You can do clean-up work that doesn't throw exceptions here.
    }

    // If the constructor and destructor are not enough for setting up
    // and cleaning up each test, you can define the following methods:

    void SetUp() override {
        // Code here will be called immediately after the constructor (right
        // before each test).
    }

    void TearDown() override {
        // Code here will be called immediately after each test (right
        // before the destructor).
    }

    // Class members declared here can be used by all tests in the test suite
};

TEST_F(HTTPTest, MakeServer){
    log::open("log.txt");
    HTTPServer myServ("0.0.0.0", 1231);
    myServ.addAPI("/", new Responce::File("/home/cirilla/run_directory/C++/c-rest-api/docs/test.html", ".html"), APIActions::GET);
    myServ.addAPI("/test.css", new Responce::File("/home/cirilla/run_directory/C++/c-rest-api/docs/test.css", ".css"), APIActions::GET);
    log::close();
}

}
}
}


