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
private:
  unsigned int texture_handle;
};
}
