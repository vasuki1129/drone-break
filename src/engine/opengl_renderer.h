#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "engine.h"

namespace engine {
class opengl_renderer {
public:
  opengl_renderer(GLFWwindow** smuggle, struct EngineCreateInfo& create_info);
  ~opengl_renderer();
  bool ShouldClose();
  void PushFrame();
private:
  GLFWwindow* window;
};
}
