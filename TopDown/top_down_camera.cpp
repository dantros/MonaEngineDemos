#include "top_down_camera.h"
#include "player.h"

void TopDownCamera::UserStartUp(Mona::World& world) noexcept
{
    m_cameraOffset = glm::vec3(0.0f, -5.0f, 20.0f);
    auto transform = world.AddComponent<Mona::TransformComponent>(*this, m_cameraOffset);
    transform->Rotate(glm::vec3(1.0f, 0.0f, 0.0f), -1.40f );
    world.SetMainCamera(world.AddComponent<Mona::CameraComponent>(*this));
}

void TopDownCamera::UserUpdate(Mona::World& world, float timeStep) noexcept
{
    /* We are adding a dependency, camera depends on the player,
        * the camera game object should be updated after the player game object...
        * sadly, current version of MonaEngine does not allow us to specify this
        * dependency. Here we just collect the current value, which could have been
        * updated or not the current frame.
        * Worse case scenario: player information will correspond to the previous
        * frame. */
    if (m_playerPtr == nullptr)
        return;

    /* The camera remains over the player */
    Player& player = *m_playerPtr;
    auto playerTransform = world.GetComponentHandle<Mona::TransformComponent>(player);
    glm::vec3 target = playerTransform->GetLocalTranslation();
    glm::vec3 newCameraLocation = target + m_cameraOffset;

    auto cameraTransform = world.GetComponentHandle<Mona::TransformComponent>(*this);
    cameraTransform->SetTranslation(newCameraLocation);
}

void TopDownCamera::SetPlayerPtr(Player* playerPtr)
{
    m_playerPtr = playerPtr;
}