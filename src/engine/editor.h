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
  void PreferencesWindow();
  void DrawTransformGizmo();

  void DrawGrid();
  EngineInstance* engine;

private:
  unsigned int grid_vao;
  unsigned int gizmo_vao;
  Transform *hierarchy_selected = nullptr;
  void HierarchyLevel(Transform* tr);
};

}
