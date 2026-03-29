#pragma once

namespace engine {

class Component {
public:
  virtual void render();
  virtual void tick(float dt);
  virtual void init();
  virtual void destroy();
};

}
