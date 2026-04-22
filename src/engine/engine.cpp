#include "engine.h"
#include "input.h"
#include "opengl_renderer.h"
#include "mesh_component.h"
#include "physics.h"
#include <GLFW/glfw3.h>
#include <GL/glew.h>
#include "../imgui/imgui.h"
#include "../imgui/imgui_impl_glfw.h"
#include "../imgui/imgui_impl_opengl3.h"
#include "sound_manager.h"

namespace engine {


void EngineInstance::Stop()
{

}

std::string EngineInstance::GetVersionString() {
  std::string out;
  out += "LIGHT v0.2.2";
  return out;
}


Component *EngineInstance::GetLocalPlayer() {
  return local_player;
}

void EngineInstance::SetLocalPlayer(Component* local_player) {
  this->local_player = local_player;
}

EngineInstance* instance = nullptr;

SoundManager* EngineInstance::GetSoundManager() {
  return sound_manager;
}

Component *EngineInstance::CreateComponent(std::string component_type_name) {
  if (registered_component_types.find(component_type_name) !=
      registered_component_types.end()) {
    Component* c = registered_component_types[component_type_name]();
    return c;
  } else {
    std::cout << "Component type `" + component_type_name + "` not found\n";
    return nullptr;
  }
}

Component *EngineInstance::LoadComponent(std::string component_type_name, json value) {
  if (registered_component_types.find(component_type_name) !=
      registered_component_types.end()) {
    Component* comp =  registered_component_types[component_type_name]();
    comp->Load(value);
    return comp;
  } else {
    std::cout << "Component type `" + component_type_name + "` not found\n";
    return nullptr;
  }
}

std::vector<std::string> EngineInstance::GetRegisteredComponentsList() {
  std::vector<std::string> out;
  for (auto comp : this->registered_component_types) {
    out.push_back(comp.first);
  }
  return out;
}

EngineInstance *Engine() {
  return instance;
}


PhysicsHandler* EngineInstance::GetPhysics()
{
  return this->physics_handler;
}

AssetManager *EngineInstance::GetAssetManager() {
  return this->asset_loader;
}

GLFWwindow *EngineInstance::GetWindow() {
  return window;
}

void EngineInstance::Run() {
  engine::Engine()->GetSceneLoader()->LoadScene(this->startup_scene,nullptr);
  while (!glfwWindowShouldClose(window)) {
    glfwPollEvents();
    renderer->StartFrame();
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
    Engine()->GetSceneLoader()->GetCurrentScene()->SetCameraToMain();
    GetSceneLoader()->UpdateCurrentScene(this->GetRenderer()->DeltaTime());
    Engine()->GetSceneLoader()->RenderCurrentScene();
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    input_handler->Update();
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

void EngineInstance::RegisterBuiltinComponents() {
  RegisterComponent("MeshComponent", FACTORY_REF(MeshComponent));
  RegisterComponent("EditorCameraComponent", FACTORY_REF(EditorCameraComponent));
  RegisterComponent("CameraComponent", FACTORY_REF(CameraComponent));
}

void EngineInstance::Initialize() {
  input_handler = new InputHandler();
  asset_loader = new AssetManager();
  scheme_interpreter = s7_init();
  sound_manager = new SoundManager();


  asset_loader->Rescan();
  RegisterBuiltinComponents();
  scene_loader = new engine::SceneLoader();
  physics_handler = new PhysicsHandler();
  renderer->InitForImGui();
  Engine()->GetInput()->DisableCursor();
}

InputHandler *EngineInstance::GetInput() {
  return input_handler;

}


EngineInstance::EngineInstance(EngineCreateInfo &create_info) {
  renderer = new engine::OpenGLRenderer(&window, create_info);
  this->startup_scene = create_info.startup_scene;
}

OpenGLRenderer *EngineInstance::GetRenderer() {
  return renderer;
}

EngineInstance::~EngineInstance()
{
  delete renderer;
  delete physics_handler;
}

}
