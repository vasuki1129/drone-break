#pragma once

namespace engine::editor {

class Gizmo {
public:
  Gizmo();
  virtual void draw()=0;
protected:
  unsigned int vao;
  unsigned int vbo;
};

}
