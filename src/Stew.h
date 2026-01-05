#pragma once
#include "Food.h"
#include "Item.h"   
#include <string>
#include <iostream>

class Stew : public Food {
public:
    Stew();
    std::string getName() const override;
};
