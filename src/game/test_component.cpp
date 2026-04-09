#include "test_component.h"
#include "../engine/input.h"
FACTORY_DEF(TestComponent);


TestComponent::TestComponent() :engine::Component(){
  this->name = "RotationComponent";
  this->component_type_id="RotationComponent";
}

void TestComponent::tick(float dt) {

  if (engine::Engine()->GetInput()->KeyDown(GLFW_KEY_D)) {
    this->owner->Rotate(this->rotation_axis, dt * this->rotation_speed);
    this->rotation_axis = glm::normalize(this->rotation_axis);
  }

}

void TestComponent::DrawWidget() {
  ImGui::InputFloat("Speed", &this->rotation_speed);
  ImGui::InputFloat3("Axis", glm::value_ptr(this->rotation_axis));
}
