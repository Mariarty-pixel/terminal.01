#ifndef MULTILINEFILE_H
#define MULTILINEFILE_H

#include "file.h"

class MultiLineFile : public File {
public:
    MultiLineFile(const std::string& name);
    virtual ~MultiLineFile();

    void edit() override;  // переопределяем
    void showContent() const override;  // переопределяем для красивого вывода
};

#endif