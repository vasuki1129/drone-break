#include "skybox_component.h"

SkyboxComponent::SkyboxComponent() : engine::Component() {
  this->name = "SkyboxComponent";
  this->component_type = "SkyboxComponent";
}

void SkyboxComponent::tick(float dt) {
  Component *ply = engine::Engine()->GetLocalPlayer();
  if (ply != nullptr) {
    this->GetOwner()->position = ply->GetOwner()->position;

  }
}

json SkyboxComponent::Save() {
  json j;
  j["name"] = name;
  j["uid"] = uid;
  j["component_type"] = component_type;
  return j;
}

bool SkyboxComponent::Load(json value) {
  PROPERTY_LOAD(name)
  PROPERTY_LOAD(uid)
  PROPERTY_LOAD(component_type)
  return true;
}

void SkyboxComponent::DrawWidget() {


}

FACTORY_DEF(SkyboxComponent);
