
#include "ItemFactory.h"
#include "Food.h"
#include "Medkit.h"
#include "WeaponItem.h"
#include "Pistol.h"
#include "Shotgun.h"

ItemFactory::ItemFactory(IRandomGenerator& rng)
    : rng_(rng) {}

std::unique_ptr<Item> ItemFactory::createRandomItem() {
    int roll = rng_.GetInt(0, 99);

    if (roll < 40)
        return std::make_unique<Food>();
    if (roll < 65)
        return std::make_unique<Medkit>();
    if (roll < 85)
        return std::make_unique<WeaponItem>(std::make_unique<Pistol>());
    
    return std::make_unique<WeaponItem>(std::make_unique<Shotgun>());
}