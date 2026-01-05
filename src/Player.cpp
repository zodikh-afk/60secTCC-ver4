    #include "Player.h"
    #include <map>
    #include <sstream>
    #include <iostream>
    // --- ctor ---
    Player::Player(IDamageCalculator& damageCalculator)
        : Essence(
            100,   // HP гравця
            10,    // базовий урон
            5      // швидкість
        ),
        damageCalculator(damageCalculator),
        hunger_point(100),
        thirst_point(100),
        stamina_point(100)
    {
    }

    // --- Attack ---
    void Player::Attack(Essence& target)
    {   
        if (!currentWeapon) {
            std::cout << "Player has no weapon equipped!\n";
            return;
        }

        int damage = damageCalculator.Calculate(currentWeapon);
        target.TakeDamage(damage);
    }

    // --- PickUpItem ---
    bool Player::PickUpItem(std::unique_ptr<Item> new_item)
    {
        if (!new_item)
            return false;

        // перевірка ваги
        if (current_weight + new_item->getWeight() > MAX_WEIGHT)
            return false;

        current_weight += new_item->getWeight();
        inventory.push_back(std::move(new_item));
        return true;
    }
    void Player::ConsumeFood(int amount)
    {
        hunger_point -= amount;
        if (hunger_point < 0)
            hunger_point = 0;
    }

    void Player::ConsumeWater(int amount)
    {
        thirst_point -= amount;
        if (thirst_point < 0)
            thirst_point = 0;
    }

    // --- CountItemByName ---
    int Player::CountItemByName(const std::wstring& name) const
    {
        int count = 0;
        for (const auto& item : inventory) {
            if (item) {
                // 1. Отримуємо ім'я предмету (std::string)
                std::string itemStatsName = item->getName();
                
                // 2. Конвертуємо його у std::wstring для порівняння
                std::wstring wItemName(itemStatsName.begin(), itemStatsName.end());

                // 3. Тепер порівнюємо два wstring
                if (wItemName == name)
                    ++count;
            }
        }
        return count;
    }


    // --- GetInventoryString ---
std::wstring Player::GetInventoryString() const
{
    std::map<std::wstring, int> counts;
    std::map<std::wstring, int> single_weights;

    for (const auto& item : inventory) {
        std::wstring name(item->getName().begin(), item->getName().end());
        counts[name]++;

        if (single_weights.find(name) == single_weights.end()) {
            single_weights[name] = item->getWeight();
        }
    }

    std::wstringstream ss;
    ss << L"Інвентар (Вага: " << current_weight
       << L" / " << MAX_WEIGHT << L"):\n";

    if (inventory.empty()) {
        ss << L"Пусто";
    }
    else {
        for (const auto& pair : counts) {
            ss << L"- " << pair.first
               << L" - x" << pair.second
               << L" (" << single_weights[pair.first] << L"г)\n";
        }
    }

    return ss.str();
}



    // --- SetWeapon ---
    void Player::SetWeapon(Weapon* weapon)
    {
        // Player НЕ володіє зброєю
        currentWeapon = weapon;
    }
