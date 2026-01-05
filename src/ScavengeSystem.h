#pragma once
#include "ItemFactory.h"
#include "Player.h"

class ScavengeSystem {
public:
    ScavengeSystem(ItemFactory& factory, IRandomGenerator& rng);

    void scavenge(Player& player);

private:
    ItemFactory& factory_;
    IRandomGenerator& rng_;
};