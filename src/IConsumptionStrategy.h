#pragma once
class Player;

class IConsumptionStrategy {
public:
    virtual ~IConsumptionStrategy() = default;
    virtual void Consume(Player& player) = 0;
};
