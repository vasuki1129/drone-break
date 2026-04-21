#pragma once
#include "../json/json.hpp"
#include <map>

#include "model.h"
#include "material.h"
#include "texture.h"
#include "shader.h"
#include "scene.h"
#include "sound.h"

using json = nlohmann::json;

namespace engine {


class AssetManager {
public:
  void Rescan();
  Mesh *GetMeshOrNull(std::string key);

  Material* GetMaterialOrNull(std::string key);
  Sound* GetSoundOrNull(std::string key);
  Shader* GetShaderOrNull(std::string key);
  Texture* GetTextureOrNull(std::string key);

  std::map<std::string, Model*> loaded_models;            //.fbx
  std::map<std::string, Mesh*> loaded_meshes;
  std::map<std::string, Material*> loaded_materials;      //.mtl
  std::map<std::string, Texture*> loaded_textures;        //.png
  std::map<std::string, Shader *> loaded_shaders;         //.shd
  std::map<std::string, Sound*> loaded_sounds;
private:
  void ProcessModel(std::filesystem::path pth);
  void ProcessMaterial(std::filesystem::path pth);
  void ProcessShader(std::filesystem::path pth);
  void ProcessTexture(std::filesystem::path pth);
  void ProcessSound(std::filesystem::path pth);
};

}
