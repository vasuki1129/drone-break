#pragma once
#include <variant>
#include <string>
#include <glm/glm.hpp>
#include <GL/glew.h>
#include "errorcheck.h"

namespace engine {

struct Uniform_i {
  std::string key;
  int value;
};
struct Uniform_ui {
  std::string key;
  unsigned int value;
};
struct Uniform_f {
  std::string key;
  float value;
};
struct Uniform_d {
  std::string key;
  double value;
};
struct Uniform_mat4 {
  std::string key;
  glm::mat4 value;
};

using Uniform =
    std::variant<Uniform_i, Uniform_ui, Uniform_f, Uniform_d, Uniform_mat4>;

class UniformList {
public:
  std::vector<Uniform> uniforms;
};

class Shader {
public:
  Error<bool> SetUniforms(UniformList& u);
  Error<bool> SetUniform(Uniform u);
private:
  unsigned int shader_handle;
  std::string name;
};

};
