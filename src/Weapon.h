#pragma once
#include "Item.h"
#include <string>

class Weapon : public Item {
protected:
    int damage = 0;

public:
    virtual ~Weapon() = default;

    int GetDamage() const;
    virtual std::string SpecialEffect() const = 0;
};

