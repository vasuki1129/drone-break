#include "camera_component.h"
#include <glm/ext/matrix_transform.hpp>

namespace engine {


glm::mat4 CameraComponent::GetCameraMatrix() {
  glm::mat4 view = glm::lookAt(this->owner->GetGlobalPosition(), this->owner->GetGlobalPosition() + this->owner->Forward(), this->owner->Up());
  glm::mat4 projection = glm::perspective(90.0f, 4.0f / 3.0f, 0.01f, 100.0f);
  return  projection * view;
}

CameraComponent::CameraComponent() {}

CameraComponent::~CameraComponent() {}

CameraComponent::CameraComponent(json val) {}


}
