#pragma once
#include "scene.h"
#include "errorcheck.h"
#include <future>


namespace engine {

class SceneLoader {
public:
  Error<bool> CueScene(std::string path); // async load scene from json dump to on deck scene, for streaming
  Error<bool> LoadScene(std::string path); // sync load scene from json dump to current scene
  void LoadDefaultScene();                 // immediately load the startup scene


private:
  Scene* current_scene;
  Scene* scene_in_progress_load;
};
}
