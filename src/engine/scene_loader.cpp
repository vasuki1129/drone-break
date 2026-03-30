#include "scene_loader.h"

namespace engine {
Error<bool> SceneLoader::CueScene(std::string path) {}

Error<bool> SceneLoader::LoadScene(std::string path) {}

void SceneLoader::LoadDefaultScene() {

  if (current_scene != nullptr)
    delete current_scene;

  current_scene = new Scene();
}





  
}
