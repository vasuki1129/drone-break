#include "scene.h"
#include "camera_component.h"
#include "engine.h"
namespace engine {

CameraComponent* Scene::GetCurrentCamera()
{
  return current_camera;
}

void Scene::SetCamera(CameraComponent* cam)
{
  this->current_camera = cam;
}

glm::vec3 Scene::GetCurrentCameraPosition() {
  if (this->current_camera == nullptr) {
    return glm::vec3(-5.0f,4.0f,5.0f);
  } else {
    return current_camera->GetOwner()->GetGlobalPosition();
  }
}

glm::mat4 Scene::GetCurrentCameraMatrix() {
  //return a default if there is no main camera
  if (this->current_camera == nullptr) {
    glm::mat4 view = glm::lookAt(glm::vec3(-5.0f,4.0f,5.0f), glm::vec3(0.0f,0.0f,0.0f), glm::vec3(0.0f,1.0f,0.0f));
    glm::mat4 projection = glm::perspective(90.0f, (float)Engine()->GetRenderer()->WindowWidth() / (float)Engine()->GetRenderer()->WindowHeight(), 0.01f, 100.0f);
    //glm::mat4 projection = glm::ortho(-20.0f,20.0f,-20.0f,20.0f,0.01f,100.0f);

    std::cout << "Using default camera.\n";
    return projection * view;
  }
  return this->current_camera->GetCameraMatrix();
}

Scene::Scene(std::string name)
  :Scene()
{
  this->name = name;
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

bool Scene::Load(json value)
{

  if(!value.contains("name"))
  {
    std::cout << "Scene has malformed header.\n";
    return false;
  }
  name = value["name"];


  if(!value.contains("root"))
  {
    std::cout << "Scene has no root component.\n";
  }

  root = new Transform();
  root->Load(value["root"]);
  this->current_camera = (CameraComponent*)root->FindComponentByUID(value["active_camera"]);
  this->finalized = true;
  return true;
}

json Scene::Save() {
  json j;
  j["name"] = name;
  j["root"] = root->Save();
  j["active_camera"] = current_camera->GetUID();
  return j;
}

Transform *Scene::GetRoot() {
  return root;
}

bool Scene::IsValid() { return finalized; }

}
