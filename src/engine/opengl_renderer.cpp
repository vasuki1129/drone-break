#include "opengl_renderer.h"
#include <GLFW/glfw3.h>

namespace engine {

opengl_renderer::opengl_renderer(GLFWwindow** smuggle, EngineCreateInfo& create_info) {
    glfwInit();
    window = glfwCreateWindow(create_info.initial_window_width, create_info.initial_window_height, create_info.game_name.c_str(), NULL, NULL);
    *smuggle = window;
    glfwMakeContextCurrent(window);
    glewInit();

}

bool opengl_renderer::ShouldClose() {
  return glfwWindowShouldClose(this->window);
}

void opengl_renderer::PushFrame() {
  glClear(GL_COLOR_BUFFER_BIT);


  glfwSwapBuffers(this->window);
}

opengl_renderer::~opengl_renderer() {
    glfwDestroyWindow(window);
    glfwTerminate();
}

}
