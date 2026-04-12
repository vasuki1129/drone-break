#pragma once
#include "scene.h"
#include "../dflib/dflib.h"
#include <future>

namespace engine {

class SceneLoader {
public:
  SceneLoader();
  ~SceneLoader();
  //std::future<Scene*> CueScene(std::string path); // async load scene from json dump to on deck scene, for streaming or quickswapping scenes,
  bool LoadScene(std::string path); // sync load scene from json dump to current scene
  void LoadDefaultScene();                 // immediately load the startup scene
  void SaveScene(std::string path);
  void DeloadScene();

  bool UpdateCurrentScene(float dt);
  bool RenderCurrentScene();
  Scene* GetCurrentScene();

  void SaveAsCheckpoint();
  void RewindToCheckpoint();


private:
  Scene *current_scene = nullptr;
  Scene *rewind_scene = nullptr;
  Scene* scene_in_progress_load = nullptr;
};
}
