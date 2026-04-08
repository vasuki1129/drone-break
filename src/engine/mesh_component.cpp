#include "mesh_component.h"
#include "engine.h"
#include "../imgui/imgui.h"
#include "../imgui/icon_fonts.h"
namespace engine {


FACTORY(MeshComponent) {
  MeshComponent *mesh_comp = new MeshComponent("MeshComponent");
  mesh_comp->SetMesh("DefaultCube.Suzanne");
  mesh_comp->SetMaterial("default");
  return mesh_comp;
}

bool MeshComponent::SetMesh(std::string msh) {
  Mesh *try_mesh = Engine()->GetAssetManager()->GetMeshOrNull(msh);
  if (try_mesh == nullptr) {
    std::cout << "Failed to set property: mesh `" + msh + "` not found";
    return false;
  } else {
    this->mesh_name = msh;
    mesh_name.resize(64);
    return true;
  }
}

bool MeshComponent::SetMaterial(std::string mat) {
  Material *try_material = Engine()->GetAssetManager()->GetMaterialOrNull(mat);
  if (try_material == nullptr) {
    std::cout << "Failed to set property: material `" + mat + "` not found";
    return false;
  } else {
    this->material_name = mat;
    material_name.resize(64);
    return true;
  }
}

void MeshComponent::render() {
  Material *material =
      Engine()->GetAssetManager()->GetMaterialOrNull(material_name);
  Mesh *mesh = Engine()->GetAssetManager()->GetMeshOrNull(mesh_name);
  if (material == nullptr) {
    material_valid = false;
    return;
  } else {
    material_valid = true;
  }
  if (mesh == nullptr) {
    mesh_valid = false;
    return;
  } else {
    mesh_valid = true;
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

    if (!mesh_valid) {
      ImGui::TextColored(ImVec4{1.0,0.0,0.0,1.0}, ICON_CI_WARNING);
      if (ImGui::IsItemHovered()) {
        ImGui::SetTooltip("Mesh could not be found!");
      }
    } else {
      ImGui::TextColored(ImVec4{0.0, 1.0, 0.0, 1.0}, ICON_CI_CHECK);
    }
    ImGui::SameLine();
    ImGui::InputText("Mesh", this->mesh_name.data(), 64);

    if (!material_valid) {
      ImGui::TextColored(ImVec4(1.0, 0.0, 0.0, 1.0), ICON_CI_WARNING);
      if (ImGui::IsItemHovered()) {
        ImGui::SetTooltip("Material could not be found!");
      }
    }else {
      ImGui::TextColored(ImVec4{0.0, 1.0, 0.0, 1.0}, ICON_CI_CHECK);
    }

    ImGui::SameLine();
    ImGui::InputText("Material", this->material_name.data(), 64);
    if (ImGui::CollapsingHeader(
            ("MaterialEdit" + std::to_string(this->GetUID())).c_str())) {
      auto mat = Engine()->GetAssetManager()->GetMaterialOrNull(material_name);
      if (mat != nullptr) {
        mat->DrawEditWidget();
      }

    }
  }




}
