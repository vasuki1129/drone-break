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
  bool SetMesh(std::string mesh);
  bool SetMaterial(std::string material);
  void DrawWidget() override;
  MeshComponent(std::string name);
private:
  std::string mesh_name;
  bool mesh_valid = false;
  std::string material_name;
  bool material_valid = false;
};


FACTORY(MeshComponent);



}
