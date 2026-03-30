#pragma once
#include "transform.h"
#include "saveable.h"
namespace engine
{
class Scene : public Saveable {
public:
  Scene();
  Scene(json value);
  ~Scene();
  void Render();
  void Tick(float dt);
  json Save();
  Transform* GetRoot();
private:
  std::string name;
  std::string path;
  Transform* root;
  bool finalized;
};


}
