#pragma once
#include "Weapon.h"

class Pistol : public Weapon {
public:
    Pistol() {
        name = "Pistol";
        weight = 1200;
        damage = 15;
    }

    std::string SpecialEffect() const override {
        return "None";
    }
};
