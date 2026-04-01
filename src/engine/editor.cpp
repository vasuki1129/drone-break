#include "editor.h"
#include "../imgui/imgui_impl_glfw.h"
#include "../imgui/imgui_impl_opengl3.h"
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

void EditorInstance::Run() {
  while (!glfwWindowShouldClose(engine->GetWindow())) {
    glfwPollEvents();
    engine->GetRenderer()->StartFrame();
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    ImGui::ShowDemoWindow();

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
