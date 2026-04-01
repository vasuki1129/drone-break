#pragma once
#include "../json/json.hpp"
#include <map>

#include "model.h"
#include "material.h"
#include "texture.h"
#include "shader.h"
#include "scene.h"

using json = nlohmann::json;

namespace engine {

class Asset {
public:
  virtual Error<bool> Load();
  virtual void Destroy();

protected:
  std::string path;
};

class AssetManager {
public:
  void Rescan();

private:
  std::map<std::string, Model*> loaded_models;            //.blend
  std::map<std::string, Mesh*> loaded_meshes;
  std::map<std::string, Material*> loaded_materials;      //.mtl
  std::map<std::string, Texture*> loaded_textures;        //.png
  std::map<std::string, Shader *> loaded_shaders;         //.shd
  std::map<std::string, Scene*> loaded_scenes;            //.scn

};

}
