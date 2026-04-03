#include "model.h"
#include "mesh.h"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <iostream>
#include "../dflib/dflib.h"
#include <filesystem>
namespace engine {

std::map<std::string, Model*> modelCache;

Model::Model(std::string path) {
  std::filesystem::path p(path);
  this->name = p.stem().c_str();
  Assimp::Importer import;
  const aiScene *scene =
    import.ReadFile(path.c_str(), aiProcess_Triangulate | aiProcess_FlipUVs);
  if(!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
  {
    std::cout << "ERROR::ASSIMP::" << import.GetErrorString() << std::endl;
    return;
  }
  this->path = path;
  auto success = ProcessNode(scene->mRootNode, scene);
  success ? valid = true : valid = false;


}
Model::~Model() {}

std::vector<Mesh *> Model::GetMeshes() {
    return meshes;
}

bool Model::ProcessNode(aiNode *node, const aiScene *scene) {
  for (unsigned int i = 0; i < node->mNumMeshes; i++) {
    aiMesh *mesh = scene->mMeshes[node->mMeshes[i]];
    auto mesh_proc = ProcessMesh(mesh,scene);

    if (mesh_proc == nullptr) {
      std::cout << "Error processing mesh in " << this->path << "\n";
    } else {
      meshes.push_back(mesh_proc);
    }
  }

  for (unsigned int i = 0; i < node->mNumChildren; i++) {
    ProcessNode(node->mChildren[i],scene);
  }

  return true;
}

Mesh* Model::ProcessMesh(aiMesh *mesh, const aiScene *scene) {
  std::vector<Vertex> vertices;
  std::vector<unsigned int> indices;
  std::vector<Texture> textures;

  for (unsigned int i = 0; i < mesh->mNumVertices; i++) {
    Vertex vertex;

    glm::vec3 vector;
    vector.x = mesh->mVertices[i].x;
    vector.y = mesh->mVertices[i].y;
    vector.z = mesh->mVertices[i].z;
    vertex.position = vector;

    vector.x = mesh->mNormals[i].x;
    vector.y = mesh->mNormals[i].y;
    vector.z = mesh->mNormals[i].z;
    vertex.normal = vector;

    if (mesh->mTextureCoords[0]) {
      glm::vec2 tc;
      tc.x = mesh->mTextureCoords[0][i].x;
      tc.y = mesh->mTextureCoords[0][i].y;
      vertex.t_coord = tc;
    } else {
      vertex.t_coord = glm::vec2(0.0f,0.0f);
    }
    vertices.push_back(vertex);
  }

  for (unsigned int i = 0; i < mesh->mNumFaces; i++) {
    aiFace face = mesh->mFaces[i];
    for (unsigned int j = 0; j < face.mNumIndices; j++) {
      indices.push_back(face.mIndices[j]);
    }
  }
  Mesh *m = new Mesh();
  m->SetVertices(vertices);
  m->SetIndices(indices);
  m->SetName(mesh->mName.C_Str());
  return m;
}


} // namespace engine
