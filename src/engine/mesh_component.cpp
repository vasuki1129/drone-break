#include "mesh_component.h"
#include "engine.h"
#include "../imgui/imgui.h"
namespace engine {

void MeshComponent::SetMesh(std::string msh) {
  Mesh *try_mesh = Engine()->GetAssetManager()->GetMeshOrNull(msh);
  if (try_mesh == nullptr) {
    std::cout << "Failed to set property: mesh `" + msh + "` not found";
  } else {
    this->mesh_name = msh;
    mesh_name.resize(64);
  }
}

void MeshComponent::SetMaterial(std::string mat) {
  Material *try_material = Engine()->GetAssetManager()->GetMaterialOrNull(mat);
  if (try_material == nullptr) {
    std::cout << "Failed to set property: material `" + mat + "` not found";
  } else {
    this->material_name = mat;
    material_name.resize(64);
  }
}

void MeshComponent::render() {
  Material *material =
      Engine()->GetAssetManager()->GetMaterialOrNull(material_name);
  Mesh *mesh = Engine()->GetAssetManager()->GetMeshOrNull(mesh_name);

  this->owner->Rotate(glm::vec3(0.0,1.0,0.0), Engine()->GetRenderer()->DeltaTime());
  if (material == nullptr || mesh == nullptr) {
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

  mesh->Draw(base, material);
}

void MeshComponent::init() {}

void MeshComponent::destroy() {}

MeshComponent::MeshComponent(std::string name)
: Component(name) {
  this->mesh_name = "";
  this->material_name = "";
  mesh_name.resize(64);
  material_name.resize(64);
}

void MeshComponent::DrawWidget() {
  if (ImGui::CollapsingHeader(this->name.c_str())) {
    ImGui::InputText("Mesh", this->mesh_name.data(), 64);
    ImGui::InputText("Material", this->material_name.data(), 64);
    if (ImGui::Button("Update")) {
        this->SetMesh(mesh_name);
    }

  }


}
  

}
