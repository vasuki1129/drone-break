#pragma once
#include <vector>
#include <variant>
#include <string>
#include <glm/glm.hpp>
#include <GL/glew.h>
#include "../dflib/dflib.h"
#include <map>
#include "asset.h"

namespace engine {

class Asset;

struct Uniform_i {
  int value;
  Uniform_i(int v)
  {
    value = v;
  }
};
struct Uniform_ui {
  unsigned int value;
};
struct Uniform_f {
  float value;
  Uniform_f(float f)
  {
    value = f;
  }
};
struct Uniform_d {
  double value;
};
struct Uniform_mat4 {
  glm::mat4 value;
  Uniform_mat4(glm::mat4 m) {
    value = m;
  }
};

struct Uniform_vec3 {
  glm::vec3 value;
  Uniform_vec3(glm::vec3 v) {
    value = v;
  }
};

using Uniform =
    std::variant<Uniform_vec3,Uniform_i, Uniform_ui, Uniform_f, Uniform_d, Uniform_mat4>;

class UniformList {
public:
  std::map<std::string,Uniform> uniforms;
};


//the shader is going to hold the VAO, so each shader
//can have its own vertex attrib set, and they can
//be set up once, at shader creation
class Shader : public Asset{
public:
  Shader(std::string path);
  ~Shader();
  bool SetUniforms(UniformList& u);
  bool SetUniform(std::string key, Uniform u);
  void Reload();
  bool Bind();
private:
  unsigned int shader_handle = 0;
  unsigned int vao = 0;
  std::string vertex_src_str;
  std::string fragment_src_str;
};

};
