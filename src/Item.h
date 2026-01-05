#pragma once
#include <string>

class Item {
protected:
    std::string name;
    int weight = 0;

public:
    virtual ~Item() = default;
    int getWeight() const; 
    virtual std::string getName() const {
        return name;
    }// ← доступний нащадкам
};
