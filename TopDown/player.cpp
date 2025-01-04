#include "player.h"
#include "Rendering/PBRTexturedMaterial.hpp"

Player::Player() : m_speed(0.0f)
{
}

void Player::UserStartUp(Mona::World& world) noexcept
{
    m_transform = world.AddComponent<Mona::TransformComponent>(*this);
    m_speed = 10.0;

    auto& config = Mona::Config::GetInstance();
    auto& meshManager = Mona::MeshManager::GetInstance();
    auto& textureManager = Mona::TextureManager::GetInstance();

    auto mesh = meshManager.LoadMesh(config.getPathOfApplicationAsset("Box_C.gltf"), true);
    auto material = std::static_pointer_cast<Mona::PBRTexturedMaterial>(world.CreateMaterial(Mona::MaterialType::DiffuseTextured));
    auto texture = textureManager.LoadTexture(config.getPathOfApplicationAsset("prototypebits_texture.png"));
    material->SetAlbedoTexture(texture);

    world.AddComponent<Mona::StaticMeshComponent>(*this, mesh, material);
}

void Player::UserUpdate(Mona::World& world, float timeStep) noexcept
{
    auto& input = world.GetInput();
    if (input.IsKeyPressed(MONA_KEY_A) or
        input.IsKeyPressed(MONA_KEY_LEFT) or
        input.IsGamepadButtonPressed(MONA_JOYSTICK_1, MONA_GAMEPAD_BUTTON_DPAD_LEFT) or
        input.GetGamepadAxisValue(MONA_JOYSTICK_1, MONA_GAMEPAD_AXIS_LEFT_X) < -0.25f)
    {
        m_transform->Translate(glm::vec3(-m_speed * timeStep, 0.0f, 0.0f));
    }
    else if (input.IsKeyPressed(MONA_KEY_D) or
        input.IsKeyPressed(MONA_KEY_RIGHT) or
        input.IsGamepadButtonPressed(MONA_JOYSTICK_1, MONA_GAMEPAD_BUTTON_DPAD_RIGHT) or
        input.GetGamepadAxisValue(MONA_JOYSTICK_1, MONA_GAMEPAD_AXIS_LEFT_X) > 0.25f)
    {
        m_transform->Translate(glm::vec3(m_speed * timeStep, 0.0f, 0.0f));
    }
    else if (input.IsKeyPressed(MONA_KEY_W) or
        input.IsKeyPressed(MONA_KEY_UP) or
        input.IsGamepadButtonPressed(MONA_JOYSTICK_1, MONA_GAMEPAD_BUTTON_DPAD_UP) or
        input.GetGamepadAxisValue(MONA_JOYSTICK_1, MONA_GAMEPAD_AXIS_LEFT_Y) < -0.25f)
    {
        m_transform->Translate(glm::vec3(0.0f, m_speed * timeStep, 0.0f));
    }
    else if (input.IsKeyPressed(MONA_KEY_S) or
        input.IsKeyPressed(MONA_KEY_DOWN) or
        input.IsGamepadButtonPressed(MONA_JOYSTICK_1, MONA_GAMEPAD_BUTTON_DPAD_DOWN) or
        input.GetGamepadAxisValue(MONA_JOYSTICK_1, MONA_GAMEPAD_AXIS_LEFT_Y) > 0.25f)
    {
        m_transform->Translate(glm::vec3(0.0f, -m_speed * timeStep, 0.0f));
    }
    else if (input.IsKeyPressed(MONA_KEY_SPACE) or
        input.IsKeyPressed(MONA_KEY_LEFT_CONTROL) or
        input.IsGamepadButtonPressed(MONA_JOYSTICK_1, MONA_GAMEPAD_BUTTON_A))
    {
        spdlog::info("shooting!");
    }
}

glm::vec3 Player::getLocation() const
{
    return m_transform->GetLocalTranslation();
}