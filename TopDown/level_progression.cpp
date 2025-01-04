#include "level_progression.h"
#include "custom_events.h"
#include "player.h"
#include "high_level_game.h"
#include "coin.h"
#include <random>

void LevelProgression::UserStartUp(Mona::World& world) noexcept
{
    auto& eventManager = world.GetEventManager();
    m_worldPtr = &world;
    eventManager.Subscribe(m_coinCollectedHandle, this, &LevelProgression::CollectCoin);
}

void LevelProgression::UserUpdate(Mona::World& world, float timeStep) noexcept
{
    m_status.currentTime += timeStep;
}

void LevelProgression::CollectCoin(const Mona::CustomUserEvent& event)
{
    if (event.eventID != CUSTOM_EVENT_COIN_COLLECTED)
        return;

    ++m_status.coinsCollected;

    spdlog::info("{} coins have been collected", m_status.coinsCollected);

    if (m_status.coinsCollected == m_status.levels.at(m_status.currentLevel).coins)
    {
        m_status.coinsCollected = 0;
        unsigned int levelScore = static_cast<unsigned int>(1000.f / (m_status.currentTime + .1f));
        m_status.points += levelScore;
        m_status.currentTime = 0.f;
        spdlog::info("Level {} Complete! Level Score = {}\tTotal Score = {}", (m_status.currentLevel + 1), levelScore, m_status.points);

        ++m_status.currentLevel;
        if (m_status.currentLevel < m_status.levels.size())
            ConfigureNewLevel();
        else
        {
            spdlog::info("GAME OVER!");

            // At the moment, MonaEngine does not have a cleaner way to close the app.
            exit(EXIT_SUCCESS);
        }
    }
}

void LevelProgression::SetPlayerPtr(Player* playerPtr)
{
    m_playerPtr = playerPtr;
}

void LevelProgression::ConfigureNewLevel()
{
    const HighLevelGame::Level& level = m_status.levels.at(m_status.currentLevel);
    GenerateRandomCoins(level.coins);
    spdlog::info("Starting Level {} with {} coins", m_status.currentLevel, level.coins);
}

void LevelProgression::GenerateRandomCoins(unsigned int numberOfCoins)
{
    if (m_worldPtr == nullptr)
        return;

    std::random_device dev;
    std::mt19937 rng(dev());
    std::uniform_real_distribution<> dist(-8.f, 8.f);

    for (int i = 0; i < numberOfCoins; ++i)
    {
        glm::vec3 coinLocation(dist(rng), dist(rng), 0.f);

        auto coinHandle = m_worldPtr->CreateGameObject<Coin>();
        coinHandle->SetLocation(coinLocation);

        if (m_playerPtr == nullptr)
            return;

        Player& player = *m_playerPtr;
        coinHandle->SetPlayerPtr(&player);
    }
}
