#include "editor.h"
#include "../imgui/imgui.h"
#include "../imgui/imgui_impl_glfw.h"
#include "../imgui/imgui_impl_opengl3.h"
#include "mesh_component.h"
#include "gui_util.h"

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

static Transform *hierarchy_selected = nullptr;

void HierarchyLevel(Transform *tr) {
  if(tr == nullptr) return;
  if (tr->GetChildren().size() == 0)
  {
    if (ImGui::TreeNodeEx((tr->GetName() + "##" + std::to_string(tr->GetUID())).c_str(),ImGuiTreeNodeFlags_Leaf | ((tr == hierarchy_selected) ? ImGuiTreeNodeFlags_Selected : 0))) {
      ImGui::TreePop();
    }
    if (ImGui::IsItemClicked()) {
      hierarchy_selected = tr;
    }
  }
  else
  {
    if (ImGui::TreeNodeEx((tr->GetName() + "##" + std::to_string(tr->GetUID())).c_str(),ImGuiTreeNodeFlags_OpenOnDoubleClick | ((tr == hierarchy_selected) ? ImGuiTreeNodeFlags_Selected : 0))) {
      if (ImGui::IsItemClicked()) {
        hierarchy_selected = tr;
      }
      for (auto child : tr->GetChildren()) {
        HierarchyLevel(child);
      }
      ImGui::TreePop();
    }
  }
}


void EditorInstance::Inspector() {
  if (hierarchy_selected != nullptr) {
    hierarchy_selected->DrawWidget();
  } else {
    ImGui::Text("No Transform Selected");
  }
}

void EditorInstance::SceneHierarchy() {

  ImGui::BeginTable("SceneHierarchy",2);
  ImGui::TableSetupColumn("Hierarchy");
  ImGui::TableSetupColumn("Inspector");
  ImGui::TableHeadersRow();
  ImGui::TableNextRow();
  ImGui::TableSetColumnIndex(0);
  if (Transform *tr;
      (tr = engine->GetSceneLoader()->GetCurrentScene()->GetRoot()) !=
      nullptr) {
    HierarchyLevel(tr);
  }
  ImGui::TableSetColumnIndex(1);
  Inspector();
  ImGui::EndTable();
}

void EditorInstance::AssetPanel() {
  static Asset* selected_asset = nullptr;
  ImGui::BeginTable("AssetPanelLayout",2);

  ImGui::TableSetupColumn("List");
  ImGui::TableSetupColumn("Details");

  ImGui::TableHeadersRow();
  ImGui::TableNextRow();
  ImGui::TableSetColumnIndex(0);
  if (ImGui::TreeNode("Models")) {
    for (auto mod : Engine()->GetAssetManager()->loaded_models) {
      if (ImGui::TreeNodeEx(mod.first.c_str(),ImGuiTreeNodeFlags_OpenOnArrow | ImGuiTreeNodeFlags_OpenOnDoubleClick | (mod.second == selected_asset ? ImGuiTreeNodeFlags_Selected : 0))) {
        if (ImGui::IsItemClicked()) {
          selected_asset = mod.second;
        }
        for (auto mesh : mod.second->GetMeshes()) {
          if (ImGui::TreeNodeEx(("." +mesh->GetName()).c_str(),ImGuiTreeNodeFlags_Leaf | (mesh == selected_asset ? ImGuiTreeNodeFlags_Selected : 0))) {
            if (ImGui::IsItemClicked()) {
                selected_asset = mesh;
            }
            ImGui::TreePop();
          }
        }
        ImGui::TreePop();
      }
    }
    ImGui::TreePop();
  }
  ImGui::TableSetColumnIndex(1);
  if (selected_asset != nullptr) {
    ImGui::Text("%s", selected_asset->GetName().c_str());
    ImGui::Text("%s", selected_asset->GetPath().c_str());
  }
  ImGui::EndTable();
}

void EditorInstance::DebugPanel()
{
  ImGui::Begin("Debug");

  if (ImGui::BeginTabBar("DebugTabs", ImGuiTabBarFlags_None))
  {
    if (ImGui::BeginTabItem("Actions")) {
      if (ImGui::Button("Reload Assets")) {
        engine->GetAssetManager()->Rescan();
      }
      if (ImGui::Button("Add Root Child")) {
        Transform* ch = new Transform(std::string("Child"));
        engine->GetSceneLoader()->GetCurrentScene()->GetRoot()->AddChild(ch);
      }
      if (ImGui::Button("Add Root Child w Debug Mesh")) {
        Transform *ch = new Transform(std::string("Child"));
        MeshComponent* comp = new MeshComponent(std::string("MeshComponent"));
        comp->SetMesh("DefaultCube.Suzanne");
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
