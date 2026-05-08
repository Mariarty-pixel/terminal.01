#include "directory.h"
#include <iostream>

Directory::Directory(const std::string& name, Entry* parent)
    : Entry(name), parent(parent) {
}

Directory::~Directory() {
    for (Entry* child : children) {
        delete child;
    }
}

void Directory::list() const {
    std::cout << "Directory: " << getName() << std::endl;
    for (Entry* child : children) {
        if (!child->isHidden()) {
            std::cout << "  " << child->getName();
            if (child->isDirectory()) {
                std::cout << "/";
            }
            std::cout << std::endl;
        }
    }
}

void Directory::addChild(Entry* child) {
    children.push_back(child);
}

Entry* Directory::findChild(const std::string& name) const {
    for (Entry* child : children) {
        if (child->getName() == name) {
            return child;
        }
    }
    return nullptr;
}