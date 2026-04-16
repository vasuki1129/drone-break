#pragma once
#include "../engine/engine.h"
#include "../engine/component.h"
#include "../json/json.hpp"
#include <string>
using json = nlohmann::json;

class PlayerComponent : engine::Component {

public:

  void tick(float dt) override;
  void DrawWidget() override;
  json Save() override;
  bool Load(json value) override;

  glm::vec3 GetVelocity();
  float GetSpeed();
  void SetVelocity(glm::vec3 vel);


  float movement_speed = 5.0;
  glm::vec3 velocity = glm::vec3(0.0f,0.0f,0.0f);
  float damping = 0.8f;
  float resistance = 0.1f;
  PlayerComponent();


  void PushMessage(std::string message);


  std::string message_buffer = "";
  std::string display_message = "";
  float print_interval = 0.1f;
  float print_timer = 0.0f;
};

FACTORY(PlayerComponent);
