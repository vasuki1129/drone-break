#pragma once
#include "../s7/s7.h"

#include "asset_manager.h"

#include <variant>
#include <string>

namespace engine {

struct ScriptLiteral {
  std::string script;
};

struct ScriptFile {
  std::string script_path;
  std::string cached_script;
  bool stale;
};

typedef std::variant<ScriptLiteral, ScriptFile> ScriptData;

class ScriptEngine {
public:
  virtual void eval_string() = 0;
};

class SchemeScriptEngine : public ScriptEngine {

public:
   SchemeScriptEngine();
   ~SchemeScriptEngine();
   void eval_string() override;
private:
  s7_scheme* scheme_handle;
};
  
}
