
#include <MonaEngine.hpp>

class TopDownDemo : public Mona::Application
{
public:
    void UserStartUp(Mona::World & world) noexcept override
    {

    }

    void UserShutDown(Mona::World& world) noexcept override
    {

    }

    void UserUpdate(Mona::World & world, float timeStep) noexcept override
    {
        
    }
};

int main()
{
    TopDownDemo app;
    Mona::Engine engine(app);
    engine.StartMainLoop();
}