#pragma once
#include "Difficulty.h"

class DifficultyManager {
public:
    static DifficultyManager& Instance();

    void SetDifficulty(Difficulty difficulty);
    Difficulty GetDifficulty() const;

    // 🔑 головне
    float GetDailyConsumptionMultiplier() const;

private:
    DifficultyManager() = default;

    Difficulty currentDifficulty = Difficulty::Normal;

    // заборона копіювання
    DifficultyManager(const DifficultyManager&) = delete;
    DifficultyManager& operator=(const DifficultyManager&) = delete;
};
