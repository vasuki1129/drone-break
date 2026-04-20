#include "menu_bgscroller.h"
#include <glm/glm.hpp>

void MenuBackgroundScroll::tick(float dt) {
  this->GetOwner()->Translate(glm::vec3(1.0f, 0.0f, 0.0f) * dt * speed);
  if (this->GetOwner()->position.x >= x_maximum) {
      this->GetOwner()->position.x = x_minimum;
  }
}

void MenuBackgroundScroll::DrawWidget() {
  ImGui::InputFloat("X Min", &x_minimum);
  ImGui::InputFloat("X Max", &x_maximum);
  ImGui::InputFloat("Speed", &speed);
}

json MenuBackgroundScroll::Save() {
  json j;
  j["name"] = name;
  j["component_type"] = component_type;
  j["uid"] = uid;
  j["x_minimum"] = x_minimum;
  j["x_maximum"] = x_maximum;
  j["speed"] = speed;
  return j;
}

bool MenuBackgroundScroll::Load(json value) {
  PROPERTY_LOAD(name)
  PROPERTY_LOAD(uid)
  PROPERTY_LOAD(component_type)
  PROPERTY_LOAD(x_minimum)
  PROPERTY_LOAD(x_maximum)
  PROPERTY_LOAD(speed)
  return true;
}

MenuBackgroundScroll::MenuBackgroundScroll() : engine::Component() {
  this->name = "MenuBackgroundScroll";
  this->component_type = "MenuBackgroundScroll";
}

FACTORY_DEF(MenuBackgroundScroll)
