#pragma once
#include "../s7/s7.h"

#include <variant>
#include <string>

namespace engine {

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
