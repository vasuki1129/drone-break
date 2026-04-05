#pragma once
#include "transform.h"
#include "saveable.h"
#include <string>
#include "../imgui/imgui.h"



#define FACTORY(type) engine::Component *__Get ## type()

#define FACTORY_DEF(type)                                                      \
  engine ::Component *__Get##type() {                                           \
    return (engine::Component *)(new type());                                 \
  }                                                                            \


#define FACTORY_REF(type) __Get ## type


namespace engine {

class Transform;

class Component : public Saveable {
public:
  Component();
  Component(std::string name);
  Component(json value); //load constructor
  virtual ~Component();
  virtual void render();
  virtual void tick(float dt);
  virtual void init();
  virtual void destroy();


  virtual void DrawWidget() =0;


  void SetOwner(Transform* own);

  std::string GetName();

  json Save() override;

  uint64_t GetUID();
protected:
  std::string name;
  uint64_t uid;
  Transform* owner;

  void ComponentDisplay();
};

}
