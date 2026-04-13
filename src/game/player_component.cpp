#include "player_component.h"
#include "../engine/input.h"

PlayerComponent::PlayerComponent() :engine::Component(){
  this->name = "PlayerComponent";
  this->component_type="PlayerComponent";
}

void PlayerComponent::tick(float dt) {

  glm::vec2 mouse_delta = engine::Engine()->GetInput()->MouseDelta();

  this->GetOwner()->Rotate(this->GetOwner()->Right(), mouse_delta.y * dt);
  this->GetOwner()->Rotate(this->GetOwner()->Up(), mouse_delta.x * dt);



  if(engine::Engine()->GetInput()->KeyDown(GLFW_KEY_Q))
  {
    this->GetOwner()->Rotate(this->GetOwner()->Forward(), dt);
  }

  if(engine::Engine()->GetInput()->KeyDown(GLFW_KEY_E))
  {
    this->GetOwner()->Rotate(this->GetOwner()->Forward(), -dt);
  }

  this->GetOwner()->Translate(velocity * dt);

  if(engine::Engine()->GetInput()->KeyDown(GLFW_KEY_SPACE))
  {
    velocity += this->GetOwner()->Forward() * dt * 4.0f;
  }
  else
  {

  }

  velocity = glm::mix(velocity,glm::vec3(0.0,0.0,0.0),damping * dt);
}

void PlayerComponent::DrawWidget() {

}

json PlayerComponent::Save() {
  json j;
  j["name"] = name;
  j["uid"] = uid;
  j["component_type"] = component_type;
  j["damping"] = damping;
  j["velocity"][0] = velocity.x;
  j["velocity"][1] = velocity.y;
  j["velocity"][2] = velocity.z;
  return j;
}


bool PlayerComponent::Load(json value) {

  PROPERTY_LOAD(name)
  PROPERTY_LOAD(uid)
  PROPERTY_LOAD(component_type)
  PROPERTY_LOAD(damping)
  return true;
}

FACTORY_DEF(PlayerComponent);
