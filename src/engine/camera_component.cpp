#include "camera_component.h"
#include <glm/ext/matrix_transform.hpp>
#include "engine.h"
#include "input.h"
#include <glm/geometric.hpp>
#include <string>
namespace engine {


EditorCameraComponent::~EditorCameraComponent()
{

}

void EditorCameraComponent::tick(float dt) {


    glm::vec2 mouse_movement = Engine()->GetInput()->MouseDelta();
    this->GetOwner()->Rotate(glm::vec3(0,1,0), mouse_movement.x * 0.01f);
    this->GetOwner()->Rotate(this->GetOwner()->Right(), mouse_movement.y * -0.01f);


    glm::vec3 movement_input = glm::vec3(0.0,0.0,0.0);


    if(Engine()->GetInput()->KeyDown(GLFW_KEY_W))
    {
      movement_input += this->GetOwner()->Forward();
    }
    else if(Engine()->GetInput()->KeyDown(GLFW_KEY_S))
    {
      movement_input += this->GetOwner()->Forward() * -1.0f;
    }


    if(Engine()->GetInput()->KeyDown(GLFW_KEY_A))
    {
      movement_input += this->GetOwner()->Left() * -1.0f;
    }
    else if(Engine()->GetInput()->KeyDown(GLFW_KEY_D))
    {
      movement_input += this->GetOwner()->Left();
    }

    if(glm::length(movement_input) != 0) movement_input = glm::normalize(movement_input);
    this->GetOwner()->Translate(movement_input * dt * movement_speed);

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
