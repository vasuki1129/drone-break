#pragma once
#include "component.h"
#include "model.h"
namespace engine {

class MeshComponent : public Component {
public:
  virtual void render() override;
  virtual void init() override;
  virtual void destroy() override;
private:
  Model* model;
};

}
