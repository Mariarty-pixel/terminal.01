#include "file.h"
#include <iostream>

File::File(const std::string& name) : Entry(name), content("") {
}

File::~File() {
}

void File::edit() {
    std::cout << "Editing file: " << getName() << std::endl;
    std::cout << "> ";
    std::getline(std::cin, content);
    std::cout << "File saved!" << std::endl;
}

void File::showContent() const {
    std::cout << "File: " << getName() << std::endl;
    std::cout << content << std::endl;
}

std::string File::getContent() const {
    return content;
}

void File::setContent(const std::string& newContent) {
    content = newContent;
}