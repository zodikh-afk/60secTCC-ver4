#include "Player.h"
#include <map>
#include <sstream> // Для wstringstream

void Player::Attack(Essence& target) 
{
    int damage = damageCalculator.Calculate(currentWeapon);
    target.TakeDamage(damage);
}
bool Player::PickUpItem(std::unique_ptr<Item> new_item) {   
    current_weight += new_item->GetWeight();
    inventory.push_back(std::move(new_item));
    return true;
}

int Player::CountItemByName(const std::wstring& name) const {
    int count = 0;
    for (const auto& item : inventory) {
        if (item && item->GetName() == name) count++;
    }
    return count;
}

std::wstring Player::GetInventoryString() const {
    // 1. Групування (ключ - wstring)
    std::map<std::wstring, int> counts;
    std::map<std::wstring, int> single_weights;

    for (const auto& item : inventory) {
        std::wstring name = item->GetName();
        counts[name]++;

        if (single_weights.find(name) == single_weights.end()) {
            single_weights[name] = item->GetWeight();
        }
    }

    // 2. Формування широкого рядка
    std::wstringstream ss;

    ss << L"Інвентар (Вага: " << current_weight << L" / " << MAX_WEIGHT << L"):\n";

    if (inventory.empty()) 
    {
        ss << L"Пусто";
    }
    else 
    {
        for (auto const& pair : counts) {
            std::wstring name = pair.first;
            int count = pair.second;
            int weight = single_weights[name];

            // Вивід: - Тушонка - x3 (300г)
            ss << L"- " << name << L" - x" << count << L" (" << weight << L"г)\n";
        }
    }

    return ss.str();
}

void Player::SetWeapon(Weapon* weapon) 
{
    currentWeapon = weapon;
}