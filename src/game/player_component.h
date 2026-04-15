#pragma once
#include "../engine/engine.h"
#include "../engine/component.h"
#include "../json/json.hpp"

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
  float damping = 0.01f;

  PlayerComponent();

};

FACTORY(PlayerComponent);
