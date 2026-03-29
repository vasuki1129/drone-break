#pragma once
#include <vector>
#include "mesh.h"
#include "material.h"
#include "texture.h"
#include <assimp/scene.h>
#include <map>




namespace engine {
class Model {
public:
  Model(std::string path);
  ~Model();
private:
  Error<bool> ProcessNode(aiNode *node, const aiScene *scene);
  Error<Mesh*> ProcessMesh(aiMesh *mesh, const aiScene *scene);
  std::vector<Mesh*> meshes;
  std::string directory;
};

Model* GetModel(std::string path);

//this is the raw(uncached) version, dont use it, go thru the cache
Model *__LoadModel(std::string path);

}
