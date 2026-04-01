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


  float DeltaTime();

  void StartFrame();


  void EndFrame();

  void InitForImGui();
private:
  double last;
  float delta_time;
  GLFWwindow* window;
};
}
