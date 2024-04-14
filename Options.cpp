#include <iostream>

#include "Options.h"
#include "InvalidOptionException.h"

Options::Options() {}

void Options::setDefault() {
    // Could have use an array of bool, map of option to index and map of index to option instead.
    // However, since this is small, a vector of pair is fine.
    unordered_map<string, bool> defaultIsPresent {
        {byteFlag, true},
        {lineFlag, true},
        {wordFlag, true},
        {charFlag, false}
    };
    isPresent = defaultIsPresent;
}

Options* Options::getOptions(int argc, char** argv, bool hasFileName) {
    Options* options = new Options();
    
    bool hasOption = false;
    for (int i = 1; i < argc - (hasFileName ? 1 : 0); i++) {
        char* option = argv[i];
        
        if (options->isPresent.count(option) == 0) {
            delete options;
            throw InvalidOptionException(option);
        }
        
        options->isPresent[option] = true;
        hasOption = true;
    }

    if (!hasOption) {
        options->setDefault();
    }

    return options;
}

void Options::printOutput(FileData& fileData, bool hasFileName, char* lastParam) {
    cout << " ";
    for (auto& option: optionOrder) {
        if (!isPresent[option]) {
            continue;
        }
        
        // Will be using if else loops instead of switch statements since c++ does
        // not support string based switch statements.
        if (option == byteFlag) {
            cout << "   " << fileData.byteCount;
        } else if (option == lineFlag) {
            cout << "   " << fileData.lineCount;
        } else if (option == wordFlag) {
            cout << "   " << fileData.wordCount;
        } else if (option == charFlag) {
            cout << "   " << fileData.charCount;
        }
    }

    if (hasFileName) {
        cout << " " << lastParam;
    }
    cout << endl;
}

unordered_map<string, bool> Options::getIsPresent() {
    return isPresent;
}