#include "trigger_component.h"
#include "collision_component.h"
#include "../engine/engine.h"
namespace  engine {


TriggerComponent::TriggerComponent() : CollisionComponent()
{
  this->name = "TriggerComponent";
  this->component_type = "TriggerComponent";
}


void TriggerComponent::tick(float dt)
{

}

void TriggerComponent::DrawWidget(){
  CollisionComponent::DrawWidget();
  ImGui::InputInt("Trigger Index", &trigger_id);
}


json TriggerComponent::Save() {
  json j = CollisionComponent::Save();
  j["trigger_id"] = trigger_id;
  return j;
}

bool TriggerComponent::Load(json value) {

  CollisionComponent::Load(value);
  PROPERTY_LOAD(trigger_id)
  return true;
}


void TriggerComponent::init() {
  engine::Engine()->GetPhysics()->RegisterTrigger(this);
}

void TriggerComponent::destroy() {
  Engine()->GetPhysics()->DeregisterTrigger(this);
}

FACTORY_DEF(TriggerComponent)
}
