#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

namespace engine {
class opengl_renderer {
public:
  opengl_renderer(GLFWwindow** smuggle);
  ~opengl_renderer();
  bool ShouldClose();
  void PushFrame();
private:
  GLFWwindow* window;
};
}
