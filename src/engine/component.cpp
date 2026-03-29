#include "component.h"
#include "util.h"

namespace engine {

void Component::render() {}
void Component::tick(float dt) {}
void Component::init() {}
void Component::destroy() {}

json Component::Save() {
  json out;
  out["name"] = this->name;
  out["uid"] = this->name;
  return out;
}

Component::Component() {
  name = "Component";
  uid = GenerateUID();
}
Component::Component(json value) {
  name = value["name"];
  uid = value["uid"];
}

}
