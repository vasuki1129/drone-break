#include "engine.h"
#include "opengl_renderer.h"

namespace engine {

engine_instance* instance = nullptr;


engine_instance *Engine() {
  return instance;

}


void engine_instance::Run() {
  while (!glfwWindowShouldClose(window)) {
    glfwPollEvents();
    renderer->PushFrame();
  }

}


engine_instance *CreateEngine(EngineCreateInfo &create_info) {
  instance = new engine_instance(create_info);
  return instance;
}


engine_instance::engine_instance(EngineCreateInfo& create_info)
{
  scheme_interpreter = s7_init();
  renderer = new engine::opengl_renderer(&window, create_info);
}

engine_instance::~engine_instance()
{
    delete renderer;
}

}
