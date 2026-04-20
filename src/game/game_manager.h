
#pragma once
#include "../engine/engine.h"
#include "../engine/component.h"
#include "../json/json.hpp"



class GameManagerComponent : engine::Component {
public:
  void init() override;
  void DrawWidget() override;
  json Save() override;
  bool Load(json value) override;

  GameManagerComponent();

};

FACTORY(GameManagerComponent);
