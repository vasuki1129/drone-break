#pragma once
#include "../engine/engine.h"
#include "../engine/component.h"
#include "../json/json.hpp"


class MenuShipController : public engine::Component {
public:
  void tick(float dt) override;
  void init() override;
  void DrawWidget() override;
  json Save() override;
  bool Load(json value) override;

  MenuShipController();

  float amplitude = 0.3f;
  float initial_position;
  float timer = 0.0f;
  float speed = 5.0f;


  //Menu
  int menu_state = 0;


};

FACTORY(MenuShipController);
