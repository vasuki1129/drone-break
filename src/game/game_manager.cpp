#include "game_manager.h"

GameManagerComponent::GameManagerComponent() : engine::Component() {
  this->name = "GameManagerComponent";
  this->component_type = "GameManagerComponent";
}

void GameManagerComponent::init() {
    engine::Engine()->GetSoundManager()->PlaySound("assets/music/drone-break_menu.mp3");
}

void GameManagerComponent::DrawWidget() {}

json GameManagerComponent::Save() {
  json j;
  j["name"] = name;
  j["uid"] = uid;
  j["component_type"] = component_type;
  return j;

}

bool GameManagerComponent::Load(json value) {
  PROPERTY_LOAD(name)
  PROPERTY_LOAD(uid)
  PROPERTY_LOAD(component_type)
  return true;
}

FACTORY_DEF(GameManagerComponent)
