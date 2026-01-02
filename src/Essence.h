#pragma once
#include <iostream>

class Essence {
protected:
    int health_point;
    int basic_damage;
    int speed_point;

public:
    Essence(int health_point, int basic_damage, int speed_point)
        : health_point(health_point), basic_damage(basic_damage), speed_point(speed_point) {}

    virtual ~Essence() = default;

    virtual void Attack(Essence& target) = 0;

    virtual void TakeDamage(int dmg) {
        if (dmg < 0) dmg = 0;
        health_point -= dmg;
        if (health_point < 0) health_point = 0;
    }

    int GetHP() const { return health_point; }
};
