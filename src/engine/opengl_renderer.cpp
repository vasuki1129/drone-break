#include "opengl_renderer.h"
#include <GLFW/glfw3.h>

namespace engine {

opengl_renderer::opengl_renderer(GLFWwindow** smuggle) {
    glfwInit();
    window = glfwCreateWindow(1024, 768, "light", NULL, NULL);
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
