#pragma once
#include "shader.h"

namespace engine {
    //we hold the uniform sets for each given material in memory
    //and they are automatically uploaded, so to change a uniform,
    //change the uniform list on the material and it will automatically
    //propagate to the gpu
    class Material
    {
    public:
        Material(std::string path);
    private:
        std::string name;
        std::string path;
        Shader* shader;
        UniformList uniform_set;
    };
};
