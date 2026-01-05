#pragma once
#include <memory>
#include <string>

class Item;
class Weapon;

class IPlayer {
public:
    virtual ~IPlayer() = default;

    virtual bool PickUpItem(std::unique_ptr<Item> new_item) = 0;
    virtual std::wstring GetInventoryString() const = 0;
    virtual int CountItemByName(const std::wstring& name) const = 0;

    virtual void Attack(Essence& target) = 0;
    virtual void SetWeapon(Weapon* weapon) = 0;
};
