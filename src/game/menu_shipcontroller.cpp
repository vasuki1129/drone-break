#include "menu_shipcontroller.h"
#include <glm/glm.hpp>

void MenuShipController::tick(float dt) {
    engine::Engine()->GetInput()->EnableCursor();
    timer += dt;
    this->GetOwner()->position.y = initial_position + sin(timer) * amplitude;

    //ACTUAL MENU CODE
    engine::Texture *title_text =
        engine::Engine()->GetAssetManager()->GetTextureOrNull("TitleText");
    ImGui::SetNextWindowPos(
        ImVec2(engine::Engine()->GetRenderer()->WindowWidth() - 600, 20));
    ImGui::Begin("TitleText", NULL,
                 ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoBackground |
                     ImGuiWindowFlags_NoInputs);
    ImGui::Image((ImTextureID)(intptr_t)title_text->GetTextureHandle(),
                 ImVec2(600, 300));
    ImGui::End();

    ImGui::PushStyleColor(ImGuiCol_Button, ImVec4(0.22,0.22,0.22,0.0));

    ImGui::Begin("MainMenu",NULL,ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_NoBackground);
    ImGui::SetWindowPos(ImVec2(100,100));

    if (menu_state == 0) {
        ImGui::Button("Campaign [Coming Soon]");
        if (ImGui::Button("Hotlap Mode")) {
          menu_state = 1;
        }
        //if (ImGui::Button("Settings")) {
          //menu_state = 2;
        //}
        //if (ImGui::Button("Quit")) {
        //    engine::Engine()->Stop();

        //}
    } else if (menu_state == 1) {
      if(ImGui::Button("Loading Bay"))
      {
          ImGui::OpenPopup("NicknamePrompt");
      }
      if (ImGui::Button("Back")) {
          menu_state = 0;
      }

    } else if (menu_state == 2) {

    } else {menu_state = 0;}

          static char nickname[50];

          if(ImGui::BeginPopupModal("NicknamePrompt",NULL,ImGuiWindowFlags_NoMove | ImGuiWindowFlags_AlwaysAutoResize))
          {
              ImGui::Text("Enter name for leaderboard.");
              ImGui::InputText("Nickname", nickname,50);
              if(ImGui::Button("Play")){
                engine::Engine()->GetInput()->DisableCursor();
                engine::Engine()->GetSceneLoader()->LoadScene("assets/levels/game.scn",(void*)nickname);
              }
              ImGui::EndPopup();
          }
    ImGui::End();
    ImGui::PopStyleColor(1);
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
