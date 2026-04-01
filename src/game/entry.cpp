#include "../engine/editor.h"

int main(int argc, char **argv) {
  auto eng = new engine::editor::EditorInstance();
  //register any additional types
  eng->Run();
  return 0;
}
