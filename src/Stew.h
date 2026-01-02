#pragma once
#include "Food.h"
#include "Item.h"   
#include <string>
#include <iostream>

class Stew : public Food {
public:
    Stew();

    int GetSaturation() const override;
    std::wstring GetName() const override;
};
