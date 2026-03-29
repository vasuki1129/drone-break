#include "engine.h"
#include "opengl_renderer.h"

namespace engine {

void engine_instance::Run() {
  while (!glfwWindowShouldClose(window)) {
    glfwPollEvents();
    renderer->PushFrame();
  }

}

engine_instance::engine_instance()
{
  scheme_interpreter = s7_init();
  renderer = new engine::opengl_renderer(&window);
}

engine_instance::~engine_instance()
{
    delete renderer;
}

}
