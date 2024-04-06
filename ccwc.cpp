#include "iostream"
#include "fstream"
#include "pair"
#include "string"
#include "vector"

#include "./FileInputException.cpp"

using namespace std;

struct FileData {
    long byteCount;
    long lineCount;
    long wordCount;
    long charCount;
};

FileData getFileStats(istream& file) {
    return FileData();
}

void checkOptions(int argc, char** argv) {
    for (int i = 1; i < argc - 1; i++) {
        option = argv[i];

        for (pair<char*, bool> isOptionPresent: isOptionPresent) {

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
    

    FileData fileData = getFileStats(*input);

    if (hasFileName) {
        fileInput.close();
    }

    return 0;
}
