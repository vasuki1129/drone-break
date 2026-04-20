#pragma once
#include "../engine/engine.h"
#include "../engine/component.h"
#include "../json/json.hpp"


class MenuBackgroundScroll : engine::Component {
public:
  void tick(float dt) override;
  void DrawWidget() override;
  json Save() override;
  bool Load(json value) override;

  MenuBackgroundScroll();

  float x_minimum = 0.0f;
  float x_maximum = 10.0f;
  float speed = 5.0f;



};

FACTORY(MenuBackgroundScroll);
