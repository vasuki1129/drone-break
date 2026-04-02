#include "editor.h"
#include "../imgui/imgui_impl_glfw.h"
#include "../imgui/imgui_impl_opengl3.h"
#include "mesh_component.h"

namespace engine::editor {

EditorInstance::EditorInstance() {
  auto c_i = engine::EngineCreateInfo {
    .game_name = "Light Editor",
    .initial_window_width = 600,
    .initial_window_height = 800
  };
  engine = engine::CreateEngine(c_i);
  engine->GetRenderer()->InitForImGui();
}

EditorInstance::~EditorInstance() {}



void HierarchyLevel(Transform *tr) {
  if (tr->GetChildren().size() == 0)
  {
    if (ImGui::Selectable(
            (tr->GetName() + "##" + std::to_string(tr->GetUID())).c_str())) {
    }
  }
  else
  {
    if (ImGui::TreeNode((tr->GetName() + "##" + std::to_string(tr->GetUID())).c_str())) {
      for (auto child : tr->GetChildren()) {
        HierarchyLevel(child);
      }
      ImGui::TreePop();
    }
  }
}


void EditorInstance::SceneHierarchy() {
  if (Transform *tr;
      (tr = engine->GetSceneLoader()->GetCurrentScene()->GetRoot()) !=
      nullptr) {
    HierarchyLevel(tr);
  }

}


void EditorInstance::AssetPanel() {
  if (ImGui::TreeNode("Models")) {

    for (auto mod : Engine()->GetAssetManager()->loaded_models) {
      if (ImGui::TreeNode(mod.first.c_str())) {

        for (auto mesh : mod.second->GetMeshes()) {
          if (ImGui::Selectable(mesh->GetName().c_str())) {

          }

        }
        ImGui::TreePop();
      }
    }
    ImGui::TreePop();
  }

}




void EditorInstance::DebugPanel()
{
  ImGui::Begin("Debug");

  if (ImGui::BeginTabBar("DebugTabs", ImGuiTabBarFlags_None))
  {
    if (ImGui::BeginTabItem("Actions")) {
      if (ImGui::Button("Add Root Child")) {
        Transform* ch = new Transform(std::string("Child"));
        engine->GetSceneLoader()->GetCurrentScene()->GetRoot()->AddChild(ch);
      }
      if (ImGui::Button("Add Root Child w Debug Mesh")) {
        Transform *ch = new Transform(std::string("Child"));
        MeshComponent* comp = new MeshComponent(std::string("MeshComponent"));
        comp->SetMesh(Engine()->GetAssetManager()->GetMeshOrNull("DefaultCube"));
        ch->AddComponent(comp);
        engine->GetSceneLoader()->GetCurrentScene()->GetRoot()->AddChild(ch);
      }
      ImGui::EndTabItem();
    }

    if (ImGui::BeginTabItem("View")) {
      SceneHierarchy();
      ImGui::EndTabItem();
    }

    if (ImGui::BeginTabItem("Assets")) {
      AssetPanel();
      ImGui::EndTabItem();
    }

    ImGui::EndTabBar();
  }
  ImGui::End();
}


void EditorInstance::Run() {
  while (!glfwWindowShouldClose(engine->GetWindow())) {
    glfwPollEvents();
    engine->GetRenderer()->StartFrame();
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    //ImGui::ShowDemoWindow();
    DebugPanel();
    int display_w, display_h;
    glfwGetFramebufferSize(engine->GetWindow(), &display_w, &display_h);
    glViewport(0, 0, display_w, display_h);
    engine->GetSceneLoader()->UpdateCurrentScene(engine->GetRenderer()->DeltaTime());
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    engine->GetRenderer()->EndFrame();
  }
}


}
