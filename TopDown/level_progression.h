#pragma once

#include <MonaEngine.hpp>
#include "high_level_game.h"

class Player;

class LevelProgression : public Mona::GameObject
{
public:

    void UserStartUp(Mona::World& world) noexcept override;

    void UserUpdate(Mona::World& world, float timeStep) noexcept override;

    void CollectCoin(const Mona::CustomUserEvent& event);

    void SetPlayerPtr(Player* playerPtr);

    void ConfigureNewLevel();

private:

    void GenerateRandomCoins(unsigned int numberOfCoins);

    Mona::World* m_worldPtr;
    Player* m_playerPtr;
    HighLevelGame m_status;
    Mona::SubscriptionHandle m_coinCollectedHandle;
};
