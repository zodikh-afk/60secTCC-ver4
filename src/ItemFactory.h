#pragma once
#include <memory>
#include "Item.h"
#include "ItemType.h"
#include "IRandomGenerator.h"

class ItemFactory {
public:
    explicit ItemFactory(IRandomGenerator& rng);

    std::unique_ptr<Item> createRandomItem();

private:
    IRandomGenerator& rng_;
};