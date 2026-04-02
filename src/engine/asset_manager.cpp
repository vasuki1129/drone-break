#include "asset_manager.h"
#include "engine.h"

namespace engine {


Error<Shader *> AssetManager::GetShader(std::string key) {
  if (loaded_shaders.find(key) != loaded_shaders.end()) {
    return MakeOk(loaded_shaders.at(key));
  } else {
    return MakeErr<Shader*>("Shader `" + key + "` not found");
  }
}

Shader *AssetManager::GetShaderOrNull(std::string key) {
  auto err = GetShader(key);
  Shader *out = nullptr;
  match {
    mcase(_implErr *){
      ErrTrace(err);

    },
    mcase(_implOk<Shader *> *) {
      out = val->val;
      ErrIgnore(err);
    }
  } eval_on(err);
  return out;
}


Error<Material *> AssetManager::GetMaterial(std::string key) {
  if (loaded_materials.find(key) != loaded_materials.end()) {
    return MakeOk(loaded_materials.at(key));
  } else {
    return MakeErr<Material*>("Material `" + key + "` not found");
  }
}

Material *AssetManager::GetMaterialOrNull(std::string key) {
  auto err = GetMaterial(key);
  Material *out = nullptr;
  match {
    mcase(_implErr *){
      ErrTrace(err);
    },
    mcase(_implOk<Material *> *) {
      out = val->val;
      ErrIgnore(err);
    }
  } eval_on(err);
  return out;
}

Mesh* AssetManager::GetMeshOrNull(std::string key) {
  auto err = Engine()->GetAssetManager()->GetMesh("DefaultCube");
  Mesh* out = nullptr;
  match {
    mcase(_implErr *){
      ErrTrace(err);
    },
    mcase(_implOk<Mesh*>*) {
      out = val->val;
      ErrIgnore(err);
    }
  }
  eval_on(err);
  return out;
}

Error<Mesh *> AssetManager::GetMesh(std::string key) {
  if (loaded_meshes.find(key) != loaded_meshes.end()) {
    return MakeOk(loaded_meshes.at(key));
  } else {
    return MakeErr<Mesh*>("Mesh `" + key + "` not found");
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

  for (const auto &dir_entry :
       std::filesystem::recursive_directory_iterator("assets")) {
    if (!dir_entry.is_directory()) {
      std::cout << "found asset: " + dir_entry.path().string() + "\n";
      if (dir_entry.path().extension() == ".fbx") {
        ProcessModel(dir_entry.path());
      } else if (dir_entry.path().extension() == ".mtl") {
        ProcessMaterial(dir_entry.path());
      } else if (dir_entry.path().extension() == ".png") {
        ProcessTexture(dir_entry.path());
      } else if (dir_entry.path().extension() == ".shd") {
        ProcessShader(dir_entry.path());
      }
    }
  }
}

void AssetManager::ProcessModel(std::filesystem::path pth) {
  Model *m = new Model(pth.string());
  if (m->IsValid()) {
    loaded_models.emplace(pth.stem().string(), m);
    for (auto mesh : m->GetMeshes()) {
      loaded_meshes.emplace(pth.stem().string() + "." + mesh->GetName(),mesh);
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
  if (tex->IsValid()) {
    loaded_textures.emplace(pth.stem().string(), tex);
  } else {
    std::cout << pth.string() << " failed to load";
    delete tex;
  }

}





}
