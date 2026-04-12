#pragma once

#include "../imgui/imgui.h"
#include "engine.h"
namespace engine::editor {

class EditorInstance {
public:
  EditorInstance();
  ~EditorInstance();
  void Run();
  void DebugPanel();
  void ActionsPanel();
  void AssetPanel();
  void Inspector();
  void SceneHierarchy();
  void MenuBar();


  void TransportPanel();


  void OpenSceneLoadMenu();
  void OpenSceneSaveMenu();

  void PreferencesWindow();
  void DrawTransformGizmo();
  void SceneLoadMenu();


  void DrawGrid();
  EngineInstance* engine;

private:

  bool game_running_switch = false;

  EditorCameraComponent* editor_camera = nullptr;

  unsigned int grid_vao;
  unsigned int gizmo_vao;
  Transform *hierarchy_selected = nullptr;
  void HierarchyLevel(Transform* tr);
};

}
