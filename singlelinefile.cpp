#include "singlelinefile.h"
#include <iostream>

SingleLineFile::SingleLineFile(const std::string& name) : File(name) {
}

SingleLineFile::~SingleLineFile() {
}

void SingleLineFile::edit() {
    std::cout << "Editing SINGLE-LINE file: " << getName() << std::endl;
    std::cout << "Enter one line of text: ";
    std::string line;
    std::getline(std::cin, line);
    setContent(line);
    std::cout << "File saved!" << std::endl;
}