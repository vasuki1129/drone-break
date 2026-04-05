#include "editor.h"
#include "../imgui/imgui.h"
#include "../imgui/imgui_impl_glfw.h"
#include "../imgui/imgui_impl_opengl3.h"
#include "mesh_component.h"
#include "gui_util.h"

namespace engine::editor {



bool debug_panel_vis = false;
bool asset_panel_vis = false;
bool hierarchy_vis = false;
bool inspector_vis = false;
bool actions_vis = false;

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

void EditorInstance::HierarchyLevel(Transform *tr) {
  if(tr == nullptr) return;
  if (tr->GetChildren().size() == 0) {
    ImGui::PushID(tr->GetUID());
    if (ImGui::TreeNodeEx((tr->GetName() + "##" + std::to_string(tr->GetUID())).c_str(), ImGuiTreeNodeFlags_Bullet | ImGuiTreeNodeFlags_DrawLinesFull | ImGuiTreeNodeFlags_Leaf | ((tr == hierarchy_selected) ? ImGuiTreeNodeFlags_Selected : 0))) {

      if (ImGui::BeginPopupContextItem((tr->GetName() + "ContextMenu##" + std::to_string(tr->GetUID())+"a").c_str())) {
        if (ImGui::MenuItem("Add Child Node", NULL, false, true)) {
          Transform *t = new Transform(std::string("Child"));
          tr->AddChild(t);
        }
        ImGui::EndPopup();
      }
      ImGui::TreePop();
    }
    ImGui::PopID();
    if (ImGui::IsItemClicked()) {
      hierarchy_selected = tr;
    }
  } else {

    if (ImGui::TreeNodeEx((tr->GetName() + "##" + std::to_string(tr->GetUID())).c_str(),ImGuiTreeNodeFlags_DrawLinesFull | ImGuiTreeNodeFlags_OpenOnDoubleClick | ((tr == hierarchy_selected) ? ImGuiTreeNodeFlags_Selected : 0))) {
      if (ImGui::BeginPopupContextItem((tr->GetName() + "ContextMenu" + std::to_string(tr->GetUID())+ "b").c_str())) {
        if (ImGui::MenuItem("Add Child Node", NULL, false, true)) {
          Transform *t = new Transform(std::string("Child"));
          tr->AddChild(t);
        }
        ImGui::EndPopup();
      }
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
    if (inspector_vis) {




      if(ImGui::Begin("Inspector",&inspector_vis)){
        if (hierarchy_selected != nullptr) {
          hierarchy_selected->DrawWidget();
        } else {
          ImGui::Text("No Transform Selected");
        }
      }
      ImGui::End();
    }
  }

  void EditorInstance::SceneHierarchy() {

    if(hierarchy_vis){

      if(ImGui::Begin("Hierarchy", &hierarchy_vis)){
        if (Transform *tr;
      (tr = engine->GetSceneLoader()->GetCurrentScene()->GetRoot()) !=
      nullptr) {
          HierarchyLevel(tr);
        }
      }
      ImGui::End();
    }
  }

  void EditorInstance::AssetPanel() {

    static Asset* selected_asset = nullptr;

    if(asset_panel_vis){


      if(ImGui::Begin("Assets")){

        if(ImGui::BeginTable("AssetLayout",2)){

          ImGui::TableSetupColumn("##ASSET");
          ImGui::TableSetupColumn("##DETAILS");
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
      }
      ImGui::End();
    }
  }


  void EditorInstance::ActionsPanel() {
    if(actions_vis){
      if(ImGui::Begin("Actions"),&actions_vis){
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
      }
      ImGui::End();
    }
  }



  void EditorInstance::DrawTransformGizmo() {
    if (hierarchy_selected == nullptr)
      return;




  }



  
void EditorInstance::DebugPanel() {
  if (debug_panel_vis) {
    if (ImGui::Begin("Debug"), &debug_panel_vis) {
      ImGui::Text("%s",Engine()->GetVersionString().c_str());
      ImGui::Text("Frame Time: %.3fms", Engine()->GetRenderer()->DeltaTime() * 1000.0f );
      ImGui::Text("FPS: %.3fms", (1.0f / Engine()->GetRenderer()->DeltaTime()) );
    }
    ImGui::End();
  }
}


void EditorInstance::MenuBar() {

    if (ImGui::BeginMainMenuBar()) {
      if (ImGui::BeginMenu("File")) {
        if (ImGui::MenuItem("Open Scene")) {
        }
        ImGui::EndMenu();
      }

      if (ImGui::BeginMenu("Tools")) {
        if (ImGui::MenuItem("Hierarchy")) {
          hierarchy_vis = true;
        }
        if (ImGui::MenuItem("Inspector")) {
          inspector_vis = true;
        }
        if (ImGui::MenuItem("Debug Info")) {
          debug_panel_vis = true;
        }
        ImGui::EndMenu();
      }
      ImGui::EndMainMenuBar();
    }
}




void EditorInstance::Run() {
  while (!glfwWindowShouldClose(engine->GetWindow())) {
    glfwPollEvents();
    engine->GetRenderer()->StartFrame();
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
    ImGui::DockSpaceOverViewport(0,NULL,ImGuiDockNodeFlags_PassthruCentralNode,NULL);

    MenuBar();
    //ImGui::ShowDemoWindow();
    DebugPanel();
    ActionsPanel();
    Inspector();
    SceneHierarchy();
    AssetPanel();

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
