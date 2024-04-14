#include <iostream>
#include <fstream>
#include <utility>
#include <string>
#include <vector>
#include <memory> 

#include "FileInputException.h"
#include "InvalidOptionException.h"
#include "Options.h"
#include "FileData.h"

using namespace std;


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


int main(int argc, char** argv) {
    if (argc == 1) {
        cout << "Usage:./ccwc [-c] [-l] [-w] [-m] <file name>" << endl;
        return 0;
    }
    
    unique_ptr<Options> optionsPtr(nullptr);
    bool hasFileName = argc > 1 && argv[argc - 1][0] != '-';
    try {
        optionsPtr.reset(Options::getOptions(argc, argv, hasFileName));
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
    optionsPtr->printOutput(fileData, hasFileName, argv[argc - 1]);

    if (hasFileName) {
        fileInput.close();
    }

    return 0;
}
