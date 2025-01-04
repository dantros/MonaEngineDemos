#pragma once

#include <MonaEngine.hpp>

class Floor : public Mona::GameObject
{
public:
    void UserStartUp(Mona::World& world) noexcept override;

    void UserUpdate(Mona::World& world, float timeStep) noexcept override;
};
