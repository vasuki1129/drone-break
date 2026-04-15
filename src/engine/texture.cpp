#include "texture.h"
#include "../stb/stb_image.h"
#include "GL/glew.h"
#include <GL/gl.h>
#include <iostream>
namespace engine {

Texture::Texture(std::string path) {

  glGenTextures(1, &texture_handle);
  glBindTexture(GL_TEXTURE_2D, texture_handle);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  int width, height, n_channels;
  unsigned char* data = stbi_load(path.c_str(),&width,&height,&n_channels,0);
  if (data) {

    if (n_channels == 3) {

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGB,
               GL_UNSIGNED_BYTE, data);
    } else {

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA,
               GL_UNSIGNED_BYTE, data);

    }
  glGenerateMipmap(GL_TEXTURE_2D);
    valid = true;
  } else {
    std::cout << "Texture failed to load `" + path + "`\n";
    valid = false;
  }
  stbi_image_free(data);
}

unsigned int Texture::GetTextureHandle() {
  return texture_handle;
}

void Texture::Bind() {
  glBindTexture(GL_TEXTURE_2D, texture_handle);
}

Texture::~Texture() {
  glDeleteTextures(1,&this->texture_handle);
}

}
