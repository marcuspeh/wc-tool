#pragma once

#include <unordered_map>
#include <vector>
#include <string>

#include "FileData.h"

using namespace std;

class Options {
private:
    string byteFlag = "-c";
    string lineFlag = "-l";
    string wordFlag = "-w";
    string charFlag = "-m";

    unordered_map<string, bool> isPresent {
        {byteFlag, false},
        {lineFlag, false},
        {wordFlag, false},
        {charFlag, false}
    };
    vector<string> optionOrder {
        lineFlag, wordFlag,  byteFlag, charFlag
    };

    Options();
    void setDefault();
public:
    static Options* getOptions(int argc, char** argv, bool hasFileName);
    void printOutput(FileData& fileData, bool hasFileName, char* lastParam);
    unordered_map<string, bool> getIsPresent();
};
