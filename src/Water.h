#pragma once
#include "Food.h"
#include <string>

class Water : public Food {
public:
     Water();
     std::string getName() const override;
};

