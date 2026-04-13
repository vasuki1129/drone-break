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
  virtual ~Component();

  virtual void begin_play();
  virtual void end_play();

  virtual void render();
  virtual void tick(float dt);
  virtual void init();
  virtual void destroy();

  virtual void DrawWidget() =0;

  Transform* GetOwner();
  void SetOwner(Transform* own);

  std::string GetName();

  virtual json Save() override =0;
  virtual bool Load(json value) override =0;
  uint64_t GetUID();
  std::string name;
  std::string component_type;
  uint64_t uid;
  Transform* owner;

  void ComponentDisplay();
};

}
