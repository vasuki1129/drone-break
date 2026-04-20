#pragma once
#include "collision_component.h"

using json = nlohmann::json;

namespace engine {

class TriggerComponent : public CollisionComponent
{
  public:

  virtual void tick(float dt) override;

  virtual void init() override;
  virtual void destroy() override;
  virtual void DrawWidget() override;
  int trigger_id = 0;

  virtual json Save() override;
  virtual bool Load(json value) override;

  TriggerComponent();

};

FACTORY(TriggerComponent);
}
