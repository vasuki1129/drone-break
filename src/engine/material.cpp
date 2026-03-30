#include "material.h"
#include "../json/json.hpp"
#include <fstream>
#include <iostream>

using json = nlohmann::json;

namespace engine
{
    Material::Material(std::string path)
    {
       std::ifstream f(path);
       json data = json::parse(f);

       name = data["name"];
       this->path = path;
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
    }
}
