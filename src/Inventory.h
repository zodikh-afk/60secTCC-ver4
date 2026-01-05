#pragma once
#include <vector>
#include <memory>
#include "Item.h"

class Inventory {
public:
    void addItem(std::unique_ptr<Item> item);
    void print() const;

private:
    std::vector<std::unique_ptr<Item>> items_;
};