#pragma once
#include "transform.h"
#include "camera_component.h"
#include "saveable.h"
namespace engine
{

class Scene : public Saveable {
public:
  Scene();
  Scene(json value);
  ~Scene();
  void Render();
  void Tick(float dt);
  json Save() override;
  Transform *GetRoot();
  bool IsValid();
  glm::mat4 GetCurrentCameraMatrix();
  glm::vec3 GetCurrentCameraPosition();
private:
  CameraComponent* current_camera;
  std::string name;
  std::string path;
  Transform* root;
  bool finalized;
};

}
