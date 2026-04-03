#include "mesh.h"
#include <GL/glew.h>

namespace engine {

bool Mesh::Draw(BaseUniforms base, Material* material) {
    glBindVertexArray(this->vertex_array_handle);

    glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer_handle);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_buffer_handle);

  {//let
    auto err = material->Bind(base);
    if (err == false) {
      std::cout << "Material for mesh " + this->name + " could not be bound\n";
      return false;
    }
  }
  //glDrawArrays(GL_TRIANGLES,0,vertices.size());
  glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
  auto err = glGetError();
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
  if (err == GL_INVALID_OPERATION) {
    std::cout << "GL_INVALID_OPERATION on mesh draw call.\n";
    return false;
  } else {
    return true;
  }
  glBindVertexArray(0);
}

bool Mesh::Rebuffer() {
  glBindVertexArray(this->vertex_array_handle);
  glBindBuffer(GL_ARRAY_BUFFER,this->vertex_buffer_handle);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->index_buffer_handle);
  glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,sizeof(Vertex),(const void*)offsetof(Vertex,position));
  glVertexAttribPointer(1,3,GL_FLOAT,GL_FALSE,sizeof(Vertex),(const void*)offsetof(Vertex,normal));
  glVertexAttribPointer(2,3,GL_FLOAT,GL_FALSE,sizeof(Vertex),(const void*)offsetof(Vertex,t_coord));
  glEnableVertexAttribArray(0);
  glEnableVertexAttribArray(1);
  glEnableVertexAttribArray(2);

  glBufferData(GL_ARRAY_BUFFER, this->vertices.size() * sizeof(Vertex),
               this->vertices.data(), GL_STATIC_DRAW);

  if (glGetError() != 0) {
    std::cout << "Failed to buffer data to vertex buffer: " +
                     std::to_string(this->vertex_buffer_handle) + " on mesh " +
                     this->name << "\n";
    return false;
  }

  glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->indices.size() * sizeof(unsigned int),
               this->indices.data(), GL_STATIC_DRAW);
  if (glGetError() != 0) {
    std::cout << "Failed to buffer data to index buffer: " +
                     std::to_string(this->index_buffer_handle) + " on mesh " +
                     this->name << "\n";
    return false;
  } else {
    return true;
  }
  glBindVertexArray(0);
}

void Mesh::SetVertices(std::vector<Vertex> v) {
  this->vertices = v;
  Rebuffer();
}

void Mesh::SetIndices(std::vector<unsigned int> v) {
  this->indices = v;
  Rebuffer();
}


Mesh::Mesh() {
  path = "inherited";
  valid = true;

  glGenVertexArrays(1,&this->vertex_array_handle);
  glBindVertexArray(this->vertex_array_handle);

  glGenBuffers(1, &this->vertex_buffer_handle);
  glGenBuffers(1, &this->index_buffer_handle);
  glBindBuffer(GL_ARRAY_BUFFER, this->vertex_buffer_handle);
  glBindBuffer(GL_ARRAY_BUFFER, this->index_buffer_handle);
  glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,sizeof(Vertex),(const void*)offsetof(Vertex,position));
  glVertexAttribPointer(1,3,GL_FLOAT,GL_FALSE,sizeof(Vertex),(const void*)offsetof(Vertex,normal));
  glVertexAttribPointer(2,3,GL_FLOAT,GL_FALSE,sizeof(Vertex),(const void*)offsetof(Vertex,t_coord));
  glEnableVertexAttribArray(0);
  glEnableVertexAttribArray(1);
  glEnableVertexAttribArray(2);
}


Mesh::~Mesh() {
  glDeleteBuffers(1, &this->vertex_buffer_handle);
  glDeleteBuffers(1, &this->index_buffer_handle);
}

}
