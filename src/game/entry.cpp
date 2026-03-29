#include "../engine/engine.h"

int main(int argc, char **argv) {

  engine::EngineCreateInfo create_info {
    .game_name = "hiverunner",
    .initial_window_width = 800,
    .initial_window_height = 600
  };

  engine::EngineInstance* eng = engine::CreateEngine(create_info);
  //register any additional types
  eng->Run();

  return 0;
}
