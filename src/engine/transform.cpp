#include "transform.h"

namespace engine {

void Transform::ProcessRender() {
  for (auto comp : components) {
    comp->render();
  }
  for (auto child : children) {
    child->ProcessRender();
  }
}

void Transform::ProcessTick(float dt) {
  for (auto comp : components) {
    comp->tick(dt);
  }
  for (auto child : children) {
    child->ProcessTick(dt);
  }
}

glm::vec3 Transform::Forward() {
  return glm::vec3(0.0f,0.0f,1.0f) * this->rotation;
}
glm::vec3 Transform::Backward() {
  return -Forward();
}
glm::vec3 Transform::Up() {
  return glm::vec3(0.0f, 1.0f, 0.0f) * this->rotation;
}
glm::vec3 Transform::Down() {
  return -Up();
}
glm::vec3 Transform::Right() {
  return glm::vec3(1.0f,0.0f,0.0f) * this->rotation;
}
glm::vec3 Transform::Left() {
  return -Right();
}





}
