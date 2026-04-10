#include "camera_component.h"
#include <glm/ext/matrix_transform.hpp>
#include "engine.h"
#include "input.h"
#include <glm/geometric.hpp>
#include <glm/gtc/matrix_inverse.hpp>
#include <string>
namespace engine {

FACTORY_DEF(EditorCameraComponent);

json EditorCameraComponent::Save()
{
  json value = CameraComponent::Save();
  PROPERTY_SAVE(movement_speed)
  return value;
}

bool EditorCameraComponent::Load(json value)
{
  if(!CameraComponent::Load(value)) return false;
  PROPERTY_LOAD(movement_speed)
  return true;
}

EditorCameraComponent::~EditorCameraComponent()
{

}

void EditorCameraComponent::tick(float dt) {

  if(Engine()->GetInput()->MouseButtonPressed(1))
  {
    Engine()->GetInput()->DisableCursor();
  }

  if(Engine()->GetInput()->MouseButtonReleased(1))
  {
    Engine()->GetInput()->EnableCursor();
  }

    if(Engine()->GetInput()->MouseButtonDown(1))
    {
      glm::vec2 mouse_movement = Engine()->GetInput()->MouseDelta();
      this->GetOwner()->Rotate(glm::vec3(0, 1, 0), mouse_movement.x * 0.01f);
      this->GetOwner()->Rotate(this->GetOwner()->Right(),
                               mouse_movement.y * -0.01f);

      glm::vec3 movement_input = glm::vec3(0.0, 0.0, 0.0);

      if (Engine()->GetInput()->KeyDown(GLFW_KEY_W)) {
        movement_input += this->GetOwner()->Forward();
      } else if (Engine()->GetInput()->KeyDown(GLFW_KEY_S)) {
        movement_input += this->GetOwner()->Forward() * -1.0f;
      }

      if (Engine()->GetInput()->KeyDown(GLFW_KEY_A)) {
        movement_input += this->GetOwner()->Left() * -1.0f;
      } else if (Engine()->GetInput()->KeyDown(GLFW_KEY_D)) {
        movement_input += this->GetOwner()->Left();
      }

      if (glm::length(movement_input) != 0)
        movement_input = glm::normalize(movement_input);
      this->GetOwner()->Translate(movement_input * dt * movement_speed);
    }
}

EditorCameraComponent::EditorCameraComponent(std::string name)
    :CameraComponent(name)
{
    this->name = name;
    this->component_type = "EditorCameraComponent";
}


void EditorCameraComponent::DrawWidget()
{

}

EditorCameraComponent::EditorCameraComponent()
  :CameraComponent()
{
  this->component_type = "EditorCameraComponent";
}

glm::mat4 CameraComponent::GetCameraMatrix() {
  glm::mat4 view = glm::lookAt(this->owner->GetGlobalPosition(), this->owner->GetGlobalPosition() + this->owner->Forward(), this->owner->Up());
  glm::mat4 projection = glm::perspective(glm::radians(90.0f),(float)Engine()->GetRenderer()->WindowWidth()/(float)Engine()->GetRenderer()->WindowHeight(), 0.01f, 100.0f);
  return  projection * view;
}

bool CameraComponent::Load(json value)
{
  PROPERTY_LOAD(name)
  PROPERTY_LOAD(uid)
  PROPERTY_LOAD(component_type)
  return true;
}

json CameraComponent::Save()
{
  json j;
  j["name"] = name;
  j["uid"] = uid;
  j["component_type"] = component_type;
  return j;
}

CameraComponent::CameraComponent() :Component() {}

CameraComponent::CameraComponent(std::string name) : Component(name) {

}
CameraComponent::~CameraComponent() {}

void CameraComponent::tick(float dt) {
}

Ray CameraComponent::ScreenPointToRay(glm::vec2 screen_point)
{
  glm::vec2 device_coords = glm::vec2(
                                      ((2.0f * screen_point.x)/Engine()->GetRenderer()->WindowWidth())-1.0,
                                      (1.0f-(2.0f * screen_point.y)/Engine()->GetRenderer()->WindowHeight()));
  glm::vec4 near = glm::vec4(device_coords.x,device_coords.y,-1.0,1.0);
  glm::vec4 far = glm::vec4(device_coords.x,device_coords.y,1.0,1.0);
  glm::vec4 near_p = glm::inverse(GetCameraMatrix()) * near;
  glm::vec4 far_p = glm::inverse(GetCameraMatrix()) * far;
  glm::vec3 near_f = glm::vec3(near_p.x/near_p.w,near_p.y/near_p.w,near_p.z/near_p.w);
  glm::vec3 far_f = glm::vec3(far_p.x/far_p.w,far_p.y/far_p.w,far_p.z/far_p.w);

  glm::vec3 dir = far_f - near_f;
  glm::vec3 dir_norm = glm::normalize(dir);
  return Ray{near_f,dir_norm};
}



}
