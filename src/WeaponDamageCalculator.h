#pragma once
#include "IDamageCalculator.h"
#include "IRandomGenerator.h"

class Weapon; // forward declare (можна так, тоді Weapon.h не треба тут)

class WeaponDamageCalculator : public IDamageCalculator {
public:
    explicit WeaponDamageCalculator(IRandomGenerator& rng);
    int Calculate(const Weapon* weapon) const override;
private:
    IRandomGenerator& rng;
};
