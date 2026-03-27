#include "engine.h"
#include "opengl_renderer.h"

namespace engine {


engine_instance::engine_instance()
{
  scheme_interpreter = s7_init();
  renderer = new engine::opengl_renderer();
}

engine_instance::~engine_instance()
{
    delete renderer;
}

}
