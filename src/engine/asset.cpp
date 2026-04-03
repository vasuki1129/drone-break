#include "asset.h"

namespace engine {


void Asset::SetName(std::string name) {
  this->name = name;

}

std::string Asset::GetName() {
  return this->name;
}

bool Asset::IsValid() {
  return valid;
}

void Asset::SetPath(std::string path) {
  this->path = path;
}

std::string Asset::GetPath() {
  return path;
}

}
