#pragma once
#include "shader.h"
namespace engine {
class ScreenShader : public Shader {


  ScreenShader(std::string path);
  ~ScreenShader();
  void Apply();
};
  
}
