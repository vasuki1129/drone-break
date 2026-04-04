#include "scene_loader.h"
#include "mesh_component.h"
#include "engine.h"
namespace engine {
bool SceneLoader::CueScene(std::string path) {}

bool SceneLoader::LoadScene(std::string path) {}

void SceneLoader::LoadDefaultScene() {

  if (current_scene != nullptr)
    delete current_scene;

  current_scene = new Scene();
  Transform *tr = new Transform(std::string("DefaultCube"));
  MeshComponent *mesh_comp = new MeshComponent("MeshComponent");

  tr->Translate(glm::vec3(5.0,0.0,0.0));

  mesh_comp->SetMesh("DefaultCube.Suzanne");
  mesh_comp->SetMaterial("default");
  tr->AddComponent(mesh_comp);
  current_scene->GetRoot()->AddChild(tr);
}

bool SceneLoader::UpdateCurrentScene(float dt) {

  if (this->current_scene == nullptr) {

    std::cout << "Error, cannot update scene as there is no scene loaded\n";
    return false;
  }
  else
  {
    this->current_scene->Tick(dt);
    this->current_scene->Render();
    return true;
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
