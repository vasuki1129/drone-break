#include "scene_loader.h"
#include "camera_component.h"
#include "mesh_component.h"
#include "engine.h"
#include <fstream>
namespace engine {
bool SceneLoader::CueScene(std::string path) {return false;}

bool SceneLoader::LoadScene(std::string path) {
  std::ifstream f(path);
  json data = json::parse(f);
  Scene* scn = new Scene();
  scn->Load(data);
  if (scn->IsValid()) {
    this->DeloadScene();
    this->current_scene = scn;
    return true;
  }
  else
  {
    return false;
  }
}

void SceneLoader::DeloadScene()
{
  delete this->current_scene;
}

void SceneLoader::SaveScene(std::string path)
{
  json output = this->current_scene->Save();
  std::cout << output.dump(2) << "\n";
  std::ofstream outfile(path);
  if(outfile.is_open())
  {
    outfile << output.dump(2);
  }
}

void SceneLoader::LoadDefaultScene() {
  if (current_scene != nullptr)
    delete current_scene;
  current_scene = new Scene(std::string("DefaultScene"));
  Transform *tr = new Transform(std::string("DefaultCube"));
  MeshComponent *mesh_comp = new MeshComponent(std::string("MeshComponent"));
  tr->Translate(glm::vec3(0.0,0.0,0.0));
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
    return true;
  }
}

bool SceneLoader::RenderCurrentScene()
{
  if (this->current_scene == nullptr) {
    std::cout << "Error, cannot render scene as there is no scene loaded\n";
    return false;
  }
  else
  {
    this->current_scene->Render();
    return true;
  }
}

Scene *SceneLoader::GetCurrentScene() {
  if(current_scene == nullptr) std::cout << "WARNING: No scene loaded!\n";
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
