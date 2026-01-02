#pragma once
#include "Item.h"

class Food : public Item {
protected:
    int saturation = 0;
public:
    virtual int GetSaturation() const = 0;
};
