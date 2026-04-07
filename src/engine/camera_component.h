#pragma once
#include "../json/json.hpp"
#include "component.h"
#include <string>

namespace engine {

class CameraComponent : public Component {
public:
  CameraComponent();
  CameraComponent(json value);
  virtual ~CameraComponent();
  virtual void tick(float dt) override;
  virtual glm::mat4 GetCameraMatrix();
};

class EditorCameraComponent : public CameraComponent {
  public:
    EditorCameraComponent();
    EditorCameraComponent(std::string name);
    EditorCameraComponent(json value);
    virtual ~EditorCameraComponent();
    virtual void tick(float dt) override;
    virtual void DrawWidget() override;
};


}
