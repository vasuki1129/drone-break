#include "game_manager.h"

GameManagerComponent::GameManagerComponent() : engine::Component() {
  this->name = "GameManagerComponent";
  this->component_type = "GameManagerComponent";
}

void GameManagerComponent::tick(float dt) {

  auto ply = engine::Engine()->GetLocalPlayer();
  if(ply == nullptr)
  {
    return;
  }

  player_collider = (engine::CollisionComponent*) ply->GetOwner()->GetComponent("CollisionComponent");

  ImGui::Begin("Lap Timer");
  ImGui::Text("%f",this->lap_timer);
  ImGui::End();

  lap_timer += dt;
  sector_timer += dt;
  total_timer += dt;


  switch(current_lap_index)
  {
    case 0:
      if(engine::Engine()->GetPhysics()->CheckTrigger(player_collider, 1))
      {
        current_lap_index = 1;
        RecordSector(0);
      }
      break;
    case 1:
      if(engine::Engine()->GetPhysics()->CheckTrigger(player_collider, 2))
      {
        current_lap_index = 2;
        RecordSector(1);
      }
      break;
    case 2:
      if(engine::Engine()->GetPhysics()->CheckTrigger(player_collider, 0))
      {
        current_lap_index = 0;
        RecordSector(2);
      }
  }



}

void GameManagerComponent::RecordSector(int sector)
{


  switch(sector)
  {
    case 0:
      current_lap.s1_time = sector_timer;
      break;
    case 1:
      current_lap.s2_time = sector_timer;
      break;
    case 2:
      current_lap.s3_time = sector_timer;
      break;
  }

  if(sector == 2)
  {
    current_lap.lap_time = lap_timer;
    best_laps[current_username] = current_lap;
    current_lap = LapInfo();
    lap_timer = 0.0f;

  }
  sector_timer = 0.0f;
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
