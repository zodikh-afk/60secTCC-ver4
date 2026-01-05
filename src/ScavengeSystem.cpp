#include "ScavengeSystem.h"
#include <iostream>

ScavengeSystem::ScavengeSystem(ItemFactory& factory, IRandomGenerator& rng)
    : factory_(factory), rng_(rng) {}

void ScavengeSystem::scavenge(Player& player) {
    int itemsFound = rng_.GetInt(1, 3);

    std::cout << "You went on a scavenging run and found:\n";

    for (int i = 0; i < itemsFound; ++i) {
        auto item = factory_.createRandomItem();
        std::cout << " * " << item->getName() << "\n";
        player.PickUpItem(std::move(item));

    }
}