
#pragma once
#include "../engine/engine.h"
#include "../engine/component.h"
#include "../json/json.hpp"
#include "collision_component.h"

struct LapInfo {
  bool valid = false;
  std::string username = "nobody";
  float lap_time = 0.0f;
  float s1_time = 0.0f;
  float s2_time = 0.0f;
  float s3_time = 0.0f;
};

class GameManagerComponent : engine::Component {
public:
  void init() override;
  void tick(float dt) override;
  void DrawWidget() override;
  json Save() override;
  bool Load(json value) override;

  std::map<std::string, LapInfo> best_laps;

  std::string map_name;

  LapInfo current_lap;
  LapInfo best_lap;
  LapInfo last_lap;

  int current_lap_index = 0;

  float lap_timer= 0.0f;
  float sector_timer = 0.0f;
  float total_timer = 0.0f;

  std::string current_username = "max";

  engine::CollisionComponent* player_collider;

  void RecordSector(int sector);

  json SaveLapData();
  void LoadLapData(std::string path);

  GameManagerComponent();

};

FACTORY(GameManagerComponent);
