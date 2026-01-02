#pragma once
#include "Food.h"
#include <string>

class Water : public Food {
public:
     Water();
     int GetSaturation() const override;
     std::wstring GetName() const override;
};

