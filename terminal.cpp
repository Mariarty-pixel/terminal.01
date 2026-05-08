#include "terminal.h"
#include "directory.h"
#include "entry.h"
#include "file.h"
#include "singlelinefile.h"
#include "multilinefile.h"  
#include <iostream>
#include <string>

Terminal::Terminal() : running(true) {
    root = new Directory("/", nullptr);
    currentPath.push_back(root);
}

Terminal::~Terminal() {
}

void Terminal::run() {
    std::string input;

    std::cout << "=== Virtual Terminal ===\n";
    std::cout << "Type 'help' for commands, 'exit' to quit\n\n";

    while (running) {
        std::cout << "> ";  
        std::getline(std::cin, input);
        executeCommand(input);
    }
}

void Terminal::executeCommand(const std::string& command) {

    if (command.rfind("touchm ", 0) == 0) {
        touchm(command.substr(7));
        return;
    }

    if (command == "exit") {
        exit();
    }
    else if (command == "help") {
        help();
    }
    else if (command == "ls") {
        ls();
    }
    else if (command == "pwd") {
        pwd();
    }
    else if (command.substr(0, 3) == "cd " && command.length() > 3) {
        cd(command.substr(3));
    }
    else if (command.substr(0, 6) == "mkdir " && command.length() > 6) {
        mkdir(command.substr(6));
    }
    else if (command.substr(0, 6) == "touch " && command.length() > 6) {
        touch(command.substr(6));
    }
    else if (command.substr(0, 4) == "cat " && command.length() > 4) {
        cat(command.substr(4));
    }
    else if (command.substr(0, 3) == "rm " && command.length() > 3) {
        rm(command.substr(3));
    }
    else if (command.substr(0, 8) == "restore " && command.length() > 8) {
        restore(command.substr(8));
    }
    else if (command.substr(0, 3) == "mv " && command.length() > 3) {
        size_t space = command.find(' ', 4);
        if (space != std::string::npos) {
            mv(command.substr(3, space - 3), command.substr(space + 1));
        }
        else {
            std::cout << "Usage: mv <old_name> <new_name>\n";
        }
    }
    else if (command.substr(0, 5) == "edit " && command.length() > 5) {
        edit(command.substr(5));
    }
    else if (!command.empty()) {
        std::cout << "Unknown command: " << command << "\n";
        std::cout << "Type 'help' for available commands\n";
    }
}

void Terminal::help() {
    std::cout << "Available commands:\n";
    std::cout << "  help            - show this help\n";
    std::cout << "  exit            - exit the terminal\n";
    std::cout << "  ls              - list directory contents\n";
    std::cout << "  pwd             - show current path\n";
    std::cout << "  cd <dir>        - change directory\n";
    std::cout << "  cat <file>      - show file content\n";
    std::cout << "  touch <file>    - create empty file\n";
    std::cout << "  mkdir <dir>     - create directory\n";
    std::cout << "  rm <name>       - hide file/directory\n";
    std::cout << "  restore <name>  - restore hidden entry\n";
    std::cout << "  mv <old> <new>  - rename entry\n";
    std::cout << "  edit <file>     - edit file content\n";
    std::cout << "  pwd             - show current path\n";
}

void Terminal::exit() {
    std::cout << "Goodbye!\n";
    running = false;
}

void Terminal::ls() {
    getCurrentDirectory()->list();
}

void Terminal::cd(const std::string& path) {
    if (path.empty()) {
        return;
    }

    // Обработка абсолютного пути (начинается с /)
    if (path[0] == '/') {
        // Возвращаемся в корень
        while (currentPath.size() > 1) {
            currentPath.pop_back();
        }
        // Разбираем путь без первого слеша
        std::string rest = path.substr(1);
        if (!rest.empty()) {
            cd(rest);  // рекурсивно обрабатываем остаток
        }
        return;
    }

    // Разбираем путь по слэшам
    std::string current;
    size_t pos = 0;
    size_t next = path.find('/');

    while (next != std::string::npos) {
        current = path.substr(pos, next - pos);

        if (current == "..") {
            if (currentPath.size() > 1) {
                currentPath.pop_back();
            }
        }
        else if (current != "." && !current.empty()) {
            Entry* entry = findEntry(current);
            if (entry == nullptr) {
                std::cout << "Directory not found: " << current << std::endl;
                return;
            }
            Directory* dir = dynamic_cast<Directory*>(entry);
            if (dir != nullptr) {
                currentPath.push_back(dir);
            }
            else {
                std::cout << "Not a directory: " << current << std::endl;
                return;
            }
        }

        pos = next + 1;
        next = path.find('/', pos);
    }

    // Обрабатываем последнюю часть пути
    current = path.substr(pos);
    if (current == "..") {
        if (currentPath.size() > 1) {
            currentPath.pop_back();
        }
        else {
            std::cout << "Already at root directory\n";
        }
    }
    else if (current != "." && !current.empty()) {
        Entry* entry = findEntry(current);
        if (entry == nullptr) {
            std::cout << "Directory not found: " << current << std::endl;
            return;
        }
        Directory* dir = dynamic_cast<Directory*>(entry);
        if (dir != nullptr) {
            currentPath.push_back(dir);
        }
        else {
            std::cout << "Not a directory: " << current << std::endl;
        }
    }
}

void Terminal::cat(const std::string& filename) {
    Entry* entry = findEntry(filename);
    if (entry == nullptr) {
        std::cout << "File not found: " << filename << std::endl;
        return;
    }

    if (entry->isFile()) {
        entry->showContent();
    }
    else {
        std::cout << "Cannot cat a directory: " << filename << std::endl;
    }
}

void Terminal::touch(const std::string& filename) {
    if (findEntry(filename) != nullptr) {
        std::cout << "Entry already exists: " << filename << std::endl;
        return;
    }

    
    SingleLineFile* newFile = new SingleLineFile(filename);
    getCurrentDirectory()->addChild(newFile);
    std::cout << "Created file: " << filename << std::endl;
}

void Terminal::touchm(const std::string& filename) {
    if (findEntry(filename) != nullptr) {
        std::cout << "Entry already exists: " << filename << std::endl;
        return;
    }

    MultiLineFile* newFile = new MultiLineFile(filename);
    getCurrentDirectory()->addChild(newFile);
    std::cout << "Created MULTI-LINE file: " << filename << std::endl;
}

void Terminal::rm(const std::string& name) {
    Entry* entry = findEntry(name);
    if (entry == nullptr) {
        std::cout << "Entry not found: " << name << std::endl;
        return;
    }

    entry->hide();
    std::cout << "Hidden: " << name << std::endl;
}

void Terminal::restore(const std::string& name) {
    // Ищем среди ВСЕХ детей (включая скрытых) - пока упростим
    Entry* entry = findEntry(name);
    if (entry == nullptr) {
        std::cout << "Entry not found: " << name << std::endl;
        return;
    }

    entry->reveal();
    std::cout << "Restored: " << name << std::endl;
}

void Terminal::mv(const std::string& oldName, const std::string& newName) {
    Entry* entry = findEntry(oldName);
    if (entry == nullptr) {
        std::cout << "Entry not found: " << oldName << std::endl;
        return;
    }

    if (findEntry(newName) != nullptr) {
        std::cout << "Entry already exists: " << newName << std::endl;
        return;
    }

    entry->setName(newName);
    std::cout << "Renamed: " << oldName << " -> " << newName << std::endl;
}

void Terminal::edit(const std::string& filename) {
    Entry* entry = findEntry(filename);
    if (entry == nullptr) {
        std::cout << "File not found: " << filename << std::endl;
        return;
    }

    if (entry->isFile()) {
        entry->changeContent();
    }
    else {
        std::cout << "Cannot edit a directory: " << filename << std::endl;
    }
}

void Terminal::mkdir(const std::string& dirname) {
    if (findEntry(dirname) != nullptr) {
        std::cout << "Entry already exists: " << dirname << std::endl;
        return;
    }

    Directory* newDir = new Directory(dirname, getCurrentDirectory());
    getCurrentDirectory()->addChild(newDir);
    std::cout << "Created directory: " << dirname << std::endl;
}

void Terminal::pwd() {
    std::string path = getCurrentPathString();
    std::cout << path << std::endl;
}

void Terminal::debugPath() {
    std::cout << "Path size: " << currentPath.size() << std::endl;
    for (size_t i = 0; i < currentPath.size(); ++i) {
        std::cout << "  [" << i << "] = " << currentPath[i]->getName() << std::endl;
    }
}

Directory* Terminal::getCurrentDirectory() {
    return currentPath.back();
}

Entry* Terminal::findEntry(const std::string& name) {
    return getCurrentDirectory()->findChild(name);
}
 
std::string Terminal::getCurrentPathString() const {
    if (currentPath.empty()) return "/";

    std::string path;
    for (size_t i = 0; i < currentPath.size(); ++i) {
        if (i == 0) {
            path = "/" + currentPath[i]->getName();
        }
        else {
            path += "/" + currentPath[i]->getName();
        }
    }
    return path;
}