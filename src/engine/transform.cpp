#include "transform.h"
#include <glm/gtc/quaternion.hpp>

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

void Transform::Translate(glm::vec3 offset) {
  this->position += offset;
}
void Transform::Scale(glm::vec3 amount) {
  this->scale *= amount;
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
glm::vec3 Transform::Left() { return -Right(); }


glm::mat4 Transform::GetModelMatrix() {
  glm::mat4 scl = glm::scale(glm::mat4(1.0f),GetGlobalScale());
  glm::mat4 rot = glm::mat4_cast(GetGlobalRotation());
  glm::mat4 trns = glm::translate(glm::mat4(1.0f),GetGlobalPosition());
  return trns * rot * scl;
}

glm::vec3 Transform::GetGlobalPosition() {
  glm::vec3 tot(0.0f, 0.0f, 0.0f);
  Transform *tr = this;
  while (tr != nullptr) {
    tot += tr->GetLocalPosition();
    tr = tr->parent;
  }
  return tot;
}

glm::vec3 Transform::GetLocalPosition() {
  return position;
}

glm::quat Transform::GetGlobalRotation() {
  glm::quat rot = glm::identity<glm::quat>();
  Transform *tr = this;
  while (tr != nullptr) {
    rot = tr->GetLocalRotation() * rot;
    tr = tr->parent;
  }
  return rot;
}

glm::quat Transform::GetLocalRotation() {
  return rotation;
}

glm::vec3 Transform::GetGlobalScale() {
  glm::vec3 tot(1.0f, 1.0f, 1.0f);
  Transform *tr = this;
  while (tr != nullptr) {
    tot *= tr->GetLocalPosition();
    tr = tr->parent;
  }
  return tot;
}


glm::vec3 Transform::GetLocalScale() {
  return scale;
}

}
