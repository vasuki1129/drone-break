#pragma once
#include "transform.h"
#include "saveable.h"
namespace engine
{
class Scene : public Saveable {
public:
  void Render();
  void Tick(float dt);
  json Save();
private:
  std::string name;
  std::string path;
  Transform* root;
};

}
