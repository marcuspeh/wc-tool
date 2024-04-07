#include <iostream>
#include <fstream>
#include <utility>
#include <string>
#include <vector>

#include "FileInputException.cpp"
#include "InvalidOptionException.cpp"

using namespace std;


struct FileData {
    long byteCount;
    long lineCount;
    long wordCount;
    long charCount;
};

void processWordAndByteCountInLine(string& line, FileData& fileData) {
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

// Since this program supports multiple of options, we might need to read the file multiple times 
// in order to get the relevant information. As io are quite slow, I have decided to retrieve all 
// all the information at one go. 
FileData getFileStats(istream& file) {
    FileData fileData;

    string line = "";
    while (getline(file, line)) {
        fileData.lineCount++;
        fileData.charCount += line.length();
        fileData.byteCount += 1; // for new line character
        processWordAndByteCountInLine(line, fileData);
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

vector<pair<const string, bool>> getIsOptionsPresentVector(int argc, char** argv, bool hasFileName) {
    vector<pair<const string, bool>> isOptionsPresent = {
        {"-l", false},
        {"-w", false},
        {"-c", false},
        {"-m", false}
    };

    bool hasAtLeastOneOption = false;
    for (int i = 1; i < argc - (hasFileName ? 1 : 0); i++) {
        char* option = argv[i];
        bool isOptionFound = false;

        for (auto& isOptionPresent: isOptionsPresent) {
            if (isOptionPresent.first != option) {
                continue;
            }

            isOptionPresent.second = true;
            hasAtLeastOneOption = true;
            isOptionFound = true;
            break;
        }

        if (!isOptionFound) {
            throw InvalidOptionException(option);
        }
    }

    if (hasAtLeastOneOption) {
        return isOptionsPresent;
    }

    for (int i = 0; i < 3; i++) {
        isOptionsPresent[i].second = true;
    }
    return isOptionsPresent;
}

void printOutput(FileData& fileData, vector<pair<const string, bool>> isOptionsPresent, 
        bool hasFileName, char* lastParam) {
    cout << " ";
    for (auto& [option, isPresent]: isOptionsPresent) {
        if (!isPresent) {
            continue;
        }
        
        // Will be using if else loops instead of switch statements since c++ does
        // not support string based switch statements.
        if (option == "-c") {
            cout << "   " << fileData.byteCount;
        } else if (option == "-l") {
            cout << "   " << fileData.lineCount;
        } else if (option == "-w") {
            cout << "   " << fileData.wordCount;
        } else if (option == "-m") {
            cout << "   " << fileData.charCount;
        }
    }

    if (hasFileName) {
        cout << " " << lastParam;
    }
    cout << endl;
}

int main(int argc, char** argv) {
    // Could have use an array of bool, map of option to index and map of index to option instead.
    // However, since this is small, a vector of pair is fine.
    vector<pair<const string, bool>> isOptionsPresent;
    bool hasFileName = argc > 1 && argv[argc - 1][0] != '-';
    try {
        isOptionsPresent = getIsOptionsPresentVector(argc, argv, hasFileName);
    } catch (InvalidOptionException& e) {
        cerr << "ccwc: illegal option -- " << e.getOption() << endl;
        return 1;
    }    
    
    ifstream fileInput;
    istream* input;
    try {
        input = getIstream(&fileInput, hasFileName, argv[argc - 1]);
    } catch (FileInputException& e) {
        cerr << "ccwc: " << e.getFileName() <<
            ": open: No such file or directory" << endl;
        return 1;
    }

    FileData fileData = getFileStats(*input);
    printOutput(fileData, isOptionsPresent, hasFileName, argv[argc - 1]);

    if (hasFileName) {
        fileInput.close();
    }

    return 0;
}
