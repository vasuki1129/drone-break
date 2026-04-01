#pragma once
#include "component.h"
#include "mesh.h"
#include "material.h"
namespace engine {

class MeshComponent : public Component {
public:
  virtual void render() override;
  virtual void init() override;
  virtual void destroy() override;
  void SetMesh(Mesh* mesh);
private:
  Mesh* mesh;
  Material *material;
};

}
