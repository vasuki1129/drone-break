#include "scene.h"
#include "camera_component.h"
#include "engine.h"
namespace engine {

glm::mat4 Scene::GetCurrentCameraMatrix() {
  //return a default if there is no main camera
  if (this->current_camera == nullptr) {
    glm::mat4 view = glm::lookAt(glm::vec3(-5.0f,4.0f,5.0f), glm::vec3(0.0f,0.0f,0.0f), glm::vec3(0.0f,1.0f,0.0f));
    glm::mat4 projection = glm::perspective(90.0f, (float)Engine()->GetRenderer()->WindowWidth() / (float)Engine()->GetRenderer()->WindowHeight(), 0.01f, 100.0f);
    //glm::mat4 projection = glm::ortho(-20.0f,20.0f,-20.0f,20.0f,0.01f,100.0f);
    return projection * view;
  }
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
  this->current_camera = nullptr;
}

Scene::~Scene() {
  delete root;
}

Scene::Scene(json value) {
  name = value["name"];
  root = new Transform(value["root"]);
  this->current_camera = nullptr;
}

json Scene::Save() {
  return root->Save();
}

Transform *Scene::GetRoot() {
  return root;
}

bool Scene::IsValid() { return finalized; }

}
