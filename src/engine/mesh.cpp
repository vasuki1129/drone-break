#include "mesh.h"
#include <GL/glew.h>

namespace engine {

Error<bool> Mesh::Draw(BaseUniforms base, Material* material) {
  {//let
    auto err = material->Bind();
    match {
      mcase(_implErr *){
        ErrTrace(err);
      },
      mcase(_implOk<bool> *) {
        ErrIgnore(err);
      }
    }
    eval_on(err);
  }

  glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer_handle);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_buffer_handle);
  glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
  auto err = glGetError();
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
  if (err == GL_INVALID_OPERATION) {
    return MakeErr<bool>("GL_INVALID_OPERATION on mesh draw call.");
  } else {
    return MakeOk<bool>(true);
  }
  glBindVertexArray(0);
}

Error<bool> Mesh::Rebuffer() {
  glBindBuffer(GL_ARRAY_BUFFER,this->vertex_buffer_handle);
  glBufferData(GL_ARRAY_BUFFER, this->vertices.size() * sizeof(Vertex),
               this->vertices.data(), GL_STATIC_DRAW);
  glBindBuffer(GL_ARRAY_BUFFER, NULL);

  if (glGetError() != 0) {
    return Error<bool>(MakeErr<bool>("Failed to buffer data to vertex buffer: " +
                     std::to_string(this->vertex_buffer_handle) + " on mesh " +
                     this->name));
  }

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->index_buffer_handle);
  glBufferData(GL_ARRAY_BUFFER, this->indices.size() * sizeof(unsigned int),
               this->indices.data(), GL_STATIC_DRAW);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, NULL);
  if (glGetError() != 0) {
    return Error<bool>(MakeErr<bool>("Failed to buffer data to index buffer: " +
                     std::to_string(this->index_buffer_handle) + " on mesh " +
                     this->name));
  } else {
    return Error<bool>(MakeOk<bool>(true));
  }
}

void Mesh::SetVertices(std::vector<Vertex> v) {
  this->vertices = v;
}

void Mesh::SetIndices(std::vector<unsigned int> v) { this->indices = v; }

void Mesh::SetName(std::string name) {
    this->name = name;
}

Mesh::Mesh() {
  glGenBuffers(1, &this->vertex_buffer_handle);
  glGenBuffers(1, &this->index_buffer_handle);
}


Mesh::~Mesh() {
  glDeleteBuffers(1, &this->vertex_buffer_handle);
  glDeleteBuffers(1, &this->index_buffer_handle);
}


std::string Mesh::GetName() {
  return name;
}

}
