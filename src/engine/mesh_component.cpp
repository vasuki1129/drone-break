#include "mesh_component.h"
#include "engine.h"
#include "../imgui/imgui.cpp"
namespace engine {

void MeshComponent::SetMesh(Mesh *mesh) {
  this->mesh = mesh;
}

void MeshComponent::SetMaterial(Material *mat) {
  this->material = mat;
}

void MeshComponent::render() {
  this->owner->Rotate(glm::vec3(0.0,1.0,0.0), Engine()->GetRenderer()->DeltaTime());
  if (this->material == nullptr || this->mesh == nullptr) {
    std::cout << "MeshComponent missing required data\n";
    return;
  }
  BaseUniforms base{
      .model = this->owner->GetModelMatrix(),
      .camera = Engine()
                    ->GetSceneLoader()
                    ->GetCurrentScene()
                    ->GetCurrentCameraMatrix(),
  };

  this->mesh->Draw(base, material);
}

void MeshComponent::init() {}

void MeshComponent::destroy() {}

MeshComponent::MeshComponent(std::string name)
: Component(name) {
  this->mesh = nullptr;
  this->material = nullptr;
  mesh_name.resize(64);
  material_name.resize(64);
}

void MeshComponent::DrawWidget() {
  ImGui::InputText("Mesh", this->mesh_name.data(), 64);
  ImGui::InputText("Material", this->material_name.data(), 64);
  if (ImGui::Button("Update")) {

    auto mesh_try = Engine()->GetAssetManager()->GetMeshOrNull(mesh_name);
    if (mesh_try != nullptr) {
      this->SetMesh(mesh_try);
    } else {
      std::cout << "Mesh " + mesh_name + " not found in asset library.\n";
    }


  }


}
  

}
