#pragma once
#include "Item.h"
#include "Weapon.h"
#include <memory>

class WeaponItem : public Item {
public:
    explicit WeaponItem(std::unique_ptr<Weapon> weapon)
        : weapon_(std::move(weapon)) {}

    std::string getName() const override {
        return "Weapon: " + weapon_->getName();
    }

    Weapon* getWeapon() const {
        return weapon_.get();
    }

private:
    std::unique_ptr<Weapon> weapon_;
};  