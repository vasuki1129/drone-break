#include "material.h"
#include "../json/json.hpp"
#include "shader.h"
#include <fstream>
#include <iostream>
#include "../dflib/errorcheck.h"


using json = nlohmann::json;

namespace engine
{
    Material::Material(std::string path)
    {
      this->path = path;
      this->Reload();
    }

    Error<bool> Material::Bind() {
      this->shader->Bind();
      this->shader->SetUniforms(this->uniform_set);
    }

    Error<bool> Material::Reload() {
       std::ifstream f(path);
       json data = json::parse(f);

       name = data["name"];
       std::string shader_name = data["shader_id"];
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
