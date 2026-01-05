#include "NormalConsumptionStrategy.h"
#include "Player.h"
#include "DifficultyManager.h"

void NormalConsumptionStrategy::Consume(Player& player)
{
    float k = DifficultyManager::Instance().GetDailyConsumptionMultiplier();

    int foodLoss  = static_cast<int>(10 * k);
    int waterLoss = static_cast<int>(8  * k);

    player.ConsumeFood(foodLoss);
    player.ConsumeWater(waterLoss);
}
