#include "coin.h"
#include "player.h"
#include "custom_events.h"
#include <Rendering/PBRTexturedMaterial.hpp>

Coin::Coin() :
    m_angle(0.f),
    m_speed(360),
    m_transform(),
    m_playerPtr(nullptr)
{
}

void Coin::UserStartUp(Mona::World& world) noexcept
{
    m_transform = world.AddComponent<Mona::TransformComponent>(*this);
    m_transform->Rotate(glm::vec3(1, 0, 0), 3.14f / 2);

    auto& config = Mona::Config::GetInstance();
    auto& meshManager = Mona::MeshManager::GetInstance();
    auto& textureManager = Mona::TextureManager::GetInstance();
    auto& audioClipManager = Mona::AudioClipManager::GetInstance();

    auto mesh = meshManager.LoadMesh(config.getPathOfApplicationAsset("Coin_A.gltf"), true);
    auto material = std::static_pointer_cast<Mona::PBRTexturedMaterial>(world.CreateMaterial(Mona::MaterialType::DiffuseTextured));
    auto texture = textureManager.LoadTexture(config.getPathOfApplicationAsset("prototypebits_texture.png"));
    material->SetAlbedoTexture(texture);

    world.AddComponent<Mona::StaticMeshComponent>(*this, mesh, material);
    
    m_audioClipPtr = audioClipManager.LoadAudioClip(config.getPathOfApplicationAsset("SFX_Powerup_21.wav"));
}

void Coin::UserUpdate(Mona::World& world, float timeStep) noexcept
{
    // Rotation animation
    {
        m_angle += m_speed * timeStep;
        const glm::fquat baseOrientation = glm::angleAxis(glm::radians(90.f), glm::vec3(1.f, 0.f, 0.f));
        const glm::fquat variableRotation = glm::angleAxis(glm::radians(m_angle), glm::vec3(0.f, 1.f, 0.f));
        const glm::fquat totalRotation = baseOrientation * variableRotation;

        m_transform->SetRotation(totalRotation);
    }

    // check collision with the player
    if (m_playerPtr == nullptr)
        return;
    
    glm::vec3 coinLocation = m_transform->GetLocalTranslation();

    Player& player = *m_playerPtr;
    auto playerTransform = world.GetComponentHandle<Mona::TransformComponent>(player);
    glm::vec3 playerLocation = playerTransform->GetLocalTranslation();

    if (glm::distance(coinLocation, playerLocation) <= 1.f)
    {
        world.PlayAudioClip2D(m_audioClipPtr, 1.f, 1.f);
        world.DestroyGameObject(*this);

        // publishing a message: a coin has been collected!
        auto& eventManager = world.GetEventManager();
        Mona::CustomUserEvent customEvent;
        customEvent.eventID = CUSTOM_EVENT_COIN_COLLECTED;
        eventManager.Publish(customEvent);
    }
}

void Coin::SetLocation(const glm::vec3& newLocation)
{
    m_transform->SetTranslation(newLocation);
}

void Coin::SetPlayerPtr(Player* playerPtr)
{
    m_playerPtr = playerPtr;
}