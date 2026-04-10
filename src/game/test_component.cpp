#include "test_component.h"
#include "../engine/input.h"

TestComponent::TestComponent() :engine::Component(){
  this->name = "RotationComponent";
  this->component_type="RotationComponent";
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


bool TestComponent::Load(json value) {

  PROPERTY_LOAD(name)
  PROPERTY_LOAD(uid)
  PROPERTY_LOAD(component_type)
  return true;
}

FACTORY_DEF(TestComponent);
