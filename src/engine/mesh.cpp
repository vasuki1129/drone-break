#include "mesh.h"
#include <GL/glew.h>
namespace engine {

Error<bool> Mesh::Rebuffer() {
  glBindBuffer(GL_ARRAY_BUFFER,this->vertex_buffer_handle);
  glBufferData(GL_ARRAY_BUFFER, this->vertices.size() * sizeof(Vertex),
               this->vertices.data(), GL_STATIC_DRAW);
  glBindBuffer(GL_ARRAY_BUFFER, NULL);

  if (glGetError() != 0) {
    return Error<bool>(Err("Failed to buffer data to vertex buffer: " +
                     std::to_string(this->vertex_buffer_handle) + " on mesh " +
                     this->name));
  }

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->index_buffer_handle);
  glBufferData(GL_ARRAY_BUFFER, this->indices.size() * sizeof(unsigned int),
               this->indices.data(), GL_STATIC_DRAW);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, NULL);
  if (glGetError() != 0) {
    return Error<bool>(Err("Failed to buffer data to index buffer: " +
                     std::to_string(this->index_buffer_handle) + " on mesh " +
                     this->name));
  } else {
    return Error<bool>(Ok<bool>(true));
  }
}

void Mesh::SetVertices(std::vector<Vertex> v) {


}
void Mesh::SetIndices(std::vector<unsigned int> v) {


}



Mesh::Mesh() {
  glGenBuffers(1, &this->vertex_buffer_handle);
  glGenBuffers(1, &this->index_buffer_handle);
}

Mesh::~Mesh() {
  glDeleteBuffers(1, &this->vertex_buffer_handle);
  glDeleteBuffers(1, &this->index_buffer_handle);
}




}
