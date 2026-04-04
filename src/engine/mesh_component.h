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
  void SetMesh(std::string mesh);
  void SetMaterial(std::string material);
  void DrawWidget() override;
  MeshComponent(std::string name);
private:
  std::string mesh_name;
  std::string material_name;
};

}
