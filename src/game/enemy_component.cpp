#include "enemy_component.h"
#include "../engine/util.h"


EnemyComponent::EnemyComponent() : engine::Component() {
  this->name = "EnemyComponent";
  this->component_type="EnemyComponent";
}




float EnemyComponent::GetSpeed() {return glm::length(velocity);}





void EnemyComponent::tick(float dt) {
  Think();

  this->GetOwner()->Rotate(this->GetOwner()->Right(), current_input.y * dt);
  this->GetOwner()->Rotate(this->GetOwner()->Up(), current_input.x * dt);

  velocity += this->GetOwner()->Forward() * dt * engine_power * throttle_input;
  velocity = MoveTowards(velocity,glm::vec3(0.0,0.0,0.0),damping * dt * this->GetSpeed() * this->GetSpeed() + resistance * dt * this->GetSpeed());
}

void EnemyComponent::DrawWidget() {
  ImGui::InputFloat("Damping", &damping);
  ImGui::InputFloat("Resistance", &resistance);
  ImGui::InputFloat("Engine Power", &engine_power);
}

void EnemyComponent::Think() {
  //compute distance between us and player
  float distance = glm::distance(this->GetOwner()->position, engine::Engine()->GetLocalPlayer()->GetOwner()->position);
  if (distance < 100.0f) {
    glm::vec3 direction =
        engine::Engine()->GetLocalPlayer()->GetOwner()->position -
        this->GetOwner()->position;
    direction = glm::normalize(direction);
    this->GetOwner()->rotation = glm::slerp(this->GetOwner()->rotation,glm::quatLookAt(direction, glm::vec3(1,0,0)),engine::Engine()->GetRenderer()->DeltaTime() );
  }
}

json EnemyComponent::Save() {
  json j;
  j["name"] = name;
  j["uid"] = uid;
  j["component_type"] = component_type;
  j["damping"] = damping;
  j["resistance"] = resistance;
  j["velocity"][0] = velocity.x;
  j["velocity"][1] = velocity.y;
  j["velocity"][2] = velocity.z;
  j["engine_power"] = engine_power;
  return j;
}

bool EnemyComponent::Load(json value) {
  PROPERTY_LOAD(name)
  PROPERTY_LOAD(uid)
  PROPERTY_LOAD(component_type)
  PROPERTY_LOAD(damping)
  PROPERTY_LOAD(resistance)
  PROPERTY_LOAD(engine_power)
  return true;
}

FACTORY_DEF(EnemyComponent)
