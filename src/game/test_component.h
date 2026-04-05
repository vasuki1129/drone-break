#pragma once
#include "../engine/engine.h"
#include "../engine/component.h"

class TestComponent : engine::Component {
  void tick(float dt) override;
  void DrawWidget() override;

  float rotation_speed = 1.0f;
  glm::vec3 rotation_axis = glm::vec3(0.0,1.0,0.0);
  public:
  TestComponent();
};

FACTORY(TestComponent);
