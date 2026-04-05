#pragma once
#include <GLFW/glfw3.h>
#include <map>
namespace engine {

enum class KeyState {
  KEY_UP,
  KEY_PRESSED,
  KEY_DOWN,
  KEY_RELEASED
};

void InputHandlerKeyCallback(GLFWwindow *window, int key, int scancode,
                             int action, int mods);

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

  void Update();
  void SendInput(int key, int action, int mods);
private:
  std::map<int, KeyState> key_state;
};

}
