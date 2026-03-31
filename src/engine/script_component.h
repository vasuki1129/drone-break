#pragma once
#include "component.h"
#include <string>
#include <variant>
#include "script_engine.h"
#include "../s7/s7.h"
namespace engine {

class ScriptComponent : public Component {
public:
  virtual void tick(float dt) override;
  virtual void init() override;
  virtual void destroy() override;
  void ReloadScripts();
private:
  ScriptData init_script;
  ScriptData tick_script;
  ScriptData destroy_script;
};

}
