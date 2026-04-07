#include "opengl_renderer.h"
#include <GLFW/glfw3.h>
#include "../imgui/imgui.h"
#include "../imgui/imgui_impl_glfw.h"
#include "../imgui/imgui_impl_opengl3.h"
#include "../imgui/icon_fonts.h"
#include "input.h"


#define STB_IMAGE_IMPLEMENTATION
#include "../stb/stb_image.h"
namespace engine {

int window_w = 0;
int window_h = 0;

void APIENTRY MessageCallback(GLenum source, GLenum type, GLuint id,
                              GLenum severity, GLsizei length,
                              const GLchar* message, const void* userParam) {
    fprintf(stderr, "GL CALLBACK: %s type = 0x%x, severity = 0x%x, message = %s\n",
           (type == GL_DEBUG_TYPE_ERROR ? "** GL ERROR **" : ""),
            type, severity, message);
}

void window_size_callback(GLFWwindow *window, int width, int height) {
  window_w = width;
  window_h = height;
  glViewport(0,0,width,height);
}

int OpenGLRenderer::WindowWidth() { return window_width; }

int OpenGLRenderer::WindowHeight() {return window_height;}

OpenGLRenderer::OpenGLRenderer(GLFWwindow** smuggle, EngineCreateInfo& create_info) {
    glfwInit();
    glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT,true);
    window = glfwCreateWindow(create_info.initial_window_width, create_info.initial_window_height, create_info.game_name.c_str(), NULL, NULL);
    *smuggle = window;
    window_w = create_info.initial_window_width;
    window_h = create_info.initial_window_height;

    glfwMakeContextCurrent(window);
    glewInit();

    glEnable(GL_DEBUG_OUTPUT);
    glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
    glDebugMessageCallback(MessageCallback, 0);
    glfwSetWindowSizeCallback(window, window_size_callback);

    //pass input to the input handler
    glfwSetKeyCallback(window, InputHandlerKeyCallback);
    glfwSetCursorPosCallback(window, InputHandlerMousePositionCallback);
    glCullFace(GL_BACK);
    glEnable(GL_CULL_FACE);
    glEnable(GL_DEPTH_TEST);
}

bool OpenGLRenderer::ShouldClose() {
  return glfwWindowShouldClose(this->window);
}

void OpenGLRenderer::InitForImGui() {
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui::StyleColorsDark();

    ImGuiIO &io = ImGui::GetIO();
    io.Fonts->AddFontFromFileTTF("ProggyCleanCENerdFont-Regular.ttf",13.0f);
    io.Fonts->AddFontFromFileTTF("ArimoNerdFont-Regular.ttf",13.0f);
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;



    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 130");
}

float OpenGLRenderer::DeltaTime() {
  return delta_time;
}

void OpenGLRenderer::StartFrame() {
  this->window_width = window_w;
  this->window_height = window_h;
  last = glfwGetTime();
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
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
