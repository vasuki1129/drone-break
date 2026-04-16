#include "test_component.h"
#include "../engine/input.h"

TestComponent::TestComponent() :engine::Component(){
  this->name = "RotationComponent";
  this->component_type="RotationComponent";
}

void TestComponent::tick(float dt) {
  this->GetOwner()->Rotate(rotation_axis,rotation_speed * dt);
}

void TestComponent::DrawWidget() {
  ImGui::InputFloat3("Axis", glm::value_ptr(this->rotation_axis));
  ImGui::InputFloat("Speed", &rotation_speed);
}

json TestComponent::Save() {
  json j;
  j["name"] = name;
  j["uid"] = uid;
  j["component_type"] = "RotationComponent";
  j["rotation_speed"] = rotation_speed;
  j["rotation_axis"][0] = rotation_axis.x;
  j["rotation_axis"][1] = rotation_axis.y;
  j["rotation_axis"][2] = rotation_axis.z;
  return j;
}


bool TestComponent::Load(json value) {

  PROPERTY_LOAD(name)
  PROPERTY_LOAD(uid)
  PROPERTY_LOAD(component_type)
  PROPERTY_LOAD(rotation_speed)
  rotation_axis.x = value["rotation_axis"][0];
  rotation_axis.y = value["rotation_axis"][1];
  rotation_axis.z = value["rotation_axis"][2];
  return true;
}

FACTORY_DEF(TestComponent);
