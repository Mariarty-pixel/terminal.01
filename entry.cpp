#include "entry.h"

Entry::Entry(const std::string& name) : name(name), hidden(false) {
}

Entry::~Entry() {
}

std::string Entry::getName() const {
    return name;
}

void Entry::setName(const std::string& newName) {
    name = newName;
}

bool Entry::isHidden() const {
    return hidden;
}

void Entry::hide() {
    hidden = true;
}

void Entry::reveal() {
    hidden = false;
}