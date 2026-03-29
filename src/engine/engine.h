#pragma once

#include <vector>

#include "../s7/s7.h"

#include "opengl_renderer.h"
#include "scene.h"

namespace engine {
    class engine_instance {
    public:
        engine_instance();
        ~engine_instance();
        void Run();

    private:
        GLFWwindow* window;
        std::vector<engine::Scene *> loaded_scenes;
        engine::Scene* current_scene = nullptr;
        s7_scheme *scheme_interpreter;
        engine::opengl_renderer* renderer;

    };
}
