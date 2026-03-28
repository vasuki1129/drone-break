#include "shader.h"
#include "cppmatch.h"
#include <glm/ext.hpp>
#include <variant>
namespace engine {
Error Shader::SetUniform(Uniform u) {
  match {
    mcase(Uniform_i){
        auto location = glGetUniformLocation(this->shader_handle, val.key.c_str());
        if (location == -1) return Error(Err{std::string("Uniform ")+ val.key + " does not exist on shader " + this->name});
        glUniform1i(location, val.value);
    },
    mcase(Uniform_f){
      auto location =
          glGetUniformLocation(this->shader_handle, val.key.c_str());
      if (location == -1) return Error(Err{std::string("Uniform ")+ val.key + " does not exist on shader " + this->name});
      glUniform1f(location,val.value);
    },
    mcase(Uniform_d) {
      auto location =
          glGetUniformLocation(this->shader_handle, val.key.c_str());
      if (location == -1) return Error(Err{std::string("Uniform ")+ val.key + " does not exist on shader " + this->name});
      glUniform1d(location,val.value);
    },
    mcase(Uniform_mat4){
      auto location =
          glGetUniformLocation(this->shader_handle, val.key.c_str());
      if (location == -1) return Error(Err{std::string("Uniform ")+ val.key + " does not exist on shader " + this->name});
      glUniformMatrix4fv(location,1,GL_FALSE, glm::value_ptr(val.value));
    },
    mcase(Uniform_ui) {
      auto location =
          glGetUniformLocation(this->shader_handle, val.key.c_str());
      if (location == -1) return Error(Err{std::string("Uniform ")+ val.key + " does not exist on shader " + this->name});
      glUniform1ui(location,val.value);
    }
  } on(u);

  switch (glGetError()) {
    case GL_INVALID_VALUE:
    case GL_INVALID_OPERATION:
      return Error(Err{"Invalid program supplied to SetUniform"});
      break;
  }
}

Error Shader::SetUniforms(UniformList &u) {
  Error ret = Error(Ok());
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
