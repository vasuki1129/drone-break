#pragma once
#include <string>

namespace engine {


class Asset {
public:
  virtual bool IsValid();
  std::string GetName();
  void SetName(std::string name);
  std::string GetPath();
  void SetPath(std::string path);

protected:
  bool valid = false;
  std::string name = "?????";
  std::string path = "INVALID";
};



}
