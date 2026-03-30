#include "engine.h"
#include "opengl_renderer.h"

namespace engine {


std::string EngineInstance::GetVersionString() {
  std::string out;
  out += "LIGHT v0.2.2\n";
  out += "Copyright 2026 Deepfrog\n";
}




EngineInstance* instance = nullptr;


EngineInstance *Engine() {
  return instance;

}


void EngineInstance::Run() {
  while (!glfwWindowShouldClose(window)) {
    glfwPollEvents();
    renderer->PushFrame();
  }

}


EngineInstance *CreateEngine(EngineCreateInfo &create_info) {
  instance = new EngineInstance(create_info);
  return instance;
}


EngineInstance::EngineInstance(EngineCreateInfo& create_info)
{
  scheme_interpreter = s7_init();
  renderer = new engine::OpenGLRenderer(&window, create_info);
}

EngineInstance::~EngineInstance()
{
    delete renderer;
}

}
