
#include "floor.h"
#include <Rendering/PBRTexturedMaterial.hpp>

void Floor::UserStartUp(Mona::World& world) noexcept
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

void Floor::UserUpdate(Mona::World& world, float timeStep) noexcept
{
}