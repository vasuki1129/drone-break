#include "component.h"
#include "util.h"
#include "../imgui/imgui.h"

namespace engine {

void Component::render() {}
void Component::tick(float dt) {}
void Component::init() {}
void Component::destroy() {}

uint64_t Component::GetUID() {
  return uid;
}

Transform *Component::GetOwner() {
  return owner;
}

std::string Component::GetName() {
  return name;
}

void Component::SetOwner(Transform *own) {
  this->owner = own;
}

Component::~Component() {

}

json Component::Save() {
  json out;
  out["name"] = this->name.c_str();
  out["uid"] = this->uid;
  out["component_type"] = this->component_type;
  return out;
}

Component::Component(std::string name){

  this->name = name;
  this->uid = GenerateUID();

}

void Component::ComponentDisplay() {
  ImGui::BeginGroup();
  ImGui::Text("%s",this->name.c_str());
  ImGui::EndGroup();
}

Component::Component() {
  name = "Component";
  uid = GenerateUID();
}

}
