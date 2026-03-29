#pragma once
#include "transform.h"
namespace engine
{
class Scene {
public:
  void Render();
  void Tick(float dt);
private:
  Transform* root;
};

}
