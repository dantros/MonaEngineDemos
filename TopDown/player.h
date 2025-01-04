#pragma once

#include <MonaEngine.hpp>

class Player : public Mona::GameObject
{
public:
    Player();;

    void UserStartUp(Mona::World& world) noexcept;

    void UserUpdate(Mona::World& world, float timeStep) noexcept;

    glm::vec3 getLocation() const;

private:
    Mona::TransformHandle m_transform;
    float m_speed;
};