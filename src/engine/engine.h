#pragma once

#include <vector>

#include "../s7/s7.h"

#include "opengl_renderer.h"
#include "scene.h"

namespace engine {

class OpenGLRenderer;


struct EngineCreateInfo {
  std::string game_name;
  uint16_t initial_window_width;
  uint16_t initial_window_height;
};

class EngineInstance {
public:
  EngineInstance(EngineCreateInfo& info);
  ~EngineInstance();
  void Run();

private:
  GLFWwindow* window;
  std::vector<engine::Scene *> loaded_scenes;
  engine::Scene* current_scene = nullptr;
  s7_scheme *scheme_interpreter;
  engine::OpenGLRenderer* renderer;
};

EngineInstance* CreateEngine(EngineCreateInfo& create_info);

}
