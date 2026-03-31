#pragma once
#include <vector>
#include <variant>
#include <string>
#include <glm/glm.hpp>
#include <GL/glew.h>
#include "../dflib/dflib.h"
#include <map>
namespace engine {

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
};

using Uniform =
    std::variant<Uniform_i, Uniform_ui, Uniform_f, Uniform_d, Uniform_mat4>;

class UniformList {
public:
  std::map<std::string,Uniform> uniforms;
};




//the shader is going to hold the VAO, so each shader
//can have its own vertex attrib set, and they can
//be set up once, at shader creation
class Shader {
public:
  Shader(std::string path);
  ~Shader();
  Error<bool> SetUniforms(UniformList& u);
  Error<bool> SetUniform(std::string key, Uniform u);
  void Reload();
  Error<bool> Bind();
private:
  unsigned int shader_handle = 0;
  unsigned int vao = 0;
  std::string name;
  std::string vertex_src_str;
  std::string fragment_src_str;
  std::string path;
};

};
