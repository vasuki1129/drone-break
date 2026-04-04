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

  EngineInstance* engine;
};

}
