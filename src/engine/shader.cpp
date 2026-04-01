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

  if (this->vao != 0) {
    glDeleteVertexArrays(1,&vao);
  }

  glGenVertexArrays(1,&this->vao);
  glBindVertexArray(this->vao);
  glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,sizeof(Vertex),(const void*)offsetof(Vertex,position));
  glVertexAttribPointer(1,3,GL_FLOAT,GL_FALSE,sizeof(Vertex),(const void*)offsetof(Vertex,normal));
  glVertexAttribPointer(2,3,GL_FLOAT,GL_FALSE,sizeof(Vertex),(const void*)offsetof(Vertex,t_coord));
  glEnableVertexAttribArray(0);
  glEnableVertexAttribArray(1);
  glEnableVertexAttribArray(2);

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

Shader::Shader(std::string path) {
  this->path = path;
  Reload();
}

Shader::~Shader()
{
  glDeleteProgram(this->shader_handle);
  this->shader_handle = 0;
}


Error<bool> Shader::SetUniform(std::string key, Uniform u) {
  Error<bool> err = (_implErr*)nullptr;

  match {
      mcase(Uniform_i) {
          auto location = glGetUniformLocation(this->shader_handle, key.c_str());
          if (location == -1)
              return MakeErr<bool>(std::string("Uniform ") + key + " does not exist on shader " + this->name);
          glUniform1i(location, val.value);
          return MakeOk<bool>(true);
      },
      mcase(Uniform_f) {
          auto location =
              glGetUniformLocation(this->shader_handle, key.c_str());
          if (location == -1)
              return MakeErr<bool>(std::string("Uniform ") + key +
                                     " does not exist on shader " + this->name);
          glUniform1f(location, val.value);
          return MakeOk<bool>(true);
      },
      mcase(Uniform_d){
          auto location =
              glGetUniformLocation(this->shader_handle, key.c_str());
          if (location == -1)
              return MakeErr<bool>(std::string("Uniform ") + key +
                                     " does not exist on shader " + this->name);
          glUniform1d(location, val.value);
          return MakeOk<bool>(true);
      },
      mcase(Uniform_mat4){
          auto location =
              glGetUniformLocation(this->shader_handle, key.c_str());
          if (location == -1)
              return MakeErr<bool>(std::string("Uniform ") + key +
                                     " does not exist on shader " + this->name);
          glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(val.value));
          return MakeOk<bool>(true);
      },
      mcase(Uniform_ui){
          auto location =
              glGetUniformLocation(this->shader_handle, key.c_str());
          if (location == -1)
              return MakeErr<bool>(std::string("Uniform ") + key + " does not exist on shader " + this->name);
          glUniform1ui(location, val.value);
          return MakeOk<bool>(true);
      }
  } assign_on(u, err);

  switch (glGetError()) {
    case GL_INVALID_VALUE:
    case GL_INVALID_OPERATION:
      ErrIgnore(err);
      return MakeErr<bool>("Invalid program supplied to SetUniform");
      break;
  }
  return err;
}

Error<bool> Shader::Bind() {
    glBindVertexArray(vao);
    glUseProgram(this->shader_handle);
    return MakeOk<bool>(true);
}

Error<bool> Shader::SetUniforms(UniformList &u) {
  for (auto uniform : u.uniforms) {
    Error<bool> e = this->SetUniform(uniform.first,uniform.second);
    if (std::holds_alternative<_implErr*>(e)) {
      return MakeErr<bool>("Error setting uniform list on shader: " + this->name, std::get<_implErr*>(e));
      break;
    }
  }
  return MakeOk<bool>(true);
}

}
