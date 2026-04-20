#include "menu_shipcontroller.h"
#include <glm/glm.hpp>

void MenuShipController::tick(float dt) {
    timer += dt;
    this->GetOwner()->position.y = initial_position + sin(timer) * amplitude;


    //ACTUAL MENU CODE
    ImGui::Begin("MainMenu");


    if (menu_state == 0) {

        ImGui::Button("Campaign [Coming Soon]");
        if (ImGui::Button("Hotlap Mode")) {
          menu_state = 1;
        }
        if (ImGui::Button("Settings")) {
          menu_state = 2;
        }
        if (ImGui::Button("Quit")) {


        }
    } else if (menu_state == 1) {
      ImGui::Button("Loading Bay");
      if (ImGui::Button("Back")) {
          menu_state = 0;
      }

    } else if (menu_state == 2) {
    } else {menu_state = 0;}


    ImGui::End();

}

void MenuShipController::init() {
   this->initial_position = this->GetOwner()->position.y;
}

void MenuShipController::DrawWidget() {
  ImGui::InputFloat("Amplitude", &amplitude);
  ImGui::InputFloat("Speed", &speed);
}

json MenuShipController::Save() {
  json j;
  j["name"] = name;
  j["component_type"] = component_type;
  j["uid"] = uid;
  j["amplitude"] = amplitude;
  j["speed"] = speed;
  return j;
}

bool MenuShipController::Load(json value) {
  PROPERTY_LOAD(name)
  PROPERTY_LOAD(uid)
  PROPERTY_LOAD(component_type)
  PROPERTY_LOAD(amplitude)
  PROPERTY_LOAD(speed)
  return true;
}

MenuShipController::MenuShipController() {
  this->name = "MenuShipController";
  this->component_type = "MenuShipController";
  timer = 0.0f;
}

FACTORY_DEF(MenuShipController)
