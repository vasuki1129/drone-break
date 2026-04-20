#pragma once
#include "../engine/component.h"
#include "../json/json.hpp"
#include <glm/glm.hpp>

using json = nlohmann::json;

namespace engine{
class TriggerComponent;

class CollisionComponent : public Component {

public:


  virtual void init() override;

  virtual void destroy() override;



  virtual void tick(float dt) override;
  virtual void DrawWidget() override;
  virtual json Save() override;
  virtual bool Load(json value) override;

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
