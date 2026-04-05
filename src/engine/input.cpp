#include "engine.h"
#include <GLFW/glfw3.h>
#include "input.h"

namespace engine {

  void InputHandlerKeyCallback(GLFWwindow *window, int key, int scancode,
                               int action, int mods) {
    Engine()->GetInput()->SendInput(key,action,mods);
  }


  int MakeKeyval(int key, int mod) { return GLFW_KEY_LAST * mod + key; }

  void InputHandler::Update() {
    for (auto v : key_state) {
      if (v.second == KeyState::KEY_PRESSED) {
        key_state[v.first] = KeyState::KEY_DOWN;
      }
      if (v.second == KeyState::KEY_RELEASED) {
        key_state[v.first] = KeyState::KEY_UP;
      }
    }
  }

  bool InputHandler::KeyDown(int key) {
    if (key_state.find(key) != key_state.end() &&
        (key_state[key] == KeyState::KEY_DOWN ||
         key_state[key] == KeyState::KEY_PRESSED)) {
      return true;
    } else {
      return false;
    }
  }

  bool InputHandler::KeyDown(int key, int mods) {
    int keyval = MakeKeyval(key, mods);
    return KeyDown(keyval);
  }

  bool InputHandler::KeyUp(int key) {
    return !KeyDown(key);
  }

  bool InputHandler::KeyUp(int key, int mods) {
    return !KeyDown(MakeKeyval(key, mods));
  }

  bool InputHandler::KeyPressed(int key) {
    if (key_state.find(key) != key_state.end() &&
        (key_state[key] == KeyState::KEY_PRESSED)) {
      return true;
    } else {
      return false;
    }
  }

  bool InputHandler::KeyPressed(int key, int mods) {
    return KeyPressed(MakeKeyval(key, mods));
  }

  bool InputHandler::KeyReleased(int key) {
    if (key_state.find(key) != key_state.end() &&
        key_state[key] == KeyState::KEY_RELEASED) {
      return true;
    } else {
      return false;
    }
  }

  bool InputHandler::KeyReleased(int key, int mods) {
    return KeyReleased(MakeKeyval(key, mods));
  }

  void InputHandler::SendInput(int key, int action, int mods) {
    int mods_filtered = mods & 0b111; //filter out all but shift, ctrl, and alt
    int key_value = MakeKeyval(key, mods);
    if (action == GLFW_PRESS) {
      key_state[key_value] = KeyState::KEY_PRESSED;
    } else if (action == GLFW_RELEASE) {
      for (int i = 0; i < 8; i++) {
        if (key_state.find(key + GLFW_KEY_LAST * i) != key_state.end()) {
          KeyState state = key_state[key + GLFW_KEY_LAST * i];
          switch (state) {
          case KeyState::KEY_PRESSED:
          case KeyState::KEY_DOWN:
            key_state[key + GLFW_KEY_LAST * i] = KeyState::KEY_RELEASED;
            break;
          case KeyState::KEY_UP:
            key_state[key + GLFW_KEY_LAST * i] = KeyState::KEY_RELEASED;
            break;
          default:
            break;
          }
        }

      }
    }
  }
}
