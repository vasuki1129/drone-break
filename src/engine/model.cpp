#include "model.h"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <iostream>
#include "cppmatch.h"


namespace engine {

std::map<std::string, Model*> modelCache;

Model::Model(std::string path) {
  Assimp::Importer import;
  const aiScene *scene =
    import.ReadFile(path.c_str(), aiProcess_Triangulate | aiProcess_FlipUVs);
  if(!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
  {
    std::cout << "ERROR::ASSIMP::" << import.GetErrorString() << std::endl;
    return;
  }
  directory = path.substr(0, path.find_last_of('/'));
  ProcessNode(scene->mRootNode, scene);
}
Model::~Model() {}

Error<bool> Model::ProcessNode(aiNode *node, const aiScene *scene) {
  for (unsigned int i = 0; i < node->mNumMeshes; i++) {
    aiMesh *mesh = scene->mMeshes[node->mMeshes[i]];
    match {
      mcase(Err) {
        std::cout << "Error processing mesh in " << this->directory << "\n";
      },
      mcase(Ok<Mesh*>) {
        meshes.push_back(val.val);
      }
    }
    on(ProcessMesh(mesh,scene));
  }

  for (unsigned int i = 0; i < node->mNumChildren; i++) {
    ProcessNode(node->mChildren[i],scene);
  }

  return Error<bool>(Ok<bool>(true));
}

Error<Mesh *> Model::ProcessMesh(aiMesh *mesh, const aiScene *scene) {
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

  return Ok<Mesh*>(m);
}

Model* __LoadModel(std::string path) {
  Model *m = new Model(path);
  return m;
}

Model* GetModel(std::string path) {
  return nullptr;
}

} // namespace engine
