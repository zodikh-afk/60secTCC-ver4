#pragma once

class IRandomGenerator {
public:
    virtual ~IRandomGenerator() = default;
    virtual int GetInt(int min, int max) = 0;
};
