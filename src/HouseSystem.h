#pragma once
#include <string>
#include <vector>
#include <memory>
#include "Item.h"

struct SearchSlot 
{
    std::wstring hidden_name; // wstring
    bool is_searched = false;
    std::unique_ptr<Item> item_inside;

    SearchSlot(std::wstring name, std::unique_ptr<Item> item = nullptr)
        : hidden_name(name), item_inside(std::move(item)), is_searched(false) {
    }
};

struct Furniture 
{
    std::wstring name; // wstring
    std::vector<SearchSlot> slots;
};

struct Room 
{
    std::wstring name; // wstring
    std::vector<Furniture> furniture;
};