#pragma once
#include "Essence.h"
#include "IPlayer.h"     
#include <string>
#include <vector>
#include <memory>
#include "IDamageCalculator.h" 
#include "Item.h"

class Player : public Essence, public IPlayer 
{
private:
    IDamageCalculator& damageCalculator;
    Weapon* currentWeapon = nullptr;
public:
    const int MAX_WEIGHT = 20000;
    int current_weight = 0;
    std::vector<std::unique_ptr<Item>> inventory;

    int hunger_point;
    int thirst_point;
    int stamina_point;

     Player(IDamageCalculator& damageCalculator): damageCalculator(damageCalculator), Essence(10, 2, 5), hunger_point(10), thirst_point(10), stamina_point(100) {}

    void Attack(Essence& target) override;

    // --- IPlayer реалізація ---
    bool PickUpItem(std::unique_ptr<Item> new_item) override;        
    std::wstring GetInventoryString() const override;               
    int CountItemByName(const std::wstring& name) const override; 
    void SetWeapon(Weapon* weapon) override;
};
