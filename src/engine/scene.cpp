#include "scene.h"

namespace engine {

void Scene::Render() {
  root->ProcessRender();
}

void Scene::Tick(float dt) {
  root->ProcessTick(dt);
}

Scene::Scene() {
  root = new Transform(std::string("Root"));
}

Scene::~Scene() {
  delete root;
}

Scene::Scene(json value) {
  name = value["name"];
  root = new Transform(value["root"]);
}

}
