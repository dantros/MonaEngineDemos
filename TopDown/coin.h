#pragma once

#include <MonaEngine.hpp>

class Player;

class Coin : public Mona::GameObject
{
public:
    Coin();

    void UserStartUp(Mona::World& world) noexcept override;

    void UserUpdate(Mona::World& world, float timeStep) noexcept override;

    void SetLocation(const glm::vec3& newLocation);

    void SetPlayerPtr(Player* playerPtr);

private:
    float m_angle;
    float m_speed;
    Mona::TransformHandle m_transform;
    Player* m_playerPtr;
    std::shared_ptr<Mona::AudioClip> m_audioClipPtr;
};
