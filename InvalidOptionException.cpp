#include "InvalidOptionException.h"

InvalidOptionException::InvalidOptionException(char* option) {
    this->option = option;
}

char* InvalidOptionException::getOption() {
    return option;
}