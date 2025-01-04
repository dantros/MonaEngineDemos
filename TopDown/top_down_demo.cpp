
#include <MonaEngine.hpp>
#include "level_progression.h"
#include "floor.h"
#include "player.h"
#include "top_down_camera.h"
#include "high_level_game.h"

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