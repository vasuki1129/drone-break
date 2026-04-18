/*
 * * * * * *
 *
 *     _/        _/_/_/    _/_/_/  _/    _/  _/_/_/_/_/
 *    _/          _/    _/        _/    _/      _/
 *   _/          _/    _/  _/_/  _/_/_/_/      _/
 *  _/          _/    _/    _/  _/    _/      _/
 * _/_/_/_/  _/_/_/    _/_/_/  _/    _/      _/
 *
 *
 *    hyper minimalist editor based game engine
 *
 *
 * * * * * *
 *
 * This engine is proudly AI free, and will remain so
 *
 * * * * * *
 */

#pragma once

#include <concepts>

#include <vector>

#include "../s7/s7.h"

#include "opengl_renderer.h"
#include "physics.h"
#include "scene.h"
#include "script_engine.h"
#include "scene_loader.h"
#include "asset_manager.h"
#include "input.h"
#include "camera_component.h"

namespace engine {

class AssetManager;
class SceneLoader;
class OpenGLRenderer;
class PhysicsHandler;
struct Ray;
struct EngineCreateInfo {
  std::string game_name;
  uint16_t initial_window_width;
  uint16_t initial_window_height;
  std::string startup_scene;
};

class EngineInstance {
public:
  EngineInstance(EngineCreateInfo& info);
  ~EngineInstance();
  void Run();
  std::string GetVersionString();
  SceneLoader* GetSceneLoader();
  OpenGLRenderer *GetRenderer();
  GLFWwindow *GetWindow();
  AssetManager* GetAssetManager();
  PhysicsHandler* GetPhysics();

  Component *GetLocalPlayer();
  void SetLocalPlayer(Component* local_player);





  void Initialize();

  std::vector<std::string> GetRegisteredComponentsList();

  Component *CreateComponent(std::string component_type_name);
  Component* LoadComponent(std::string component_type_name,json value);
  void RegisterComponent(std::string type_name, Component* (*factory)(void))
  {
      registered_component_types[type_name] = factory;
  };



  InputHandler* GetInput();

private:
  std::string startup_scene;
  Component* local_player;

  void RegisterBuiltinComponents();
  glm::vec2 window_size;
  GLFWwindow *window;
  AssetManager* asset_loader;
  SceneLoader* scene_loader;
  s7_scheme *scheme_interpreter;
  OpenGLRenderer* renderer;
  InputHandler* input_handler;
  PhysicsHandler* physics_handler;
  std::map<std::string, Component* (*) ()> registered_component_types;
};

EngineInstance* CreateEngine(EngineCreateInfo& create_info);

EngineInstance *Engine();
}
