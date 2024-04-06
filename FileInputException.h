#pragma once

using namespace std;

class FileInputException : public exception {
    char* filename;

public:
    FileInputException(char* filename);
    char* getFileName();
};
