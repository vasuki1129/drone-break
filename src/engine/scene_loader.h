#pragma once
#include "scene.h"
#include "errorcheck.h"
namespace engine {

class SceneLoader {
public:
  Error<bool> CueScene(std::string path);
private:
  Scene* current_scene;
  Scene* scene_in_progress_load;
};

}
