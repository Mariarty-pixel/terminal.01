#ifndef DIRECTORY_H
#define DIRECTORY_H

#include "entry.h"
#include <vector>

class Directory : public Entry {
private:
    std::vector<Entry*> children;
    Entry* parent;

public:
    Directory(const std::string& name, Entry* parent = nullptr);
    virtual ~Directory();

    bool isDirectory() const override { return true; }
    bool isFile() const override { return false; }  

    void list() const override;

    void addChild(Entry* child) override;
    Entry* findChild(const std::string& name) const override;
};

#endif