#include "../engine/editor.h"
#include "test_component.h"
#include "player_component.h"
#include "collision_component.h"


int main(int argc, char **argv) {
  //auto eng = new engine::editor::EditorInstance();
  engine::EngineCreateInfo create_info{
      .game_name = "Light",
      .initial_window_width = 800,
      .initial_window_height = 600,
  };
  auto eng = new engine::editor::EditorInstance();

  //register our types with the engine
  engine::Engine()->RegisterComponent("RotationComponent",FACTORY_REF(TestComponent));
  engine::Engine()->RegisterComponent("PlayerComponent",FACTORY_REF(PlayerComponent));
  engine::Engine()->RegisterComponent("CollisionComponent",
                                      engine::__GetCollisionComponent);
  eng->Run();
  delete eng;
  return 0;
}
