#pragma once
#include "../json/json.hpp"
#include "component.h"
#include <string>
#include "physics.h"

namespace engine {

FACTORY(EditorCameraComponent);
FACTORY(CameraComponent);

class CameraComponent : public Component {
public:
  CameraComponent();
  CameraComponent(std::string name);
  virtual ~CameraComponent();
  virtual void tick(float dt) override;
  virtual glm::mat4 GetCameraMatrix();
  virtual Ray ScreenPointToRay(glm::vec2 screen_point);
  virtual json Save() override;
  virtual bool Load(json value) override;
  virtual void DrawWidget() override;
};

class EditorCameraComponent : public CameraComponent {
public:
  EditorCameraComponent();
  EditorCameraComponent(std::string name);
  virtual ~EditorCameraComponent();
  virtual void tick(float dt) override;
  virtual void DrawWidget() override;

  virtual json Save() override;
  virtual bool Load(json value) override;




protected:
  float movement_speed = 5.0f;
};


}
