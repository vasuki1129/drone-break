#pragma once
#include "component.h"
#include "saveable.h"
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include <vector>
#include <string>
#include "../dflib/dflib.h"

namespace engine {

class Component;

class Transform : public Saveable {
public:
  Transform();
  Transform(json value);
  Transform(std::string name);
  ~Transform();
  void SetName(std::string name);

  json Save() override;
  void ProcessRender();
  void ProcessTick(float dt);

  void AddChild(Transform *tr);
  Error<Transform*> FindChildByName(std::string name);
  Error<Transform*> RemoveChild(Transform *tr);

  void Translate(glm::vec3 offset);
  void Scale(glm::vec3 amount);

  glm::vec3 Forward();
  glm::vec3 Backward();
  glm::vec3 Up();
  glm::vec3 Down();
  glm::vec3 Left();
  glm::vec3 Right();

  glm::mat4 GetModelMatrix();

  glm::vec3 GetGlobalPosition();
  glm::vec3 GetLocalPosition();

  glm::quat GetGlobalRotation();
  glm::quat GetLocalRotation();

  glm::vec3 GetGlobalScale();
  glm::vec3 GetLocalScale();

private:
  std::string name;
  uint64_t uid;
  glm::vec3 position;
  glm::quat rotation;
  glm::vec3 scale;
  Transform *parent;
  std::vector<Transform *> children;
  std::vector<Component*> components;
};

}
