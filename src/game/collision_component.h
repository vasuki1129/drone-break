#pragma once
#include "../engine/engine.h"
#include "../engine/component.h"
#include "../json/json.hpp"

using json = nlohmann::json;

class CollisionComponent : engine::Component {

public:

  void tick(float dt) override;
  void DrawWidget() override;
  json Save() override;
  bool Load(json value) override;


  glm::vec3 CheckCollision(CollisionComponent* other);




  glm::vec3 offset = glm::vec3(0.0,0.0,0.0);
  glm::vec3 bounds = glm::vec3(1.0,1.0,1.0);

  CollisionComponent();
};

FACTORY(CollisionComponent);
