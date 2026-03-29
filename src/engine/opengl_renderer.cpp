#include "opengl_renderer.h"
#include <GLFW/glfw3.h>

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

void OpenGLRenderer::PushFrame() {
  glClear(GL_COLOR_BUFFER_BIT);


  glfwSwapBuffers(this->window);
}

OpenGLRenderer::~OpenGLRenderer() {
    glfwDestroyWindow(window);
    glfwTerminate();
}

}
