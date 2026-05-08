#include "multilinefile.h"
#include <iostream>
#include <sstream>
#include <vector>

MultiLineFile::MultiLineFile(const std::string& name) : File(name) {
}

MultiLineFile::~MultiLineFile() {
}

void MultiLineFile::edit() {
    std::cout << "Editing MULTI-LINE file: " << getName() << std::endl;
    std::cout << "Enter lines of text. Empty line finishes:" << std::endl;

    std::vector<std::string> lines;
    std::string line;
    int lineNum = 1;

    while (true) {
        std::cout << lineNum << "> ";
        std::getline(std::cin, line);
        if (line.empty()) break;
        lines.push_back(line);
        lineNum++;
    }

    // Собираем содержимое
    std::string content;
    for (const auto& l : lines) {
        content += l + "\n";
    }
    setContent(content);

    std::cout << "File saved! (" << lines.size() << " lines)" << std::endl;
}

void MultiLineFile::showContent() const {
    std::cout << "MULTI-LINE File: " << getName() << std::endl;
    std::cout << "Content:" << std::endl;

    std::string content = getContent();
    std::istringstream stream(content);
    std::string line;
    int lineNum = 1;

    while (std::getline(stream, line)) {
        std::cout << "  " << lineNum << ". " << line << std::endl;
        lineNum++;
    }
}