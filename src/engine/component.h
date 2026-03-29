#pragma once
#include "transform.h"
#include "saveable.h"
#include <string>
namespace engine {

class Transform;

class Component : public Saveable {
public:
  Component();
  Component(json value); //load constructor
  virtual void render();
  virtual void tick(float dt);
  virtual void init();
  virtual void destroy();

  json Save() override;

protected:
  std::string name;
  uint64_t uid;
  Transform* owner;
};

}
