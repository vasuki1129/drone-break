#include "engine.h"
#include <GLFW/glfw3.h>
#include "input.h"

namespace engine {

  void InputHandlerKeyCallback(GLFWwindow *window, int key, int scancode,
                               int action, int mods) {
    Engine()->GetInput()->SendInput(key,action,mods);
  }

  void InputHandlerMousePositionCallback(GLFWwindow* window, double xpos, double ypos)
  {
    Engine()->GetInput()->SendMousePosition(glm::vec2(xpos,ypos));
  }

  void InputHandlerMouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
  {
    Engine()->GetInput()->SendMouseButton(button, action, mods);
  }

  int MakeKeyval(int key, int mod) { return GLFW_KEY_LAST * mod + key; }
  void InputHandler::SendMousePosition(glm::vec2 position)
  {
    mouse_delta = (position - last_mouse_pos);
    last_mouse_pos = position;
  }

  void InputHandler::SendMouseButton(int button, int action, int mods)
  {
    if(action == GLFW_PRESS)
    {
      switch (button) {
      case GLFW_MOUSE_BUTTON_LEFT:
        leftClick = KeyState::KEY_PRESSED;
        break;
      case GLFW_MOUSE_BUTTON_RIGHT:
        rightClick = KeyState::KEY_PRESSED;
        break;
      }
    }
    else if(action == GLFW_RELEASE)
    {
      switch (button) {
      case GLFW_MOUSE_BUTTON_LEFT:
        leftClick = KeyState::KEY_RELEASED;
        break;
      case GLFW_MOUSE_BUTTON_RIGHT:
        rightClick = KeyState::KEY_RELEASED;
        break;
      }
    }
  }

  glm::vec2 InputHandler::MouseDelta()
  {
    return this->mouse_delta;
  }

  glm::vec2 InputHandler::MousePosition()
  {
    return this->last_mouse_pos;
  }

  void InputHandler::Update() {

    this->mouse_delta.x = 0.0;
    this->mouse_delta.y = 0.0;
    for (auto v : key_state) {
      if (v.second == KeyState::KEY_PRESSED) {
        key_state[v.first] = KeyState::KEY_DOWN;
      }
      if (v.second == KeyState::KEY_RELEASED) {
        key_state[v.first] = KeyState::KEY_UP;
      }
    }

    if(leftClick == KeyState::KEY_PRESSED)
    {
      leftClick = KeyState::KEY_DOWN;
    }
    else if(leftClick == KeyState::KEY_RELEASED)
    {
      leftClick = KeyState::KEY_UP;
    }

    if(rightClick == KeyState::KEY_PRESSED)
    {
      rightClick = KeyState::KEY_DOWN;
    }
    else if(rightClick == KeyState::KEY_RELEASED)
    {
      rightClick = KeyState::KEY_UP;
    }



  }

  void InputHandler::DisableCursor()
  {
    glfwSetInputMode(Engine()->GetWindow(),GLFW_CURSOR,GLFW_CURSOR_DISABLED);
    if (glfwRawMouseMotionSupported())
      glfwSetInputMode(Engine()->GetWindow(), GLFW_RAW_MOUSE_MOTION, GLFW_TRUE);
  }




  void InputHandler::EnableCursor()
  {
    glfwSetInputMode(Engine()->GetWindow(),GLFW_CURSOR,GLFW_CURSOR_NORMAL);
  }


  bool InputHandler::MouseButtonPressed(int button)
  {
    if(button == 0)
      {
        return leftClick == KeyState::KEY_PRESSED;
      }
    else if(button == 1)
     {
        return rightClick == KeyState::KEY_PRESSED;
     }
    else
     {
      return false;
     }
  }


  bool InputHandler::MouseButtonReleased(int button)
  {
    if(button == 0)
      {
        return leftClick == KeyState::KEY_RELEASED;
      }
    else if(button == 1)
     {
        return rightClick == KeyState::KEY_RELEASED;
     }
    else
     {
      return false;
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

  bool InputHandler::MouseButtonDown(int button)
  {
    if(button == 0)
      {
        return leftClick == KeyState::KEY_DOWN || leftClick == KeyState::KEY_PRESSED;
      }
    else if(button == 1)
     {
        return rightClick == KeyState::KEY_DOWN || rightClick == KeyState::KEY_PRESSED;
     }
    else
     {
      return false;
     }
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
