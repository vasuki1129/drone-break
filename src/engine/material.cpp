#include "material.h"
#include "../json/json.hpp"
#include "shader.h"
#include <fstream>
#include <iostream>
#include "../dflib/errorcheck.h"
#include "engine.h"

using json = nlohmann::json;

namespace engine
{
    Material::Material(std::string path)
    {
      this->path = path;
      auto err = this->Reload();

      match {
        mcase(_implErr *){
          valid = false;
          ErrTrace(err);

        },
        mcase(_implOk<bool> *) {
          valid = true;
          ErrIgnore(err);
        }
      } eval_on(err);
    }

    Error<bool> Material::Bind() {
      if (this->shader == nullptr) {
          this->shader = Engine()->GetAssetManager()->GetShaderOrNull(this->shader_path);
          return MakeErr<bool>("Material " + this->name + " has no shader");
      }
      this->shader->Bind();
      this->shader->SetUniforms(this->uniform_set);
      return MakeOk(true);
    }

    Error<bool> Material::Reload() {
       std::ifstream f(path);
       json data = json::parse(f);

       name = data["name"];
       shader_path = data["shader_id"];
       this->shader = Engine()->GetAssetManager()->GetShaderOrNull(this->shader_path);
       for(json val : data["uniforms"])
       {
           if(val["value"].is_number_integer())
           {
               Uniform u = Uniform_i(val["value"]);
               uniform_set.uniforms.emplace(val["key"],u);
           }
           else if(val["value"].is_number_float())
           {
               Uniform u = Uniform_f(val["value"]);
               uniform_set.uniforms.emplace(val["key"],u);
           }
           else
           {
               std::cout << "Unknown uniform value type: " << val["key"] << "\n";
           }
       }
      return MakeOk<bool>(true);
    }
}
