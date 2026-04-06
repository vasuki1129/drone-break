#include "screen_shader.h"







namespace engine {


float quad_data[] = {
    -1.0f, -1.0f, 0.0f,
    -1.0f, 1.0f, 0.0f,
    1.0f, 1.0f, 0.0f,

    -1.0f, -1.0f, 0.0f,
    1.0f, 1.0f, 0.0f,
    1.0f, -1.0f, 0.0f
};

void ScreenShader::Apply() {

}

ScreenShader::ScreenShader(std::string path) : Shader(path) {

}

ScreenShader::~ScreenShader() {


}
  
}
