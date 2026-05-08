#ifndef ENTRY_H
#define ENTRY_H

#include <string>

class Entry {
protected:
    std::string name;
    bool hidden;  // ДОБАВЬТЕ ЭТУ СТРОКУ

public:
    Entry(const std::string& name);
    virtual ~Entry();

    std::string getName() const;
    void setName(const std::string& newName);

    // Методы для работы со скрытостью
    bool isHidden() const;
    void hide();
    void reveal();

    // Методы для определения типа
    virtual bool isDirectory() const { return false; }
    virtual bool isFile() const { return false; }

    // Полиморфные методы
    virtual void list() const {}
    virtual void showContent() const {}
    virtual void changeContent() {}

    // Вспомогательные методы (будут переопределены в Directory)
    virtual void addChild(Entry* child) {}
    virtual Entry* findChild(const std::string& name) const { return nullptr; }
};

#endif