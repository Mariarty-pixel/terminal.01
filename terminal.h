#ifndef TERMINAL_H
#define TERMINAL_H

#include <string>
#include <vector>

class Directory;
class Entry;

class Terminal {
private:
    bool running;
    Directory* root;
    std::vector<Directory*> currentPath;

public:
    Terminal();
    ~Terminal();

    void run();
    void executeCommand(const std::string& command);

    void help();
    void exit();
    void ls();
    void cd(const std::string& path);
    void pwd();                          
    void cat(const std::string& filename);
    void touch(const std::string& filename);
    void touchm(const std::string& filename);
    void mkdir(const std::string& dirname);
    void rm(const std::string& name);
    void restore(const std::string& name);
    void mv(const std::string& oldName, const std::string& newName);
    void edit(const std::string& filename);

    // Вспомогательные методы
    Directory* getCurrentDirectory();
    Entry* findEntry(const std::string& name);
    std::string getCurrentPathString() const;
    void debugPath();  // для отладки (опционально)
};

#endif