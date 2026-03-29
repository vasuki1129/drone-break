#include "scene.h"

namespace engine {

void Scene::Render() {
  root->ProcessRender();
}

void Scene::Tick(float dt) {
  root->ProcessTick(dt);
}

}
