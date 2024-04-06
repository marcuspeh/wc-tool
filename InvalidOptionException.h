#pragma once

using namespace std;

class InvalidOptionException : public exception {
    char* option;

public:
    InvalidOptionException(char* option);
    char* getOption();
};
