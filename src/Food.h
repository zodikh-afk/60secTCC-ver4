#pragma once
#include "Item.h"

class Food : public Item {
public:
    std::string getName() const override {
        return "Food";
    }
};
