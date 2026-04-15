#pragma once
#include "../engine/engine.h"
#include "../engine/component.h"
#include "../json/json.hpp"
#include <glm/glm.hpp>

using json = nlohmann::json;

namespace engine{


class CollisionComponent : engine::Component {

public:


  void init() override;

  void destroy() override;



  void tick(float dt) override;
  void DrawWidget() override;
  json Save() override;
  bool Load(json value) override;

  void editor_render() override;

  bool colliding = false;

  bool CheckCollision(CollisionComponent* other, glm::vec3* vector_out);

  glm::vec3 offset = glm::vec3(0.0,0.0,0.0);
  glm::vec3 bounds = glm::vec3(1.0,1.0,1.0);

  bool should_tick = false;


  CollisionComponent();
};

FACTORY(CollisionComponent);
}
