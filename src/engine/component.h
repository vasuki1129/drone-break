#pragma once
#include "transform.h"
#include "saveable.h"
#include <string>
namespace engine {

class Transform;

class Component : public Saveable {
public:
  Component();
  Component(std::string name);
  Component(json value); //load constructor
  virtual void render();
  virtual void tick(float dt);
  virtual void init();
  virtual void destroy();


  virtual void DrawWidget() =0;


  void SetOwner(Transform* own);


  json Save() override;

protected:
  std::string name;
  uint64_t uid;
  Transform* owner;

  void ComponentDisplay();
};

}
