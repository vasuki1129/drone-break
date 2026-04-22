#pragma once
#include "../engine/engine.h"
#include "../engine/component.h"

class SkyboxComponent : engine::Component {
  void tick(float dt) override;

  void DrawWidget() override;

  json Save() override;
  bool Load(json value) override;
  public:
  SkyboxComponent();
};

FACTORY(SkyboxComponent);
