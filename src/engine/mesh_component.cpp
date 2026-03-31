#include "mesh_component.h"
#include "engine.h"
namespace engine {

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
