#include "editor.h"
#include "../imgui/imgui.h"
#include "../imgui/imgui_impl_glfw.h"
#include "../imgui/imgui_impl_opengl3.h"
#include "mesh_component.h"
#include "gui_util.h"
#include "opengl_renderer.h"
#include "physics.h"
#include <GL/gl.h>
#include <glm/geometric.hpp>
#include <glm/glm.hpp>
#include <deque>
#include "camera_component.h"
#include "../imgui/imfilebrowser.h"
#include "../imgui/icon_fonts.h"
namespace engine::editor {

bool debug_panel_vis = false;
bool asset_panel_vis = false;
bool hierarchy_vis = false;
bool inspector_vis = false;
bool actions_vis = false;
bool preferences_vis = false;

bool scene_load_menu_open = false;

ImGui::FileBrowser loadBrowser;
ImGui::FileBrowser saveBrowser(ImGuiFileBrowserFlags_EnterNewFilename);

int fps_smooth_samples = 100;

EditorInstance::EditorInstance() {
  auto c_i = engine::EngineCreateInfo {
    .game_name = "Light Editor",
    .initial_window_width = 600,
    .initial_window_height = 800
  };
  engine = engine::CreateEngine(c_i);
  engine->Initialize();
  engine->GetRenderer()->InitForImGui();
  glGenVertexArrays(1,&grid_vao);

  Transform* editor_camera_transform = new Transform(std::string("EditorCameraNode"));
  this->game_start_camera = Engine()->GetSceneLoader()->GetCurrentScene()->GetCurrentCamera();
  EditorCameraComponent* comp = new EditorCameraComponent("EditorCamera");
  editor_camera_transform->AddComponent(comp);
  this->editor_camera = comp;
  Engine()->GetSceneLoader()->GetCurrentScene()->SetCamera(comp);
  Engine()->GetInput()->EnableCursor();
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

        ImGui::End();
      }
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


      if(ImGui::Begin("Assets",&asset_panel_vis)){

        if(ImGui::BeginTable("AssetLayout",2)){

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

          if (ImGui::TreeNode("Textures")) {
            for (auto tx : Engine()->GetAssetManager()->loaded_textures) {
              if(ImGui::TreeNodeEx(tx.first.c_str(),ImGuiTreeNodeFlags_Leaf)){
                if(ImGui::IsItemClicked())
                {
                  selected_asset = tx.second;
                }
                ImGui::TreePop();
              }

            }
            ImGui::TreePop();
          }


          if (ImGui::TreeNode("Shaders")) {
            for (auto sh : Engine()->GetAssetManager()->loaded_shaders) {
              if (ImGui::TreeNodeEx(sh.first.c_str(),
                                    ImGuiTreeNodeFlags_Leaf)) {
                if (ImGui::IsItemClicked()) {
                  selected_asset = sh.second;
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
      static bool x_axis_translate_dragging = false;
      static bool y_axis_translate_dragging = false;
      static bool z_axis_translate_dragging = false;
    if (hierarchy_selected == nullptr)
      return;


    if(!Engine()->GetInput()->MouseButtonDown(0))
    {
        x_axis_translate_dragging = false;
        y_axis_translate_dragging = false;
        z_axis_translate_dragging = false;
    }

    static glm::vec3 dragging_start_pos;

    if(x_axis_translate_dragging)
    {
        glm::vec3 pA = dragging_start_pos;
        glm::vec3 pB = pA + hierarchy_selected->Right()*1.0f;
        glm::vec3 pA_t = Engine()->GetSceneLoader()->GetCurrentScene()->GetCurrentCameraMatrix() * glm::vec4(pA,1.0);
        glm::vec3 pB_t = Engine()->GetSceneLoader()->GetCurrentScene()->GetCurrentCameraMatrix() * glm::vec4(pB,1.0);
        glm::vec3 dir = pB_t - pA_t;
        glm::vec2 pr = glm::vec2(dir.x,dir.y);
        float proj = glm::dot(Engine()->GetInput()->MouseDelta(),pr)/glm::length(dir);
        hierarchy_selected->Translate((glm::vec3(1.0,0.0,0.0) * hierarchy_selected->GetGlobalRotation()) * proj * glm::length(Engine()->GetInput()->MouseDelta()) * 0.01f);
    }

    if(y_axis_translate_dragging)
    {
        glm::vec3 pA = dragging_start_pos;
        glm::vec3 pB = pA + hierarchy_selected->Up()*1.0f;
        glm::vec3 pA_t = Engine()->GetSceneLoader()->GetCurrentScene()->GetCurrentCameraMatrix() * glm::vec4(pA,1.0);
        glm::vec3 pB_t = Engine()->GetSceneLoader()->GetCurrentScene()->GetCurrentCameraMatrix() * glm::vec4(pB,1.0);
        glm::vec3 dir = pB_t - pA_t;
        glm::vec2 pr = glm::vec2(dir.x,dir.y);
        float proj = glm::dot(Engine()->GetInput()->MouseDelta(),pr)/glm::length(dir);
        hierarchy_selected->Translate((glm::vec3(0.0,-1.0,0.0) * hierarchy_selected->GetGlobalRotation()) * proj * glm::length(Engine()->GetInput()->MouseDelta()) * 0.01f);
    }


    if(z_axis_translate_dragging)
    {
        glm::vec3 pA = dragging_start_pos;
        glm::vec3 pB = pA + hierarchy_selected->Forward()*1.0f;
        glm::vec3 pA_t = Engine()->GetSceneLoader()->GetCurrentScene()->GetCurrentCameraMatrix() * glm::vec4(pA,1.0);
        glm::vec3 pB_t = Engine()->GetSceneLoader()->GetCurrentScene()->GetCurrentCameraMatrix() * glm::vec4(pB,1.0);
        glm::vec3 dir = pB_t - pA_t;
        glm::vec2 pr = glm::vec2(dir.x,dir.y);
        float proj = glm::dot(Engine()->GetInput()->MouseDelta(),pr)/glm::length(dir);
        hierarchy_selected->Translate((glm::vec3(0.0,0.0,1.0) * hierarchy_selected->GetGlobalRotation()) * proj * glm::length(Engine()->GetInput()->MouseDelta() * 0.01f));
    }

    glBindVertexArray(gizmo_vao);

    Shader* shader = Engine()->GetAssetManager()->GetShaderOrNull("shd_transform_gizmo");
    if(shader->IsValid())
    {

      shader->Bind();

      shader->SetUniform("gizmo_location", hierarchy_selected->GetGlobalPosition());
      shader->SetUniform("model", hierarchy_selected->GetModelMatrixUnscaled());
      shader->SetUniform("camera", Engine()
                                  ->GetSceneLoader()
                                  ->GetCurrentScene()
                                  ->GetCurrentCameraMatrix());



      if (engine->GetSceneLoader()->GetCurrentScene()->GetCurrentCamera() !=
          nullptr) {


      
      Ray r = engine->GetSceneLoader()->GetCurrentScene()->GetCurrentCamera()->ScreenPointToRay(Engine()->GetInput()->MousePosition());
      float int_dist;
      if(TestRayOBBIntersection(r.position, r.direction, glm::vec3(0,0,0), glm::vec3(2.0f,0.1f,0.1f), hierarchy_selected->GetModelMatrixUnscaled(), int_dist)
         && !(y_axis_translate_dragging || z_axis_translate_dragging))
      {
        shader->SetUniform("x_hovered", Uniform_f(1.0f));
        if(Engine()->GetInput()->MouseButtonPressed(0))
        {
            x_axis_translate_dragging = true;
            dragging_start_pos = hierarchy_selected->GetGlobalPosition();
        }


      }
      else
      {
        shader->SetUniform("x_hovered", Uniform_f(0.0f));
      }


      r = engine->GetSceneLoader()->GetCurrentScene()->GetCurrentCamera()->ScreenPointToRay(Engine()->GetInput()->MousePosition());
      if(TestRayOBBIntersection(r.position, r.direction, glm::vec3(0,0,0), glm::vec3(0.1f,2.0f,0.1f), hierarchy_selected->GetModelMatrixUnscaled(), int_dist)
         && !(x_axis_translate_dragging || z_axis_translate_dragging))
      {
        shader->SetUniform("y_hovered", Uniform_f(1.0f));
        if(Engine()->GetInput()->MouseButtonPressed(0))
        {
            y_axis_translate_dragging = true;

            dragging_start_pos = hierarchy_selected->GetGlobalPosition();
        }
      }
      else
      {
        shader->SetUniform("y_hovered", Uniform_f(0.0f));
      }


      r = engine->GetSceneLoader()->GetCurrentScene()->GetCurrentCamera()->ScreenPointToRay(Engine()->GetInput()->MousePosition());
      if(TestRayOBBIntersection(r.position, r.direction, glm::vec3(0,0,0), glm::vec3(0.1f,0.1f,2.0f), hierarchy_selected->GetModelMatrixUnscaled(), int_dist)
         && !(x_axis_translate_dragging || y_axis_translate_dragging))
      {
        shader->SetUniform("z_hovered", Uniform_f(1.0f));
        z_axis_translate_dragging = true;
        dragging_start_pos = hierarchy_selected->GetGlobalPosition();
      }
      else
      {
        shader->SetUniform("z_hovered", Uniform_f(0.0f));
      }
      }

      glLineWidth(3.0);
      glDepthFunc(GL_ALWAYS);
      glDrawArrays(GL_LINES,0,6);
      glDepthFunc(GL_LESS);
    }

    glBindVertexArray(0);
  }

  void EditorInstance::DrawGrid() {
    glBindVertexArray(this->grid_vao);
    auto shd = Engine()->GetAssetManager()->GetShaderOrNull("shd_editor_grid");

    if (shd == nullptr) {
      std::cout << "grid shader not found\n";
      return;
    }

    shd->Bind();
    shd->SetUniform("camera", Engine()
                                  ->GetSceneLoader()
                                  ->GetCurrentScene()
                                  ->GetCurrentCameraMatrix());
    shd->SetUniform("cam_pos", Engine()->GetSceneLoader()->GetCurrentScene()->GetCurrentCameraPosition());
    shd->SetUniform("grid_color_thin", glm::vec3(0.3,0.3,0.3));
    shd->SetUniform("grid_color_thick", glm::vec3(1.0,1.0,1.0));
    shd->SetUniform("grid_size", Uniform_f(1.0f));
    shd->SetUniform("min_pixels", Uniform_f(2.0f));
    glEnable(GL_MULTISAMPLE);
    glDisable(GL_CULL_FACE);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glEnable(GL_CULL_FACE);
  }

void EditorInstance::DebugPanel() {
  static std::vector<float> fps_smooth;

  if (debug_panel_vis) {
    if (ImGui::Begin("Debug", &debug_panel_vis)) {
      ImGui::Text("%s",Engine()->GetVersionString().c_str());
      ImGui::Text("Frame Time: %.3fms", Engine()->GetRenderer()->DeltaTime() * 1000.0f );

      fps_smooth.push_back(1.0f/Engine()->GetRenderer()->DeltaTime());
      if (fps_smooth.size() >= fps_smooth_samples) {
        fps_smooth.erase(fps_smooth.begin());
      }

      float tot = 0.0f;
      for (auto f : fps_smooth) {
        tot += f;
      }
      tot /= fps_smooth.size();

      ImGui::Text("FPS: %.3fms", (tot));
      ImGui::PlotLines("FPS Graph",fps_smooth.data(), fps_smooth.size(),0,NULL,0,120,ImVec2(0,100));

      ImGui::Text("Mouse Delta: ( %f, %f )",Engine()->GetInput()->MouseDelta().x, Engine()->GetInput()->MouseDelta().y);
    }
    ImGui::End();
  }
}


  void EditorInstance::OpenSceneLoadMenu(){
      loadBrowser.Open();
  }
  void EditorInstance::OpenSceneSaveMenu()
  {
      saveBrowser.Open();
  }


void EditorInstance::SceneLoadMenu()
{


}




void EditorInstance::MenuBar() {

    if (ImGui::BeginMainMenuBar()) {
      if (ImGui::BeginMenu("File")) {
        if (ImGui::MenuItem("Open Scene")) {
          OpenSceneLoadMenu();
        }
        if(ImGui::MenuItem("Save Scene"))
        {
          OpenSceneSaveMenu();
        }
        if (ImGui::MenuItem("Editor Settings")) {
          preferences_vis = true;

        }


        ImGui::EndMenu();
      }

      if (ImGui::BeginMenu("Tools")) {
        if (ImGui::MenuItem("Assets")) {
          asset_panel_vis = true;
        }
        if (ImGui::MenuItem("Hierarchy")) {
          hierarchy_vis = true;
        }
        if (ImGui::MenuItem("Inspector")) {
          inspector_vis = true;
        }
        if (ImGui::MenuItem("Debug Info")) {
          debug_panel_vis = true;
        }
        if (ImGui::MenuItem("Actions")) {
          actions_vis = true;
        }
        ImGui::EndMenu();
      }



      ImGui::EndMainMenuBar();
    }

}

enum class PrefsPage {
  APPEARANCE,
  GENERAL
};

PrefsPage current_page = PrefsPage::GENERAL;

void EditorInstance::PreferencesWindow() {
  if (!preferences_vis) return;

  ImGui::Begin("Preferences", &preferences_vis);

  ImGui::BeginTable("PrefsTable", 2,
                    ImGuiTableFlags_Resizable | ImGuiTableFlags_BordersInner,ImVec2{0.0f,-FLT_MIN});
  ImGui::TableNextRow(0,ImGui::GetWindowHeight() - 50);
  ImGui::TableSetColumnIndex(0);
  if (ImGui::TreeNodeEx("Editor")) {
    if (ImGui::TreeNodeEx("General",ImGuiTreeNodeFlags_Leaf | (current_page == PrefsPage::GENERAL ? ImGuiTreeNodeFlags_Selected : 0))) {
      if (ImGui::IsItemClicked()) {
        current_page = PrefsPage::GENERAL;
      }
      ImGui::TreePop();
    }
    if (ImGui::TreeNodeEx("Appearance",ImGuiTreeNodeFlags_Leaf | (current_page == PrefsPage::APPEARANCE ? ImGuiTreeNodeFlags_Selected : 0))) {
      if (ImGui::IsItemClicked()) {
        current_page = PrefsPage::APPEARANCE;
      }
      ImGui::TreePop();
    }

    ImGui::TreePop();
  }
  ImGui::TableSetColumnIndex(1);

  ImGui::EndTable();

  ImGui::End();
}

void EditorInstance::Run() {


ImVec4* colors = ImGui::GetStyle().Colors;
colors[ImGuiCol_Text]                   = ImVec4(0.72f, 0.74f, 0.77f, 1.00f);
colors[ImGuiCol_TextDisabled]           = ImVec4(0.50f, 0.50f, 0.50f, 1.00f);
colors[ImGuiCol_WindowBg]               = ImVec4(0.19f, 0.21f, 0.19f, 1.00f);
colors[ImGuiCol_ChildBg]                = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
colors[ImGuiCol_PopupBg]                = ImVec4(0.08f, 0.08f, 0.08f, 1.00f);
colors[ImGuiCol_Border]                 = ImVec4(0.26f, 0.31f, 0.26f, 0.98f);
colors[ImGuiCol_BorderShadow]           = ImVec4(0.00f, 0.00f, 0.00f, 1.00f);
colors[ImGuiCol_FrameBg]                = ImVec4(0.00f, 0.00f, 0.00f, 1.00f);
colors[ImGuiCol_FrameBgHovered]         = ImVec4(0.26f, 0.59f, 0.98f, 0.45f);
colors[ImGuiCol_FrameBgActive]          = ImVec4(0.26f, 0.59f, 0.98f, 0.67f);
colors[ImGuiCol_TitleBg]                = ImVec4(0.04f, 0.04f, 0.04f, 1.00f);
colors[ImGuiCol_TitleBgActive]          = ImVec4(0.08f, 0.09f, 0.08f, 1.00f);
colors[ImGuiCol_TitleBgCollapsed]       = ImVec4(0.00f, 0.00f, 0.00f, 0.51f);
colors[ImGuiCol_MenuBarBg]              = ImVec4(0.14f, 0.14f, 0.14f, 1.00f);
colors[ImGuiCol_ScrollbarBg]            = ImVec4(0.02f, 0.02f, 0.02f, 0.53f);
colors[ImGuiCol_ScrollbarGrab]          = ImVec4(0.31f, 0.31f, 0.31f, 1.00f);
colors[ImGuiCol_ScrollbarGrabHovered]   = ImVec4(0.41f, 0.41f, 0.41f, 1.00f);
colors[ImGuiCol_ScrollbarGrabActive]    = ImVec4(0.51f, 0.51f, 0.51f, 1.00f);
colors[ImGuiCol_CheckMark]              = ImVec4(0.31f, 0.31f, 0.31f, 1.00f);
colors[ImGuiCol_SliderGrab]             = ImVec4(0.24f, 0.52f, 0.88f, 1.00f);
colors[ImGuiCol_SliderGrabActive]       = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
colors[ImGuiCol_Button]                 = ImVec4(0.00f, 0.00f, 0.00f, 1.00f);
colors[ImGuiCol_ButtonHovered]          = ImVec4(0.31f, 0.31f, 0.31f, 1.00f);
colors[ImGuiCol_ButtonActive]           = ImVec4(0.47f, 0.47f, 0.47f, 1.00f);
colors[ImGuiCol_Header]                 = ImVec4(0.00f, 0.00f, 0.00f, 1.00f);
colors[ImGuiCol_HeaderHovered]          = ImVec4(0.31f, 0.31f, 0.31f, 1.00f);
colors[ImGuiCol_HeaderActive]           = ImVec4(0.47f, 0.47f, 0.47f, 1.00f);
colors[ImGuiCol_Separator]              = ImVec4(0.43f, 0.43f, 0.50f, 0.30f);
colors[ImGuiCol_SeparatorHovered]       = ImVec4(0.50f, 0.50f, 0.50f, 0.30f);
colors[ImGuiCol_SeparatorActive]        = ImVec4(0.50f, 0.50f, 0.50f, 0.30f);
colors[ImGuiCol_ResizeGrip]             = ImVec4(0.26f, 0.59f, 0.98f, 0.20f);
colors[ImGuiCol_ResizeGripHovered]      = ImVec4(0.26f, 0.59f, 0.98f, 0.67f);
colors[ImGuiCol_ResizeGripActive]       = ImVec4(0.26f, 0.59f, 0.98f, 0.95f);
colors[ImGuiCol_InputTextCursor]        = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
colors[ImGuiCol_TabHovered]             = ImVec4(0.26f, 0.59f, 0.98f, 0.80f);
colors[ImGuiCol_Tab]                    = ImVec4(0.18f, 0.35f, 0.58f, 0.86f);
colors[ImGuiCol_TabSelected]            = ImVec4(0.20f, 0.41f, 0.68f, 1.00f);
colors[ImGuiCol_TabSelectedOverline]    = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
colors[ImGuiCol_TabDimmed]              = ImVec4(0.07f, 0.10f, 0.15f, 0.97f);
colors[ImGuiCol_TabDimmedSelected]      = ImVec4(0.14f, 0.26f, 0.42f, 1.00f);
colors[ImGuiCol_TabDimmedSelectedOverline]  = ImVec4(0.50f, 0.50f, 0.50f, 0.00f);
colors[ImGuiCol_DockingPreview]         = ImVec4(0.51f, 0.51f, 0.51f, 0.39f);
colors[ImGuiCol_DockingEmptyBg]         = ImVec4(0.20f, 0.20f, 0.20f, 1.00f);
colors[ImGuiCol_PlotLines]              = ImVec4(0.61f, 0.61f, 0.61f, 1.00f);
colors[ImGuiCol_PlotLinesHovered]       = ImVec4(1.00f, 0.43f, 0.35f, 1.00f);
colors[ImGuiCol_PlotHistogram]          = ImVec4(0.90f, 0.70f, 0.00f, 1.00f);
colors[ImGuiCol_PlotHistogramHovered]   = ImVec4(1.00f, 0.60f, 0.00f, 1.00f);
colors[ImGuiCol_TableHeaderBg]          = ImVec4(0.19f, 0.19f, 0.20f, 1.00f);
colors[ImGuiCol_TableBorderStrong]      = ImVec4(0.31f, 0.31f, 0.35f, 1.00f);
colors[ImGuiCol_TableBorderLight]       = ImVec4(0.33f, 0.33f, 0.33f, 1.00f);
colors[ImGuiCol_TableRowBg]             = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
colors[ImGuiCol_TableRowBgAlt]          = ImVec4(1.00f, 1.00f, 1.00f, 0.00f);
colors[ImGuiCol_TextLink]               = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
colors[ImGuiCol_TextSelectedBg]         = ImVec4(0.26f, 0.59f, 0.98f, 0.35f);
colors[ImGuiCol_TreeLines]              = ImVec4(0.43f, 0.43f, 0.50f, 0.50f);
colors[ImGuiCol_DragDropTarget]         = ImVec4(1.00f, 1.00f, 0.00f, 0.90f);
colors[ImGuiCol_DragDropTargetBg]       = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
colors[ImGuiCol_UnsavedMarker]          = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
colors[ImGuiCol_NavCursor]              = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
colors[ImGuiCol_NavWindowingHighlight]  = ImVec4(1.00f, 1.00f, 1.00f, 0.70f);
colors[ImGuiCol_NavWindowingDimBg]      = ImVec4(0.80f, 0.80f, 0.80f, 0.20f);
colors[ImGuiCol_ModalWindowDimBg]       = ImVec4(0.80f, 0.80f, 0.80f, 0.35f);



  while (!glfwWindowShouldClose(engine->GetWindow())) {
    glfwPollEvents();
    engine->GetRenderer()->StartFrame();
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
    ImGui::DockSpaceOverViewport(0,NULL,ImGuiDockNodeFlags_PassthruCentralNode,NULL);
    if(!game_running_switch)
    {
      ImGui::ShowDemoWindow();
      MenuBar();
      DebugPanel();
      ActionsPanel();
      Inspector();
      SceneHierarchy();
      AssetPanel();
      PreferencesWindow();
      SceneLoadMenu();
      DrawGrid();
    }
    TransportPanel();

    loadBrowser.Display();
    if (loadBrowser.HasSelected()) {
      std::string path = loadBrowser.GetSelected().string();
      if(!Engine()->GetSceneLoader()->LoadScene(path)){
          ImGui::OpenPopup("Scene Load Failure");
          std::cout << "Scene failed to load: " << path << "\n";
      }
      if(ImGui::BeginPopupModal("Scene Load Failure"))
      {

          ImGui::Text("Scene failed to load, it may be corrupted.");
          if(ImGui::Button("Close##SceneLoadFailure"))
          {
              ImGui::CloseCurrentPopup();
          }
          ImGui::EndPopup();
      }
      loadBrowser.ClearSelected();
    }

    saveBrowser.Display();
    if (saveBrowser.HasSelected()) {
      std::string path = saveBrowser.GetSelected().string();
      Engine()->GetSceneLoader()->SaveScene(path);
      saveBrowser.ClearSelected();
    }
    int display_w, display_h;
    glfwGetFramebufferSize(engine->GetWindow(), &display_w, &display_h);
    glViewport(0, 0, display_w, display_h);




    if(!game_running_switch)
    {
      editor_camera->GetOwner()->ProcessTick(engine->GetRenderer()->DeltaTime());
      editor_camera->GetOwner()->ProcessRender();
      engine->GetSceneLoader()->GetCurrentScene()->EditorRender();
      Engine()->GetSceneLoader()->GetCurrentScene()->SetCamera(this->editor_camera);
    }
    else
    {
      if(engine->GetInput()->KeyPressed(GLFW_KEY_ESCAPE))
      {
        engine->GetInput()->EnableCursor();
      }
      
      Engine()->GetSceneLoader()->GetCurrentScene()->SetCameraToMain();
      engine->GetSceneLoader()->UpdateCurrentScene(engine->GetRenderer()->DeltaTime());
    }
    engine->GetSceneLoader()->RenderCurrentScene();

    DrawTransformGizmo();

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    engine->GetInput()->Update();
    engine->GetRenderer()->EndFrame();
  }
}


void EditorInstance::TransportPanel()
{
    ImGui::Begin("Transport##PanelToplevel");

    if (ImGui::Button(
            (std::string(ICON_CI_ARROW_LEFT) + " ##TransportRewind").c_str(),
            ImVec2{30, 20})) {
      hierarchy_selected = nullptr;
      Engine()->GetSceneLoader()->RewindToCheckpoint();
      Engine()->GetSceneLoader()->GetCurrentScene()->SetCamera(this->editor_camera);
    }

    ImGui::SameLine();

    if(this->game_running_switch)
    {
        if(ImGui::Button((std::string(ICON_CI_STOP_CIRCLE)+" ##TransportStop").c_str(),ImVec2{30,20}))
        {
            engine->GetInput()->EnableCursor();
            game_running_switch = false;
        }
    }
    else
    {
      if (ImGui::Button(
              (std::string(ICON_CI_PLAY_CIRCLE) + " ##TransportPlay").c_str(),
              ImVec2{30, 20})) {

          engine->GetInput()->DisableCursor();
          game_running_switch = true;
      }
    }

    ImGui::SameLine();

    if(ImGui::Button((std::string(ICON_CI_SAVE) + " ##TransportSave").c_str(),ImVec2(30,20)))
    {
      Engine()->GetSceneLoader()->SaveAsCheckpoint();
    }
    ImGui::End();
}
}
