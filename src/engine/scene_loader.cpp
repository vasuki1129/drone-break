#include "scene_loader.h"
#include "mesh_component.h"
namespace engine {
Error<bool> SceneLoader::CueScene(std::string path) {}

Error<bool> SceneLoader::LoadScene(std::string path) {}

void SceneLoader::LoadDefaultScene() {

  if (current_scene != nullptr)
    delete current_scene;

  current_scene = new Scene();
  //Transform *tr = new Transform(std::string("DefaultCube"));
  //MeshComponent *meshComp = new MeshComponent();
}

Error<bool> SceneLoader::UpdateCurrentScene(float dt) {

  if (this->current_scene == nullptr)
  {
    return MakeErr<bool>("No Scene Loaded");
  }
  else
  {
    this->current_scene->Tick(dt);
    this->current_scene->Render();
    return MakeOk(true);
  }
}

Scene *SceneLoader::GetCurrentScene() {
  return current_scene;
}

SceneLoader::SceneLoader() {
  LoadDefaultScene();
}

SceneLoader::~SceneLoader() {

  if (current_scene != nullptr) {
    delete current_scene;
  }

  if (scene_in_progress_load != nullptr) {
    delete scene_in_progress_load;
  }

}




}
