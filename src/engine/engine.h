#pragma once

#include <vector>

#include "../s7/s7.h"

#include "opengl_renderer.h"
#include "scene.h"

namespace engine {

class opengl_renderer;


struct EngineCreateInfo {
  std::string game_name;
  uint16_t initial_window_width;
  uint16_t initial_window_height;
};

    class engine_instance {
    public:
        engine_instance(EngineCreateInfo& info);
        ~engine_instance();
        void Run();

    private:
        GLFWwindow* window;
        std::vector<engine::Scene *> loaded_scenes;
        engine::Scene* current_scene = nullptr;
        s7_scheme *scheme_interpreter;
        engine::opengl_renderer* renderer;
    };

  engine_instance* CreateEngine(EngineCreateInfo& create_info);
}
