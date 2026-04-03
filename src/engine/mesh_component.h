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
  void SetMesh(Mesh *mesh);
  void SetMaterial(Material* material);
  void DrawWidget() override;
  MeshComponent(std::string name);
private:
  std::string mesh_name;
  std::string material_name;
  Mesh* mesh;
  Material *material;
};

}
