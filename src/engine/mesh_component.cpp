#include "mesh_component.h"
#include "engine.h"
namespace engine {

void MeshComponent::SetMesh(Mesh *mesh) {
  this->mesh = mesh;
}
void MeshComponent::SetMaterial(Material *mat) {
  this->material = mat;
}

void MeshComponent::render() {
  if (this->material == nullptr || this->mesh == nullptr) {
    std::cout << "MeshComponent missing required data\n";
    return;
  }
  BaseUniforms base{
    .model = this->owner->GetModelMatrix(),
    .camera = Engine()->GetSceneLoader()->GetCurrentScene()->GetCurrentCameraMatrix(),
  };
  this->mesh->Draw(base, material);
}
void MeshComponent::init() {}
void MeshComponent::destroy() {}


MeshComponent::MeshComponent(std::string name)
: Component(name) {
  this->mesh = nullptr;
  this->material = nullptr;
}


}
