#include "game_manager.h"
#include <fstream>
GameManagerComponent::GameManagerComponent() : engine::Component() {
  this->name = "GameManagerComponent";
  this->component_type = "GameManagerComponent";
  this->map_name.resize(64);
}



json GameManagerComponent::SaveLapData()
{
    json j;
    int ctr = 0;
    for (auto val : best_laps) {
        j[ctr]["username"] = val.second.username;
        j[ctr]["lap_time"] = val.second.lap_time;
        j[ctr]["s1"] = val.second.s1_time;
        j[ctr]["s2"] = val.second.s2_time;
        j[ctr]["s3"] = val.second.s3_time;
        ctr++;
    }

    try{
      std::ofstream file("lapdata/" + std::string(this->map_name.c_str()) + ".json");

      if (!file.is_open()) {
        std::cout << "failed to open lap file for writing\n";
        return j;
      }
      file << j.dump();
      file.close();

    } catch(std::exception ex)
    {
        std::cout << ex.what() << "\n";
    }
    return j;
}

void GameManagerComponent::LoadLapData(std::string path)
{
    best_laps.clear();
    std::ifstream f(path);
    if(!f.is_open())
    {
        std::cout << "failed to open lap data file\n";
        return;
    }
    json data = json::parse(f);
    for(auto value : data)
    {
        LapInfo l;
        l.lap_time = value["lap_time"];
        l.s1_time = value["s1"];
        l.s2_time = value["s2"];
        l.s3_time = value["s3"];
        l.username = value["username"];
        l.valid = true;
        best_laps[l.username] = l;
    }
    f.close();
}

void GameManagerComponent::tick(float dt) {

  auto ply = engine::Engine()->GetLocalPlayer();
  if(ply == nullptr)
  {
    return;
  }

  player_collider = (engine::CollisionComponent*) ply->GetOwner()->GetComponent("CollisionComponent");

  ImGui::Begin("Lap Timer",NULL, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_AlwaysAutoResize);
  ImGui::Text("%f",this->lap_timer);
  ImGui::Text("S1: %f",this->current_lap.s1_time);
  ImGui::Text("S2: %f", this->current_lap.s2_time);
  ImGui::Text("S3: %f", this->current_lap.s3_time);
  ImGui::End();

  ImGui::Begin("Best Laps", NULL, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoDecoration | ImGuiWindowFlags_AlwaysAutoResize);
  ImGui::SetWindowPos(ImVec2(engine::Engine()->GetRenderer()->WindowWidth() - 200,100));
  std::vector<LapInfo> laps;
  for(auto val : best_laps)
  {
      laps.push_back(val.second);
  }

  std::sort(laps.begin(), laps.end(), [] (const LapInfo& a, const LapInfo& b){
      return a.lap_time>b.lap_time;
  });

  for(int i = 0; i < laps.size();i++)
  {
      ImGui::Text("%d\t%s\t%f",i+1, laps[i].username.c_str(),laps[i].lap_time);
  }
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
    current_lap.username = this->current_username;
    current_lap.valid = true;

    if(best_laps.find(current_username) == best_laps.end())
    {
        best_laps[current_username] = current_lap;
        SaveLapData();
    }
    else
    {
        LapInfo f = best_laps[current_username];
        if(current_lap.lap_time < f.lap_time)
        {
            best_laps[current_username] = current_lap;
            SaveLapData();
        }
    }


    current_lap = LapInfo();
    lap_timer = 0.0f;

  }
  sector_timer = 0.0f;
}

void GameManagerComponent::init() {
    engine::Engine()->GetSoundManager()->PlaySound("assets/music/drone-break_menu.mp3");
    LoadLapData("lapdata/" + std::string(this->map_name.c_str()) + ".json");
}

void GameManagerComponent::DrawWidget() {
    ImGui::InputText("Map Name", map_name.data(),64);
}

json GameManagerComponent::Save() {
  json j;
  j["name"] = name;
  j["uid"] = uid;
  j["component_type"] = component_type;
  j["map_name"] = std::string(map_name.c_str());
  return j;

}

bool GameManagerComponent::Load(json value) {
  PROPERTY_LOAD(name)
  PROPERTY_LOAD(uid)
  PROPERTY_LOAD(component_type)
  PROPERTY_LOAD(map_name)
  map_name.resize(64);
  return true;
}

FACTORY_DEF(GameManagerComponent)
