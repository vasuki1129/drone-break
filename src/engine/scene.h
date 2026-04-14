#pragma once
#include "transform.h"
#include "camera_component.h"
#include "saveable.h"
namespace engine
{

class Scene : public Saveable {
public:
  Scene();
  Scene(std::string name);
  ~Scene();
  void Render();
  void Tick(float dt);
  void EditorRender();
  json Save() override;
  bool Load(json value) override;

  Transform *GetRoot();
  bool IsValid();

  void SetCamera(CameraComponent* cam);
  void SetMainCamera(CameraComponent* cam);
  void SetCameraToMain();

  Scene *Clone();

  glm::mat4 GetCurrentCameraMatrix();
  glm::vec3 GetCurrentCameraPosition();
  CameraComponent* GetCurrentCamera();
private:
  CameraComponent* current_camera;
  CameraComponent* main_camera;
  std::string name;
  std::string path;
  Transform* root;
  bool finalized;
};

}
