#include "Stew.h"

Stew::Stew()
{
	weight = 300;
	saturation = 4;
}

int Stew::GetSaturation() const
{
	return saturation;
}

std::wstring Stew::GetName() const 
{
	return L"Тушонка"; // Обов'язково L
}
