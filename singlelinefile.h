#ifndef SINGLELINEFILE_H
#define SINGLELINEFILE_H

#include "file.h"

class SingleLineFile : public File {
public:
    SingleLineFile(const std::string& name);
    virtual ~SingleLineFile();

    void edit() override;  // переопределяем
};

#endif