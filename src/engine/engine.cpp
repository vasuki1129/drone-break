#include "engine.h"
#include "opengl_renderer.h"

namespace engine {

std::string EngineInstance::GetVersionString() {
  std::string out;
  out += "LIGHT v0.2.2\n";
  out += "Copyright 2026 Deepfrog\n";
  return out;
}

EngineInstance* instance = nullptr;

EngineInstance *Engine() {
  return instance;
}

AssetManager *EngineInstance::GetAssetManager() {
  return this->asset_loader;
}

GLFWwindow *EngineInstance::GetWindow() {
  return window;
}

void EngineInstance::Run() {
  while (!glfwWindowShouldClose(window)) {
    glfwPollEvents();
    renderer->StartFrame();
    GetSceneLoader()->UpdateCurrentScene(this->GetRenderer()->DeltaTime());
    renderer->EndFrame();
  }
}

SceneLoader *EngineInstance::GetSceneLoader() {
  return scene_loader;
}

EngineInstance *CreateEngine(EngineCreateInfo &create_info) {
  instance = new EngineInstance(create_info);
  instance->Initialize();
  return instance;
}


void EngineInstance::Initialize() {
  asset_loader = new AssetManager();
  scheme_interpreter = s7_init();
  asset_loader->Rescan();
  scene_loader = new engine::SceneLoader();
}



EngineInstance::EngineInstance(EngineCreateInfo &create_info) {
  renderer = new engine::OpenGLRenderer(&window, create_info);
}

OpenGLRenderer *EngineInstance::GetRenderer() {
  return renderer;
}

EngineInstance::~EngineInstance()
{
    delete renderer;
}

}
