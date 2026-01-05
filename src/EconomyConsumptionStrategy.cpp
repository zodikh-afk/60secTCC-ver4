#include "EconomyConsumptionStrategy.h"
#include "Player.h"
#include "DifficultyManager.h"

void EconomyConsumptionStrategy::Consume(Player& player)
{
    float k = DifficultyManager::Instance().GetDailyConsumptionMultiplier();

    int foodLoss  = static_cast<int>(6 * k);  // менше їжі
    int waterLoss = static_cast<int>(5 * k);  // менше води

    player.ConsumeFood(foodLoss);
    player.ConsumeWater(waterLoss);

    // 💥 ціна економії
    player.ReduceStamina(5);
}
