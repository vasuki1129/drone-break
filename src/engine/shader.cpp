#include "shader.h"
#include "cppmatch.h"
#include <glm/ext.hpp>
#include <variant>
#include <fstream>
#include "../json/json.hpp"

using json = nlohmann::json;

namespace engine {


Shader::Shader(std::string path)
{
  std::ifstream f(path);
  json value = json::parse(f);
  this->name = value["name"];
  std::string vertex_src;
  for(std::string line : value["vertex_shader"])
  {
    vertex_src += line + "\n";
  }

  std::string fragment_src;
  for(std::string line : value["fragment_shader"])
  {
    fragment_src += line + "\n";
  }

  const char* vert_src = vertex_src.c_str();
  const char* frag_src = fragment_src.c_str();

  unsigned int vertex_shader;
  vertex_shader = glCreateShader(GL_VERTEX_SHADER);
  glShaderSource(vertex_shader, 1, &vert_src,NULL);
  glCompileShader(vertex_shader);

  int success;
  char infoLog[512];
  glGetShaderiv(vertex_shader, GL_COMPILE_STATUS, &success);

  if(!success)
  {
    glGetShaderInfoLog(vertex_shader, 512, NULL, infoLog);
    std::cout << "Error: Vertex shader compilation failed\n" << infoLog;
  }

  unsigned int fragment_shader;
  fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
  glShaderSource(fragment_shader, 1, &frag_src,NULL);
  glCompileShader(fragment_shader);

  glGetShaderiv(fragment_shader, GL_COMPILE_STATUS, &success);

  if(!success)
  {
    glGetShaderInfoLog(fragment_shader, 512, NULL, infoLog);
    std::cout << "Error: Fragment shader compilation failed\n" << infoLog;
  }

  unsigned int shader_hnd;
  shader_hnd = glCreateProgram();
  glAttachShader(shader_hnd, vertex_shader);
  glAttachShader(shader_hnd, fragment_shader);
  glLinkProgram(shader_hnd);

  glGetProgramiv(shader_hnd, GL_LINK_STATUS, &success);

  if(!success)
  {
    glGetProgramInfoLog(shader_hnd, 512, NULL, infoLog);
    std::cout << "Error: Shader link failed\n" << infoLog;
  }
  this->shader_handle = shader_hnd;

  glDeleteShader(vertex_shader);
  glDeleteShader(fragment_shader);
}

Shader::~Shader()
{
  glDeleteProgram(this->shader_handle);
}


Error<bool> Shader::SetUniform(Uniform u) {
  match {
    mcase(Uniform_i){
        auto location = glGetUniformLocation(this->shader_handle, val.key.c_str());
        if (location == -1) return Error<bool>(Err(std::string("Uniform ")+ val.key + " does not exist on shader " + this->name));
        glUniform1i(location, val.value);
    },
    mcase(Uniform_f){
      auto location =
          glGetUniformLocation(this->shader_handle, val.key.c_str());
      if (location == -1) return Error<bool>(Err(std::string("Uniform ")+ val.key + " does not exist on shader " + this->name));
      glUniform1f(location,val.value);
    },
    mcase(Uniform_d) {
      auto location =
          glGetUniformLocation(this->shader_handle, val.key.c_str());
      if (location == -1) return Error<bool>(Err(std::string("Uniform ")+ val.key + " does not exist on shader " + this->name));
      glUniform1d(location,val.value);
    },
    mcase(Uniform_mat4){
      auto location =
          glGetUniformLocation(this->shader_handle, val.key.c_str());
      if (location == -1) return Error<bool>(Err(std::string("Uniform ")+ val.key + " does not exist on shader " + this->name));
      glUniformMatrix4fv(location,1,GL_FALSE, glm::value_ptr(val.value));
    },
    mcase(Uniform_ui) {
      auto location =
          glGetUniformLocation(this->shader_handle, val.key.c_str());
      if (location == -1) return Error<bool>(Err(std::string("Uniform ")+ val.key + " does not exist on shader " + this->name));
      glUniform1ui(location,val.value);
    }
  } on(u);

  switch (glGetError()) {
    case GL_INVALID_VALUE:
    case GL_INVALID_OPERATION:
      return Error<bool>(Err("Invalid program supplied to SetUniform"));
      break;
  }
  return Error<bool>(Ok<bool>(true));
}

Error<bool> Shader::SetUniforms(UniformList &u) {
  Error<bool> ret = Error<bool>(Ok<bool>(true));
  for (auto uniform : u.uniforms) {
    Error e = this->SetUniform(uniform);
    if (std::holds_alternative<Err>(e)) {
      ret = e;
      break;
    }
  }
  return ret;
}

}
