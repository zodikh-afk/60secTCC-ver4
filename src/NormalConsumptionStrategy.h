#pragma once
#include "IConsumptionStrategy.h"

class NormalConsumptionStrategy : public IConsumptionStrategy {
public:
    void Consume(Player& player) override;
};
