#pragma once
#include <string>
#include "asset.h"
namespace engine {

class Asset;

class Texture : public Asset{
public:
  Texture(std::string path);
  ~Texture();
  void Bind();

  unsigned int GetTextureHandle();

private:
  unsigned int texture_handle;
};
}
