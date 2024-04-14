#pragma once

using namespace std;

#include <exception>


class InvalidOptionException : public exception {
    char* option;

public:
    InvalidOptionException(char* option);
    char* getOption();
};
