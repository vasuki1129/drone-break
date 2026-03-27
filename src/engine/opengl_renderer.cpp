#include "opengl_renderer.h"
#include <GLFW/glfw3.h>

namespace engine {

opengl_renderer::opengl_renderer() {
    glfwInit();
    window = glfwCreateWindow(1024, 768, "light", NULL, NULL);
    glfwMakeContextCurrent(window);
    glewInit();

}

opengl_renderer::~opengl_renderer() {
    glfwDestroyWindow(window);
    glfwTerminate();
}

}
