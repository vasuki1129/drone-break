#include "player_component.h"
#include "../engine/input.h"

PlayerComponent::PlayerComponent() :engine::Component(){
  this->name = "PlayerComponent";
  this->component_type="PlayerComponent";
}

void PlayerComponent::tick(float dt) {

  this->GetOwner()->Translate(velocity * dt);

  if(Engine()->GetInput()->)




}

void PlayerComponent::DrawWidget() {

}

json PlayerComponent::Save() {
  json j;
  j["name"] = name;
  j["uid"] = uid;
  j["component_type"] = component_type;
  return j;
}


bool PlayerComponent::Load(json value) {

  PROPERTY_LOAD(name)
  PROPERTY_LOAD(uid)
  PROPERTY_LOAD(component_type)
  return true;
}

FACTORY_DEF(PlayerComponent);
