#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "engine.h"

namespace engine {
class OpenGLRenderer {
public:
  OpenGLRenderer(GLFWwindow** smuggle, struct EngineCreateInfo& create_info);
  ~OpenGLRenderer();
  bool ShouldClose();
  void PushFrame();
private:
  GLFWwindow* window;
};
}
