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
private:
  glm::vec3 position;
  glm::quat rotation;
  glm::vec3 scale;
  Transform *parent;
  std::vector<Transform *> children;
  std::vector<Component*> components;
};

}
