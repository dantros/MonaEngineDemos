
#include <MonaEngine.hpp>
#include "Rendering/DiffuseFlatMaterial.hpp"
#include "Rendering/PBRTexturedMaterial.hpp"
#include <glm/gtx/quaternion.hpp>
#include <glm/gtx/string_cast.hpp>
#include <iostream>
#include <random>

constexpr unsigned int CUSTOM_EVENT_COIN_COLLECTED = 0;
constexpr unsigned int CUSTOM_EVENT_NEW_LEVEL = 1;

class Player : public Mona::GameObject
{
public:
    Player() : m_speed(0.0f)
    {
    }

    void UserStartUp(Mona::World& world) noexcept
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

    void UserUpdate(Mona::World& world, float timeStep) noexcept
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

    glm::vec3 getLocation() const
    {
        return m_transform->GetLocalTranslation();
    }

private:
    Mona::TransformHandle m_transform;
    float m_speed;
};

class TopDownCamera : public Mona::GameObject
{
public:
    void UserStartUp(Mona::World& world) noexcept override
    {
        m_cameraOffset = glm::vec3(0.0f, -5.0f, 20.0f);
        auto transform = world.AddComponent<Mona::TransformComponent>(*this, m_cameraOffset);
        transform->Rotate(glm::vec3(1.0f, 0.0f, 0.0f), -1.40f );
        world.SetMainCamera(world.AddComponent<Mona::CameraComponent>(*this));
    }

    void UserUpdate(Mona::World& world, float timeStep) noexcept override
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

    void SetPlayerPtr(Player* playerPtr)
    {
        m_playerPtr = playerPtr;
    }

private:
    glm::vec3 m_cameraOffset;
    Player* m_playerPtr;
};

class Floor : public Mona::GameObject
{
public:
    void UserStartUp(Mona::World& world) noexcept override
    {
        auto transform = world.AddComponent<Mona::TransformComponent>(*this);
        transform->SetTranslation(glm::vec3(0,0,-1));
        transform->SetRotation(glm::angleAxis(glm::radians(90.f), glm::vec3(1,0,0)));
        transform->SetScale(glm::vec3(4, 1, 4));

        auto& config = Mona::Config::GetInstance();
        auto& meshManager = Mona::MeshManager::GetInstance();
        auto& textureManager = Mona::TextureManager::GetInstance();

        auto mesh = meshManager.LoadMesh(config.getPathOfApplicationAsset("Floor_Prototype.gltf"), true);
        auto material = std::static_pointer_cast<Mona::PBRTexturedMaterial>(world.CreateMaterial(Mona::MaterialType::DiffuseTextured));
        auto texture = textureManager.LoadTexture(config.getPathOfApplicationAsset("prototypebits_texture.png"));
        material->SetAlbedoTexture(texture);

        world.AddComponent<Mona::StaticMeshComponent>(*this, mesh, material);
    }

    void UserUpdate(Mona::World& world, float timeStep) noexcept override {}
};

class Coin : public Mona::GameObject
{
public:
    Coin() : m_angle(0.f), m_speed(360), m_transform(), m_playerPtr(nullptr){}

    void UserStartUp(Mona::World& world) noexcept override
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

    void UserUpdate(Mona::World& world, float timeStep) noexcept override
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

    void SetLocation(const glm::vec3& newLocation)
    {
        m_transform->SetTranslation(newLocation);
    }

    void SetPlayerPtr(Player* playerPtr)
    {
        m_playerPtr = playerPtr;
    }

private:
    float m_angle;
    float m_speed;
    Mona::TransformHandle m_transform;
    Player* m_playerPtr;
    std::shared_ptr<Mona::AudioClip> m_audioClipPtr;
};

struct HighLevelGame
{
    unsigned int currentLevel = 0;
    unsigned int coinsCollected = 0;
    float currentTime = 0.f;
    unsigned int points = 0;

    struct Level
    {
        unsigned int coins;
        unsigned int monsters; // pending implementation
    };

    const std::vector<Level> levels
    {
        {10, 1},
        {5, 2},
        {10, 3},
        {20, 4},
        {30, 4},
        {5, 8},
        {3, 10},
        {50, 1}
    };
};

class LevelProgression : public Mona::GameObject
{
public:

    void UserStartUp(Mona::World& world) noexcept override
    {
        auto& eventManager = world.GetEventManager();
        m_worldPtr = &world;
        eventManager.Subscribe(m_coinCollectedHandle, this, &LevelProgression::CollectCoin);
    }

    void UserUpdate(Mona::World& world, float timeStep) noexcept override
    {
        m_status.currentTime += timeStep;
    }

    void CollectCoin(const Mona::CustomUserEvent& event)
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

    void SetPlayerPtr(Player* playerPtr)
    {
        m_playerPtr = playerPtr;
    }

    void ConfigureNewLevel()
    {
        const HighLevelGame::Level& level = m_status.levels.at(m_status.currentLevel);
        GenerateRandomCoins(level.coins);
        spdlog::info("Starting Level {} with {} coins", m_status.currentLevel, level.coins);
    }

private:

    void GenerateRandomCoins(unsigned int numberOfCoins)
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

    Mona::World* m_worldPtr;
    Player* m_playerPtr;
    HighLevelGame m_status;
    Mona::SubscriptionHandle m_coinCollectedHandle;
};

class TopDownDemo : public Mona::Application
{
public:
    void UserStartUp(Mona::World& world) noexcept override
    {
        // Setting up our Game Objects
        auto playerHandle = world.CreateGameObject<Player>();

        // We will use a reference so selected game objects can access player information
        Player& player = *playerHandle;

        world.CreateGameObject<Floor>();

        // This game object is able to spawn more game objects, amazing!
        auto levelProgressionHandle = world.CreateGameObject<LevelProgression>();
        levelProgressionHandle->SetPlayerPtr(&player);
        levelProgressionHandle->ConfigureNewLevel();

        auto cameraHandle = world.CreateGameObject<TopDownCamera>();
        cameraHandle->SetPlayerPtr(&player);

        // Setting up lighting
        auto directionalLight = world.AddComponent<Mona::DirectionalLightComponent>(cameraHandle, glm::vec3(1.0f));

        directionalLight->SetLightColor(glm::vec3(1.0f, 1.0f, 1.0f));
    }

    void UserShutDown(Mona::World& world) noexcept override
    {
        spdlog::info("Bye!");
    }

    void UserUpdate(Mona::World & world, float timeStep) noexcept override
    {
        auto& input = world.GetInput();
        auto& window = world.GetWindow();
        if (input.IsKeyPressed(MONA_KEY_ESCAPE))
        {
            //window.ShutDown();
            // At the moment, MonaEngine does not have a cleaner way to close the app.
            exit(EXIT_SUCCESS);
        }
    }
private:

};

int main()
{
    spdlog::info("Top Down Demo");
    TopDownDemo app;
    Mona::Engine engine(app);
    engine.StartMainLoop();
}