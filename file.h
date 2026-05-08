#ifndef FILE_H
#define FILE_H

#include "entry.h"
#include <string>

class File : public Entry {
protected:
    std::string content;

public:
    File(const std::string& name);
    virtual ~File();

    bool isFile() const override { return true; } 

    virtual void edit();
    virtual void showContent() const;

    std::string getContent() const;
    void setContent(const std::string& newContent);
};

#endif