#include "scene.h"
#include "camera_component.h"
namespace engine {

glm::mat4 Scene::GetCurrentCameraMatrix() {
  return this->current_camera->GetCameraMatrix();
}

void Scene::Render() {
  root->ProcessRender();
}

void Scene::Tick(float dt) {
  root->ProcessTick(dt);
}

Scene::Scene() {
  root = new Transform(std::string("Root"));
}

Scene::~Scene() {
  delete root;
}

Scene::Scene(json value) {
  name = value["name"];
  root = new Transform(value["root"]);
}

json Scene::Save() {
  return root->Save();
}

Transform *Scene::GetRoot() {
  return root;
}

bool Scene::IsValid() { return finalized; }




}
