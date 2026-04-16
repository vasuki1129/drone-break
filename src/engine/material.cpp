#include "material.h"
#include "../json/json.hpp"
#include "shader.h"
#include <fstream>
#include <iostream>
#include "engine.h"

using json = nlohmann::json;

namespace engine
{
    Material::Material(std::string path)
    {
      this->path = path;
      auto success = this->Reload();
      this->texture_path.resize(64);
      if (success) {
        valid = true;
      } else {
        valid = false;
      }
    }

    void Material::DrawEditWidget() {
      ImGui::InputText("Texture", this->texture_path.data(), 64);
    }
    bool Material::Bind(BaseUniforms base) {
      if (this->shader == nullptr) {
          this->shader = Engine()->GetAssetManager()->GetShaderOrNull(this->shader_path);
          std::cout << "Material " + this->name + " has no shader\n";
          return false;
      }
      this->texture = Engine()->GetAssetManager()->GetTextureOrNull(texture_path);
      glBindTexture(GL_TEXTURE_2D,0);
      if (this->texture != nullptr) {
        this->texture->Bind();
      } else {
        this->texture =
            Engine()->GetAssetManager()->GetTextureOrNull("default_texture");
        this->texture->Bind();

      }
      this->shader->Bind();
      this->shader->SetUniform("model", Uniform_mat4(base.model));
      this->shader->SetUniform("camera", Uniform_mat4(base.camera));
      this->shader->SetUniforms(this->uniform_set);
      return true;
    }

    bool Material::Reload() {
      std::ifstream f(path);
      uniform_set.uniforms.clear();
       json data = json::parse(f);

       name = data["name"];
       shader_path = data["shader_id"];
       if(data.contains("texture"))
           this->texture_path = data["texture"];
       this->shader = Engine()->GetAssetManager()->GetShaderOrNull(this->shader_path);
       this->texture = Engine()->GetAssetManager()->GetTextureOrNull(this->texture_path);
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
           } else if (val["value"].is_array()) {

             Uniform u = Uniform_vec3(
                 glm::vec3(val["value"][0], val["value"][1], val["value"][2]));
             uniform_set.uniforms.emplace(val["key"],u);

           }
           else
           {
               std::cout << "Unknown uniform value type: " << val["key"] << "\n";
           }
       }

       this->uniform_set.uniforms.insert_or_assign("light_pos",Uniform_vec3(glm::vec3(0.0, 0.0, 10.0)));

      return true;
    }
}
