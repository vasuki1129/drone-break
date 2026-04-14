#include "shader.h"
#include "../dflib/dflib.h"
#include <glm/ext.hpp>
#include <variant>
#include <fstream>
#include "../json/json.hpp"
#include "opengl_renderer.h"

using json = nlohmann::json;

namespace engine {

void Shader::Reload() {

  std::ifstream f(path);
  json value = json::parse(f);
  this->name = value["name"];
  this->vertex_src_str.clear();
  for(std::string line : value["vertex_shader"])
  {
    vertex_src_str += line + "\n";
  }

  this->fragment_src_str.clear();
  for(std::string line : value["fragment_shader"])
  {
    fragment_src_str += line + "\n";
  }

  const char* vert_src = vertex_src_str.c_str();
  const char* frag_src = fragment_src_str.c_str();

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
    valid = false;
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
    valid = false;
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
    valid = false;
    glDeleteProgram(shader_hnd);
  }
  this->shader_handle = shader_hnd;
  this->valid = true;
  glDeleteShader(vertex_shader);
  glDeleteShader(fragment_shader);
}


Shader::Shader(std::string path) {
  this->path = path;

  Reload();
}

Shader::~Shader()
{
  glDeleteProgram(this->shader_handle);
  this->shader_handle = 0;
}


bool Shader::SetUniform(std::string key, Uniform u) {
  bool err;

  match {
    mcase(Uniform_vec3) {

          auto location = glGetUniformLocation(this->shader_handle, key.c_str());
          if (location == -1) {
            //std::cout << std::string("Uniform ") + key + " does not exist on shader " + this->name << "\n";
            return false;
          }
          glUniform3fv(location,1, glm::value_ptr(val.value));
          return true;

    },
      mcase(Uniform_i) {
          auto location = glGetUniformLocation(this->shader_handle, key.c_str());
          if (location == -1) {
            //std::cout << std::string("Uniform ") + key + " does not exist on shader " + this->name << "\n";
            return false;
          }
          glUniform1i(location, val.value);
          return true;
      },
      mcase(Uniform_f) {
          auto location =
              glGetUniformLocation(this->shader_handle, key.c_str());
          if (location == -1) {
            //std::cout << std::string("Uniform ") + key + " does not exist on shader " + this->name + "\n";
            return false;
          }
          glUniform1f(location, val.value);
          return true;
      },
      mcase(Uniform_d){
          auto location =
              glGetUniformLocation(this->shader_handle, key.c_str());
          if (location == -1) {
            //std::cout << std::string("Uniform ") + key +
            //                         " does not exist on shader " + this->name << "\n";

            return false;
          }
            glUniform1d(location, val.value);
          return true;
      },
      mcase(Uniform_mat4){
          auto location =
              glGetUniformLocation(this->shader_handle, key.c_str());
          if (location == -1) {
            //std::cout << std::string("Uniform ") + key +
            //                         " does not exist on shader " + this->name << "\n";
            return false;
          }
            glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(val.value));
          return true;
      },
      mcase(Uniform_ui){
          auto location =
              glGetUniformLocation(this->shader_handle, key.c_str());
          if (location == -1) {
            //std::cout << std::string("Uniform ") + key + " does not exist on shader " + this->name << "\n";
            return false;

          }
          glUniform1ui(location, val.value);
          return true;
      }
  } assign_on(u, err);

  switch (glGetError()) {
    case GL_INVALID_VALUE:
    case GL_INVALID_OPERATION:
      return false;
      break;
  }
  return err;
}

bool Shader::Bind() {
  if (!this->valid) {
      std::cout << "Attempt to bind invalid shader "+ this->name << "\n";
      return false;
    }
    glUseProgram(this->shader_handle);
    return true;
}

bool Shader::SetUniforms(UniformList &u) {
  for (auto uniform : u.uniforms) {
    auto e = this->SetUniform(uniform.first,uniform.second);
    if (!e) {
      std::cout << "Error setting uniform list on shader: " + this->name << "\n";
      return false;
      break;
    }
  }
  return true;
}

}
