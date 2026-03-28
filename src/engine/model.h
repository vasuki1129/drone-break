#pragma once
#include <vector>
#include "mesh.h"
#include "material.h"
#include "texture.h"

namespace engine {
class Model {
public:
  Model(std::string path);
  ~Model();
private:
  std::vector<Mesh *> meshes;
};
}
