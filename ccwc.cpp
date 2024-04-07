#include <iostream>
#include <fstream>
#include <utility>
#include <string>
#include <vector>

#include "FileInputException.cpp"
#include "InvalidOptionException.cpp"

using namespace std;

// Could have use an array of bool, map of option to index and map of index to option instead.
// However, since this is small, a vector of pair is fine.
vector<pair<string, bool> > isOptionsPresent;
//  {
//     {"-c", false},
//     {"-l", false},
//     {"-w", false},
//     {"-m", false}
// }

struct FileData {
    long byteCount;
    long lineCount;
    long wordCount;
    long charCount;
};

void processWordAndCharCountInLine(string& line, FileData& fileData) {
    bool inWord = false;
    for (int i = 0; i < line.length(); i++) {
        fileData.byteCount += sizeof(line[i]);
        if (!isspace(line[i])) {
            inWord = true;
            continue;
        }

        if (inWord) {
            inWord = false;
            fileData.wordCount++;
        }
    }
    if (inWord) {
        fileData.wordCount++;
    }
}

FileData getFileStats(istream& file) {
    FileData fileData;

    string line = "";
    while (getline(file, line)) {
        fileData.lineCount++;
        fileData.charCount += line.length();
        fileData.byteCount += 1; // for new line character
        processWordAndCharCountInLine(line, fileData);
    }

    return fileData;
}

istream* getIstream(ifstream* fileInput, bool hasFileName, char* lastParam) {
    if (!hasFileName) {
        return &cin;
    }

    fileInput->open(lastParam);
    if (!fileInput->is_open()) {
        throw FileInputException(lastParam);
    }
    return fileInput;
}

void checkOptions(int argc, char** argv, bool hasFileName) {
    for (int i = 1; i < argc - (hasFileName ? 1 : 0); i++) {
        char* option = argv[i];
        bool isOptionFound = false;

        for (int j = 0; j < isOptionsPresent.size(); j++) {
            pair<string, bool> isOptionPresent = isOptionsPresent[j];
            if (isOptionPresent.first != option) {
                continue;
            }

            isOptionPresent.second = true;
            isOptionFound = true;
            break;
        }

        if (!isOptionFound) {
            throw InvalidOptionException(option);
        }
    }
}

int main(int argc, char** argv) {
    bool hasFileName = argc > 1 && argv[argc - 1][0] != '-';
    ifstream fileInput;
    istream* input;
    try {
        input = getIstream(&fileInput, hasFileName, argv[argc - 1]);
    } catch (FileInputException& e) {
        cerr << "ccwc: " << e.getFileName() <<
            ": open: No such file or directory" << endl;
        return 1;
    }
    

    try {
        checkOptions(argc, argv, hasFileName);
    } catch (InvalidOptionException& e) {
        cerr << "ccwc: illegal option -- " << e.getOption() << endl;
        return 1;
    }

    FileData fileData = getFileStats(*input);
    cout << fileData.byteCount << endl;
    cout << fileData.lineCount << endl;
    cout << fileData.wordCount << endl;
    cout << fileData.charCount << endl;

    if (hasFileName) {
        fileInput.close();
    }

    return 0;
}
