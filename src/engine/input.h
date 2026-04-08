#pragma once
#include <GLFW/glfw3.h>
#include <map>
#include <glm/glm.hpp>
namespace engine {

enum class KeyState {
  KEY_UP,
  KEY_PRESSED,
  KEY_DOWN,
  KEY_RELEASED
};

void InputHandlerKeyCallback(GLFWwindow *window, int key, int scancode,
                             int action, int mods);


void InputHandlerMousePositionCallback(GLFWwindow* window, double xpos, double ypos);

void InputHandlerMouseButtonCallback(GLFWwindow* window, int key, int action, int mods);




class InputHandler {
public:
  bool KeyDown(int key);
  bool KeyDown(int key, int mods);
  bool KeyUp(int key);
  bool KeyUp(int key, int mods);
  bool KeyPressed(int key);
  bool KeyPressed(int key, int mods);
  bool KeyReleased(int key);
  bool KeyReleased(int key, int mods);


  void DisableCursor();
  void EnableCursor();

  bool MouseButtonDown(int button);
  bool MouseButtonPressed(int button);
  bool MouseButtonReleased(int button);

  glm::vec2 MouseDelta();
  glm::vec2 MousePosition();

  void Update();
  void SendInput(int key, int action, int mods);
  void SendMousePosition(glm::vec2 position);
  void SendMouseButton(int button, int action, int mods);


private:
  glm::vec2 mouse_delta_accum = glm::vec2(0.0,0.0);
  glm::vec2 mouse_delta = glm::vec2(0.0,0.0);
  glm::vec2 last_mouse_pos = glm::vec2(0.0,0.0);

  std::map<int, KeyState> key_state;
  KeyState leftClick;
  KeyState rightClick;




};

}
