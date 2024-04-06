#include "FileInputException.h"

FileInputException::FileInputException(char* filename) {
    this->filename = filename;
}

char* FileInputException::getFileName() {
    return filename;
}
