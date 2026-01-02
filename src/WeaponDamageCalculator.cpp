#include "WeaponDamageCalculator.h"
#include "Weapon.h"

WeaponDamageCalculator::WeaponDamageCalculator(IRandomGenerator& rng)
    : rng(rng) 
{ }

int WeaponDamageCalculator::Calculate(const Weapon* weapon) const {
    if (!weapon) return 0;

    int baseDamage = weapon->GetDamage();

    // Випадковий множник: 80% – 120%
    int modifier = rng.GetInt(80, 120);

    return baseDamage * modifier / 100;
}