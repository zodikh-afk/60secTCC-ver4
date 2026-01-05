#include "DifficultyManager.h"

DifficultyManager& DifficultyManager::Instance()
{
    static DifficultyManager instance;
    return instance;
}

void DifficultyManager::SetDifficulty(Difficulty difficulty)
{
    currentDifficulty = difficulty;
}

Difficulty DifficultyManager::GetDifficulty() const
{
    return currentDifficulty;
}

float DifficultyManager::GetDailyConsumptionMultiplier() const
{
    switch (currentDifficulty) {
    case Difficulty::Easy:
        return 0.5f;
    case Difficulty::Normal:
        return 1.0f;
    case Difficulty::Hard:
        return 1.5f;
    default:
        return 1.0f;
    }
}
