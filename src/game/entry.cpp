#include "../engine/editor.h"
#include "test_component.h"
#include "player_component.h"
#include "collision_component.h"
#include "enemy_component.h"
#include "game_manager.h"
#include "menu_bgscroller.h"
#include "menu_shipcontroller.h"
#include "trigger_component.h"

int main(int argc, char **argv) {

  if ((argc == 2 )&& (strcmp(argv[1], "-editor") == 0)) {
    engine::EngineCreateInfo create_info{
    .game_name = "Light", .initial_window_width = 800,
    .initial_window_height = 600, .startup_scene = "assets/levels/f1.scn"
  };
    auto eng = new engine::editor::EditorInstance();
    //auto eng = engine::editor::EditorInstance(create_info);

    //register our types with the engine
    engine::Engine()->RegisterComponent("RotationComponent",FACTORY_REF(TestComponent));
    engine::Engine()->RegisterComponent("PlayerComponent",FACTORY_REF(PlayerComponent));
    engine::Engine()->RegisterComponent("CollisionComponent",
                                        engine::__GetCollisionComponent);

    engine::Engine()->RegisterComponent("EnemyComponent",FACTORY_REF(EnemyComponent));
    engine::Engine()->RegisterComponent("GameManagerComponent",
                                        FACTORY_REF(GameManagerComponent));

    engine::Engine()->RegisterComponent("MenuBackgroundScroll",
                                        FACTORY_REF(MenuBackgroundScroll));
    engine::Engine()->RegisterComponent("MenuShipController",FACTORY_REF(MenuShipController));
    engine::Engine()->RegisterComponent("TriggerComponent",engine::__GetTriggerComponent);
    eng->Run();
    delete eng;
  } else {

    engine::EngineCreateInfo create_info{
    .game_name = "Light", .initial_window_width = 800,
    .initial_window_height = 600, .startup_scene = "assets/levels/menu.scn"
  };
    //auto eng = new engine::editor::EditorInstance();
    auto eng = engine::CreateEngine(create_info);

    //register our types with the engine
    engine::Engine()->RegisterComponent("RotationComponent",FACTORY_REF(TestComponent));
    engine::Engine()->RegisterComponent("PlayerComponent",FACTORY_REF(PlayerComponent));
    engine::Engine()->RegisterComponent("CollisionComponent",
                                        engine::__GetCollisionComponent);

    engine::Engine()->RegisterComponent("EnemyComponent",FACTORY_REF(EnemyComponent));
    engine::Engine()->RegisterComponent("MenuBackgroundScroll",
                                        FACTORY_REF(MenuBackgroundScroll));

    engine::Engine()->RegisterComponent("GameManagerComponent",
                                        FACTORY_REF(GameManagerComponent));
    engine::Engine()->RegisterComponent("MenuShipController",FACTORY_REF(MenuShipController));
    engine::Engine()->RegisterComponent("TriggerComponent",engine::__GetTriggerComponent);
    eng->Run();
    delete eng;
  }
}
