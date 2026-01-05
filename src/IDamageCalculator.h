#pragma once
class Weapon;

class IDamageCalculator {
public:
    virtual ~IDamageCalculator() = default;
    virtual int Calculate(const Weapon* weapon) const = 0;
};
