#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

namespace engine {
class opengl_renderer {
public:
  opengl_renderer();
  ~opengl_renderer();
private:
  GLFWwindow* window;
};
}
