#pragma once
#include "Weapon.h"

class Shotgun : public Weapon {
public:
    Shotgun() {
        name = "Shotgun";
        weight = 3500;
        damage = 35;
    }

    std::string SpecialEffect() const override {
        return "Spread damage";
    }
};
