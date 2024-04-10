#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "../InvalidOptionException.cpp"

using namespace std;

TEST_CASE("InvalidOptionException class") {
    SUBCASE("should be able to get option") {
        char* option = (char*)"sample option";
        InvalidOptionException exc {option};

        CHECK(exc.getOption() == option);
    }

    SUBCASE("should be an exception instance") {
        char* option = (char*)"";
        InvalidOptionException exc {option};

        CHECK(dynamic_cast<const exception*>(&exc) != nullptr);
    }
}
