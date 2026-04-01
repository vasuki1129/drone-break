#include "opengl_renderer.h"
#include <GLFW/glfw3.h>
#include "../imgui/imgui.h"
#include "../imgui/imgui_impl_glfw.h"
#include "../imgui/imgui_impl_opengl3.h"
namespace engine {

OpenGLRenderer::OpenGLRenderer(GLFWwindow** smuggle, EngineCreateInfo& create_info) {
    glfwInit();
    window = glfwCreateWindow(create_info.initial_window_width, create_info.initial_window_height, create_info.game_name.c_str(), NULL, NULL);
    *smuggle = window;
    glfwMakeContextCurrent(window);
    glewInit();
}

bool OpenGLRenderer::ShouldClose() {
  return glfwWindowShouldClose(this->window);
}


void OpenGLRenderer::InitForImGui() {
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui::StyleColorsDark();

    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 130");
}


float OpenGLRenderer::DeltaTime() {
  return delta_time;
}



void OpenGLRenderer::StartFrame() {
  last = glfwGetTime();
  glClear(GL_COLOR_BUFFER_BIT);
}

void OpenGLRenderer::EndFrame() {
  glfwSwapBuffers(this->window);
  delta_time = glfwGetTime() - last;
}




OpenGLRenderer::~OpenGLRenderer() {
    glfwDestroyWindow(window);
    glfwTerminate();
}

}
