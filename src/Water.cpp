#include "Water.h"

Water::Water() {
    weight = 500;
    saturation = 2;
}

int Water::GetSaturation() const {
    return saturation;
}

std::wstring Water::GetName() const {
    return L"Вода";
}