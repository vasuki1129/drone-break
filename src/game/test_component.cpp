#include "test_component.h"
#include "../engine/input.h"

TestComponent::TestComponent() :engine::Component(){
  this->name = "RotationComponent";
  this->component_type_id="RotationComponent";
}

void TestComponent::tick(float dt) {

}

void TestComponent::DrawWidget() {

}

json TestComponent::Save() {
  json j;
  j["name"] = name;
  j["uid"] = uid;
  j["component_type"] = "RotationComponent";
  return j;
}


void TestComponent::Load(json value)
{
  this->name = value["name"];
  this->uid = value["uid"];
  this->component_type_id = value["component_type"];
}

FACTORY_DEF(TestComponent);
