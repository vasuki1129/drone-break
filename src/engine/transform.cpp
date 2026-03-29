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

}
