#pragma once
class IItem {
public:
    virtual ~IItem() = default;
    virtual int GetWeight() const = 0;
};

