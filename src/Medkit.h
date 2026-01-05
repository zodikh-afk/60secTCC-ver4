#pragma once
#include "Item.h"

class Medkit : public Item {
public:
    std::string getName() const override {
        return "Medkit";
    }
};