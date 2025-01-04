#pragma once

#include <MonaEngine.hpp>

class Player;

class TopDownCamera : public Mona::GameObject
{
public:
    void UserStartUp(Mona::World& world) noexcept override;

    void UserUpdate(Mona::World& world, float timeStep) noexcept override;

    void SetPlayerPtr(Player* playerPtr);

private:
    glm::vec3 m_cameraOffset;
    Player* m_playerPtr;
};
