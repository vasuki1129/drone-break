#include "mesh_component.h"
#include "engine.h"
namespace engine {

void MeshComponent::SetMesh(Mesh *mesh) {
  this->mesh = mesh;
}


void MeshComponent::render() {
  BaseUniforms base{
    .model = this->owner->GetModelMatrix(),
    .camera = Engine()->GetSceneLoader()->GetCurrentScene()->GetCurrentCameraMatrix(),
  };
  this->mesh->Draw(base, material);
}
void MeshComponent::init() {}
void MeshComponent::destroy() {}

}
