#pragma once
#include "component.h"
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <vector>

namespace engine {

class Transform {
public:
  void ProcessRender();
  void ProcessTick(float dt);

  void Translate(glm::vec3 offset);
  void Scale(glm::vec3 amount);

  glm::vec3 Forward();
  glm::vec3 Backward();
  glm::vec3 Up();
  glm::vec3 Down();
  glm::vec3 Left();
  glm::vec3 Right();

  glm::vec3 GetGlobalPosition();
  glm::vec3 GetLocalPosition();

  glm::quat GetGlobalRotation();
  glm::quat GetLocalRotation();

  glm::vec3 GetGlobalScale();
  glm::vec3 GetLocalScale();

private:
  glm::vec3 position;
  glm::quat rotation;
  glm::vec3 scale;
  Transform *parent;
  std::vector<Transform *> children;
  std::vector<Component*> components;
};

}
