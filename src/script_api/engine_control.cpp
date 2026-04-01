#include "../s7/s7.h"
#include "../engine/engine.h"
#include <iostream>

static s7_pointer scm_print_engine_about(s7_scheme *sc, s7_pointer args) {
  std::cout << engine::Engine()->GetVersionString();
  return s7_nil(sc);
}
