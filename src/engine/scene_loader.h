#pragma once
#include "scene.h"
#include "../dflib/dflib.h"
#include <future>


namespace engine {

class SceneLoader {
public:
  SceneLoader();
  ~SceneLoader();
  bool CueScene(std::string path); // async load scene from json dump to on deck scene, for streaming
  bool LoadScene(std::string path); // sync load scene from json dump to current scene
  void LoadDefaultScene();                 // immediately load the startup scene

  bool UpdateCurrentScene(float dt);
  Scene* GetCurrentScene();

private:
  Scene* current_scene = nullptr;
  Scene* scene_in_progress_load = nullptr;
};
}
