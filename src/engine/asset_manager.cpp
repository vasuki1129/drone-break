#include "asset_manager.h"
#include "engine.h"
#include <filesystem>

namespace engine {

std::string trim_str(std::string in) {
  std::string nk = "";
  int ind = 0;
  while (in[ind] != '\0') {
    nk += in[ind];
    ind++;
  }
  return nk;
}

Sound *AssetManager::GetSoundOrNull(std::string key) {
  std::string nk = trim_str(key);
  if (loaded_sounds.find(nk) != loaded_sounds.end()) {
    return loaded_sounds.at(nk);
  } else {
    return nullptr;
  }
}

Texture *AssetManager::GetTextureOrNull(std::string key) {
  std::string nk = trim_str(key);
  if (loaded_textures.find(nk) != loaded_textures.end()) {
    return loaded_textures.at(nk);
  } else {
    return nullptr;
  }
}


Shader* AssetManager::GetShaderOrNull(std::string key) {

  std::string nk = trim_str(key);

  if (loaded_shaders.find(nk) != loaded_shaders.end()) {
    return loaded_shaders.at(nk);
  } else {
    //std::cout << "Shader `" + nk + "` not found" << "\n";
    return nullptr;
  }
}

Material *AssetManager::GetMaterialOrNull(std::string key) {
  std::string nk = trim_str(key);
  if (loaded_materials.find(nk) != loaded_materials.end()) {
    return loaded_materials.at(nk);
  } else {
    return nullptr;
  }
}

Mesh *AssetManager::GetMeshOrNull(std::string key) {
  std::string nk = trim_str(key);

  if (loaded_meshes.find(nk) != loaded_meshes.end()) {
    return loaded_meshes[nk];
  } else {
    //std::cout <<"Mesh `" + key + "` not found"<<"\n";
    return nullptr;
  }
}

void AssetManager::Rescan() {
  for (auto model : loaded_models) {
    delete model.second;
  }
  loaded_models.clear();
  loaded_meshes.clear();//dealloc on models will free meshes

  for (auto material : loaded_materials) {
    delete material.second;
  }
  loaded_materials.clear();

  for (auto texture : loaded_textures) {
    delete texture.second;
  }
  loaded_textures.clear();

  for (auto shader : loaded_shaders) {
    delete shader.second;
  }
  loaded_shaders.clear();

  //then we're gonna look in the `assets` folder for files matching
  //certain extensions

  std::vector<std::filesystem::directory_entry> models_ls;
  std::vector<std::filesystem::directory_entry> materials_ls;
  std::vector<std::filesystem::directory_entry> textures_ls;
  std::vector<std::filesystem::directory_entry> shaders_ls;
  std::vector<std::filesystem::directory_entry> sounds_ls;

  for (const auto &dir_entry :
       std::filesystem::recursive_directory_iterator("assets")) {
    if (!dir_entry.is_directory()) {
      std::cout << "found asset: " + dir_entry.path().string() + "\n";
      if (dir_entry.path().extension() == ".fbx") {
        models_ls.push_back(dir_entry);
      } else if (dir_entry.path().extension() == ".mtl") {
        materials_ls.push_back(dir_entry);
      } else if (dir_entry.path().extension() == ".png") {
        textures_ls.push_back(dir_entry);
      } else if (dir_entry.path().extension() == ".shd") {
        shaders_ls.push_back(dir_entry);
      } else if (dir_entry.path().extension() == ".mp3") {
        sounds_ls.push_back(dir_entry);
      }
    }
  }

  for (auto entry : models_ls) {
    ProcessModel(entry.path());
  }
  for (auto entry : shaders_ls) {
    ProcessShader(entry.path());
  }
  for (auto entry : textures_ls) {
    ProcessTexture(entry.path());
  }
  for (auto entry : materials_ls) {
    ProcessMaterial(entry.path());
  }
  for (auto entry : sounds_ls) {
    ProcessSound(entry.path());
  }



}

void AssetManager::ProcessModel(std::filesystem::path pth) {
  Model *m = new Model(pth.string());
  if (m->IsValid()) {
    loaded_models.emplace(pth.stem().string(), m);
    for (auto mesh : m->GetMeshes()) {
      loaded_meshes.emplace(pth.stem().string() + "." + mesh->GetName(), mesh);
      std::cout << "added mesh: "+ pth.stem().string()+"."+mesh->GetName() << "\n";
    }
  } else {
    std::cout << pth.string() << " failed to load";
    delete m;
  }
}

void AssetManager::ProcessMaterial(std::filesystem::path pth) {
  Material *m = new Material(pth.string());
  if (m->IsValid()) {
    loaded_materials.emplace(pth.stem().string(), m);
  } else {
    std::cout << pth.string() << " failed to load";
    delete m;
  }
}

void AssetManager::ProcessShader(std::filesystem::path pth) {
  Shader *sh = new Shader(pth.string());
  if (sh->IsValid()) {
    loaded_shaders.emplace(pth.stem().string(), sh);
  } else {
    std::cout << pth.string() << " failed to load";
    delete sh;
  }
}

void AssetManager::ProcessTexture(std::filesystem::path pth) {
  Texture *tex = new Texture(pth.string());
  tex->SetName(pth.stem().string());
  tex->SetPath(pth.string());
  if (tex->IsValid()) {
    loaded_textures.emplace(pth.stem().string(), tex);
  } else {
    std::cout << pth.string() << " failed to load";
    delete tex;
  }
}

void AssetManager::ProcessSound(std::filesystem::path pth) {
  Sound *sound = new Sound(pth.string());
  sound->SetName(pth.stem().string());
  sound->SetPath(pth.string());
  if (sound->IsValid()) {
    loaded_sounds[sound->GetName()] = sound;
    std::cout << "loaded sound: " << sound->GetName();
  }
}

}
