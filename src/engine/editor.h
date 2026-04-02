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
  void AssetPanel();
  void SceneHierarchy();
  EngineInstance* engine;
};

}
