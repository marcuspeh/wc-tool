#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "../FileInputException.cpp"

using namespace std;

TEST_CASE("FilenputException class") {
    SUBCASE("should be able to get filename") {
        char* fileName = (char*)"sample file name.txt";
        FileInputException exc {fileName};

        CHECK(exc.getFileName() == fileName);
    }

    SUBCASE("should be an exception instance") {
        char* filename = (char*)"";
        FileInputException exc {filename};

        CHECK(dynamic_cast<const exception*>(&exc) != nullptr);
    }
}