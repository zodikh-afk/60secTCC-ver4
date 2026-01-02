#pragma once
#include "IItem.h"
#include <string>

class Item : public IItem {
protected:
    int weight;

public:
    virtual ~Item() = default;

    int GetWeight() const override; // Реалізація в Item.cpp

    // Тільки wstring!
    virtual std::wstring GetName() const = 0;
};