#pragma once
#include "IRandomGenerator.h"

class RandomGenerator : public IRandomGenerator {
public:
    int GetInt(int min, int max) override;
};
