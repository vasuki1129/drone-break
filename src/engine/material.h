#pragma once
#include "texture.h"
#include "shader.h"
#include "asset.h"
#include "gl_util.h"

namespace engine {

  class Shader;
  class Asset;

    //we hold the uniform sets for each given material in memory
    //and they are automatically uploaded, so to change a uniform,
    //change the uniform list on the material and it will automatically
    //propagate to the gpu
    class Material : public Asset
    {
    public:
        Material(std::string path);
        bool Reload();
        bool Bind(BaseUniforms base);
        void DrawEditWidget();
      private:
        std::string texture_path;
        std::string shader_path;
        Shader* shader;
        Texture* texture;
        UniformList uniform_set;
    };
};
