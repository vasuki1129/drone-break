#pragma once
#include "component.h"
#include <string>
#include <variant>
#include "../s7/s7.h"
namespace engine {

struct ScriptLiteral {
  std::string script;
};

struct ScriptFile {
  std::string script_path;
  std::string cached_script;
  bool stale;
};

class ScriptComponent : public Component {
public:
  virtual void tick(float dt) override;
  virtual void init() override;
  virtual void destroy() override;
  void ReloadScripts();

private:
  std::variant<ScriptLiteral, ScriptFile> init_script;
  std::variant<ScriptLiteral, ScriptFile> tick_script;
  std::variant<ScriptLiteral, ScriptFile> destroy_script;

  s7_pointer tick_code;
  s7_pointer init_code;
  s7_pointer destroy_code;

};
}
