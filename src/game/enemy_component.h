#pragma once
#include "../engine/engine.h"
#include "../engine/component.h"
#include "../json/json.hpp"
#include <glm/glm.hpp>

using json = nlohmann::json;





class EnemyComponent : public engine::Component {
public:
  void tick(float dt) override;
  void Think();
  void DrawWidget() override;

  float GetSpeed();


  json Save() override;
  bool Load(json value) override;

  EnemyComponent();


private:
  glm::vec2 current_input = glm::vec2(0.0,0.0);
  float throttle_input = 0.0f;

  float damping = 0.05;
  float resistance = 0.05;
  float engine_power = 6.0f;
  glm::vec3 velocity;

};

FACTORY(EnemyComponent);
