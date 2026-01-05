#pragma once

#include "Essence.h"
#include "IPlayer.h"
#include "IDamageCalculator.h"
#include "Item.h"
#include "Weapon.h"
#include <vector>
#include <memory>
#include <string>

class Player : public Essence, public IPlayer
{
private:
    // DI – гравець НЕ створює калькулятор
    IDamageCalculator& damageCalculator;

    // Player НЕ володіє зброєю, лише використовує
    Weapon* currentWeapon = nullptr;

    // Інвентар володіє предметами
    std::vector<std::unique_ptr<Item>> inventory;

    int current_weight = 0;     

public:
    static constexpr int MAX_WEIGHT = 20000;

    int hunger_point;
    int thirst_point;
    int stamina_point;
    void ConsumeFood(int amount);
    void ConsumeWater(int amount);
    explicit Player(IDamageCalculator& damageCalculator);

    void ReduceStamina(int amount);

    // --- Бойова логіка ---
    void Attack(Essence& target) override;
    void SetWeapon(Weapon* weapon) override;

    // --- Інвентар ---
    bool PickUpItem(std::unique_ptr<Item> new_item) override;
    std::wstring GetInventoryString() const override;
    int CountItemByName(const std::wstring& name) const;


};
