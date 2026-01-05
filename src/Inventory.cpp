#include "Inventory.h"
#include <iostream>

void Inventory::addItem(std::unique_ptr<Item> item) {
    items_.push_back(std::move(item));
}

void Inventory::print() const {
    std::cout << "Inventory:\n";
    for (const auto& item : items_) {
        std::cout << "- " << item->getName() << "\n";
    }
}