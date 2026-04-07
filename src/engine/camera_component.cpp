#include "camera_component.h"
#include <glm/ext/matrix_transform.hpp>
#include "engine.h"
#include "input.h"
#include <string>
namespace engine {


EditorCameraComponent::~EditorCameraComponent()
{

}

void EditorCameraComponent::tick(float dt) {


    glm::vec2 mouse_movement = Engine()->GetInput()->MouseDelta();
    this->GetOwner()->Rotate(glm::vec3(0,1,0), mouse_movement.x * 0.01f);
    this->GetOwner()->Rotate(this->GetOwner()->Right(), mouse_movement.y * -0.01f);
}

EditorCameraComponent::EditorCameraComponent(std::string name)
    :CameraComponent(name)
{
    this->name = name;
}

EditorCameraComponent::EditorCameraComponent(json value)
    :CameraComponent(value)
{

}

void EditorCameraComponent::DrawWidget()
{

}

EditorCameraComponent::EditorCameraComponent()
{

}

glm::mat4 CameraComponent::GetCameraMatrix() {
  glm::mat4 view = glm::lookAt(this->owner->GetGlobalPosition(), this->owner->GetGlobalPosition() + this->owner->Forward(), this->owner->Up());
  glm::mat4 projection = glm::perspective(90.0f, 4.0f / 3.0f, 0.01f, 100.0f);
  return  projection * view;
}

CameraComponent::CameraComponent() {}

CameraComponent::~CameraComponent() {}

CameraComponent::CameraComponent(json val) {}

    void CameraComponent::tick(float dt) {
    }


}
