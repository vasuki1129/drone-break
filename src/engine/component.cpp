#include "component.h"
#include "util.h"
#include "../imgui/imgui.h"


namespace engine {

void Component::render() {}
void Component::tick(float dt) {}
void Component::init() {}
void Component::destroy() {}

json Component::Save() {
  json out;
  out["name"] = this->name;
  out["uid"] = this->name;
  return out;
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
Component::Component(json value) {
  name = value["name"];
  uid = value["uid"];
}

}
