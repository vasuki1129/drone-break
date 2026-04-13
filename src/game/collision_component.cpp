#include "collision_component.h"
#include "../engine/input.h"

CollisionComponent::CollisionComponent() :engine::Component(){
  this->name = "CollisionComponent";
  this->component_type="CollisionComponent";
}

void CollisionComponent::tick(float dt) {

}

void CollisionComponent::DrawWidget() {

}

json CollisionComponent::Save() {
  json j;
  j["name"] = name;
  j["uid"] = uid;
  j["component_type"] = component_type;
  j["offset"][0] = offset.x;
  j["offset"][1] = offset.y;
  j["offset"][2] = offset.z;
  j["bounds"][0] = bounds.x;
  j["bounds"][1] = bounds.y;
  j["bounds"][2] = bounds.z;

  return j;
}


bool CollisionComponent::Load(json value) {

  PROPERTY_LOAD(name)
  PROPERTY_LOAD(uid)
  PROPERTY_LOAD(component_type)
  this->offset.x = value["offset"][0];
  this->offset.y = value["offset"][1];
  this->offset.z = value["offset"][2];

  this->bounds.x = value["bounds"][0];
  this->bounds.y = value["bounds"][1];
  this->bounds.z = value["bounds"][2];

  return true;
}


glm::vec3 CollisionComponent::CheckCollision(CollisionComponent* other)
{






}











FACTORY_DEF(CollisionComponent);
