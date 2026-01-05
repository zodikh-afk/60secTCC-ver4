#pragma once
#include "IConsumptionStrategy.h"

class EconomyConsumptionStrategy : public IConsumptionStrategy {
public:
    void Consume(Player& player) override;
};
