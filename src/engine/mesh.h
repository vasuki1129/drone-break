#pragma once
#include <stdint.h>
#include <glm/glm.hpp>
#include <GL/glew.h>
#include "errorcheck.h"
struct Vertex {
  glm::vec3 position;
  glm::vec3 normal;
  glm::vec2 t_coord;
};

namespace engine {

//the mesh class represents an instance of the given
//data on both the CPU and GPU, and the lifetime of
//the data on the GPU depends entirely on the lifetime
//of this object.  Therefore, to load and deload meshes,
//you `new` and `delete` instances of this class

//meshes are grouped into models, so the actual handling
//of that mesh memory is done in `model.cpp`
class Mesh {
public:
  Mesh();
  ~Mesh();
  void SetVertices(std::vector<Vertex> v);
  void SetIndices(std::vector<unsigned int> v);
  Error<bool> Rebuffer();
private:
  std::string name;
  uint8_t material_index;
  std::vector<Vertex> vertices;
  std::vector<unsigned int> indices;
  GLuint vertex_buffer_handle;
  GLuint index_buffer_handle;
};
}
