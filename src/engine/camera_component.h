#pragma once
#include "../json/json.hpp"

#include "component.h"
namespace engine {

class CameraComponent : public Component {
public:
  CameraComponent();
  CameraComponent(json value);
  ~CameraComponent();
  glm::mat4 GetCameraMatrix();
};

}
