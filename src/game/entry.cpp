#include "../engine/editor.h"

int main(int argc, char **argv) {
  //auto eng = new engine::editor::EditorInstance();
  engine::EngineCreateInfo create_info{
      .game_name = "Light",
      .initial_window_width = 800,
      .initial_window_height = 600,
  };
  auto eng = new engine::editor::EditorInstance();

  //register any additional types
  eng->Run();
  delete eng;
  return 0;
}
