#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN

#include <iostream>
#include <sstream>

#include "doctest.h"
#include "../Options.cpp"

using namespace std;



TEST_CASE("printOutput method") {
    SUBCASE("getOptions - should be able to parse 1 option without filename") {
        // Input
        int argc = 2;
        char *argv[] = {(char*)"./test", (char*)"-c"};
        bool hasFileName = false;

        Options* options = Options::getOptions(argc, argv, hasFileName);
        CHECK(options->getIsPresent().size() == 4);
        CHECK(options->getIsPresent()["-c"]);
        CHECK_FALSE(options->getIsPresent()["-l"]);
        CHECK_FALSE(options->getIsPresent()["-w"]);
        CHECK_FALSE(options->getIsPresent()["-m"]);
        delete options;
    }

    SUBCASE("getOptions - should be able to parse 1 option with filename") {
        // Input
        int argc = 3;
        char *argv[] = {(char*)"./test", (char*)"-l", (char*)"./test"};
        bool hasFileName = true;

        Options* options = Options::getOptions(argc, argv, hasFileName);
        CHECK(options->getIsPresent().size() == 4);
        CHECK_FALSE(options->getIsPresent()["-c"]);
        CHECK(options->getIsPresent()["-l"]);
        CHECK_FALSE(options->getIsPresent()["-w"]);
        CHECK_FALSE(options->getIsPresent()["-m"]);
        delete options;
    }

    SUBCASE("getOptions - should be able to parse multiple options") {
        // Input
        int argc = 4;
        char *argv[] = {(char*)"./test", (char*)"-l", (char*)"-m", (char*)"-w"};
        bool hasFileName = false;

        Options* options = Options::getOptions(argc, argv, hasFileName);
        CHECK(options->getIsPresent().size() == 4);
        CHECK_FALSE(options->getIsPresent()["-c"]);
        CHECK(options->getIsPresent()["-l"]);
        CHECK(options->getIsPresent()["-w"]);
        CHECK(options->getIsPresent()["-m"]);
        delete options;
    }

    SUBCASE("getOptions - should return default values with file name") {
        // Input
        int argc = 2;
        char *argv[] = {(char*)"./test", (char*)"./test"};
        bool hasFileName = true;

        Options* options = Options::getOptions(argc, argv, hasFileName);
        CHECK(options->getIsPresent().size() == 4);
        CHECK(options->getIsPresent()["-c"]);
        CHECK(options->getIsPresent()["-l"]);
        CHECK(options->getIsPresent()["-w"]);
        CHECK_FALSE(options->getIsPresent()["-m"]);
        delete options;
    }

    SUBCASE("getOptions - should return default values without file name") {
        // Input
        int argc = 1;
        char *argv[] = {(char*)"./test"};
        bool hasFileName = false;

        Options* options = Options::getOptions(argc, argv, hasFileName);
        CHECK(options->getIsPresent().size() == 4);
        CHECK(options->getIsPresent()["-c"]);
        CHECK(options->getIsPresent()["-l"]);
        CHECK(options->getIsPresent()["-w"]);
        CHECK_FALSE(options->getIsPresent()["-m"]);
        delete options;
    }

    SUBCASE("getOptions - throws error with invalid options") {
        // Input
        int argc = 2;
        char *argv[] = {(char*)"./test", (char*)"-o"};
        bool hasFileName = false;

        try {
            Options::getOptions(argc, argv, hasFileName);
            CHECK(false);
        } catch (InvalidOptionException& e) {
            CHECK(e.getOption() == (char*)"-o");
        } catch (exception& e) {
            CHECK(false);
        } 
    }

    SUBCASE("should print default values with file name") {
        // Replace cout
        ostringstream oss;
        streambuf* p_cout_streambuf = cout.rdbuf();
        cout.rdbuf(oss.rdbuf());

        int argc = 2;
        char *argv[] = {(char*)"./test", (char*)"./test"};
        bool hasFileName = true;
        FileData fileData; 
        fileData.byteCount = 123;
        fileData.lineCount = 124;
        fileData.wordCount = 125;
        fileData.charCount = 126;

        Options* options = Options::getOptions(argc, argv, hasFileName);
        options->printOutput(fileData, hasFileName, argv[1]);

        // Restore cout
        cout.rdbuf(p_cout_streambuf);

        // test your oss content...
        CHECK(oss.str() == "    124   125   123 ./test\n");
    }

     SUBCASE("should print default values without file name") {
        // Replace cout
        ostringstream oss;
        streambuf* p_cout_streambuf = cout.rdbuf();
        cout.rdbuf(oss.rdbuf());

        int argc = 1;
        char *argv[] = {(char*)"./test"};
        bool hasFileName = false;
        FileData fileData; 
        fileData.byteCount = 123;
        fileData.lineCount = 124;
        fileData.wordCount = 125;
        fileData.charCount = 126;

        Options* options = Options::getOptions(argc, argv, hasFileName);
        options->printOutput(fileData, hasFileName, argv[0]);

        // Restore cout
        cout.rdbuf(p_cout_streambuf);

        // test your oss content...
        CHECK(oss.str() == "    124   125   123\n");
    }
}