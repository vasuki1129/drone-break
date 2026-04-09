#include "transform.h"
#include <glm/gtc/quaternion.hpp>
#include "util.h"
#include "../imgui/icon_fonts.h"
#include "../imgui/imgui.h"
#include "engine.h"
namespace engine {

static int CompSearchCallback(ImGuiInputTextCallbackData* data) {
    if (data->EventFlag == ImGuiInputTextFlags_CallbackEdit) {

    }
    return 0;
}

  void Transform::DrawWidget() {
    ImGui::InputText("Name",this->name.data(),64);

    if (ImGui::CollapsingHeader("Transform",
                                ImGuiTreeNodeFlags_CollapsingHeader |
                                ImGuiTreeNodeFlags_Framed)) {

      if(ImGui::BeginChild("TransformWidge",ImVec2(0,0),ImGuiChildFlags_Borders | ImGuiChildFlags_AutoResizeY,0)){
        ImGui::InputFloat3("position", glm::value_ptr(this->position), "%.3f");
        ImGui::InputFloat4("rotation", glm::value_ptr(this->rotation), "%.3f");
        ImGui::InputFloat3("scale", glm::value_ptr(this->scale));

        ImGui::EndChild();
      }
    }

    for (auto comp : this->components) {

      if (ImGui::CollapsingHeader((comp->GetName() + "##" + std::to_string(comp->GetUID())).c_str())) {

        if (ImGui::BeginPopupContextItem((comp->GetName() + "ContextMenu" + std::to_string(comp->GetUID())).c_str())) {
          if (ImGui::MenuItem("Remove", NULL, false, true)) {
          }
          ImGui::EndPopup();
        }


      if(ImGui::BeginChild((comp->GetName() + "Widge"+ std::to_string(comp->GetUID())).c_str(),ImVec2(0,0),ImGuiChildFlags_Borders | ImGuiChildFlags_AutoResizeY,0)){

        comp->DrawWidget();
        ImGui::EndChild();
      }
      }
    }

    if (ImGui::Button( (std::string(ICON_CI_GIST_NEW) +" ").c_str())) {
      ImGui::OpenPopup("ComponentPicker");
    }

    static std::string comp_picker_srch;
    if (comp_picker_srch.size() < 60) {
      comp_picker_srch.resize(60);
    }
    if (ImGui::BeginPopup("ComponentPicker")) {
      std::vector<std::string> results = Engine()->GetRegisteredComponentsList();


      ImGui::InputText("##COMPONENTPICKERSEARCH",comp_picker_srch.data(),60,ImGuiInputTextFlags_None,CompSearchCallback,&results);


      if (ImGui::BeginListBox("Results")) {
        for (int i = 0; i < results.size(); i++) {
          if (ImGui::Selectable(
                  (results[i] + "##" + std::to_string(i)).c_str())) {
            Component *c = Engine()->CreateComponent(results[i]);
            if (c != nullptr) {
              this->AddComponent(c);
              ImGui::CloseCurrentPopup();
            }
          }
        }
        ImGui::EndListBox();
      }
      ImGui::EndPopup();

    }
  }
void Transform::AddComponent(Component *component) {
  component->SetOwner(this);
  this->components.push_back(component);
}

void Transform::AddChild(Transform *tr) {
  tr->parent = this;
  this->children.push_back(tr);
}

Transform *Transform::FindChildByName(std::string name) {
  auto it = std::find_if(children.begin(), children.end(), [name](Transform* t) {return t->name == name;});
  if (it == children.end()) {
    std::cout << "Supplied name " + name + " not found on " +
               this->name << "\n";
    return nullptr;
  } else {
    return *it;
  }
}

Transform* Transform::RemoveChild(Transform *tr) {
  auto it = std::find(children.begin(),children.end(),tr);
  if (it == children.end()) {
    std::cout << "Supplied transform " + tr->name + " is not a child of " +
               this->name << "\n";
    return nullptr;
  } else {
    children.erase(it);
    return tr;
  }
}

Transform::Transform() {
  name.resize(64);
  name = "Transform";
  uid = GenerateUID();
  children = std::vector<Transform*>();
  components = std::vector<Component*>();
  position = glm::vec3(0.0f);
  rotation = glm::identity<glm::quat>();
  scale = glm::vec3(1.0f,1.0f,1.0f);
}

Transform::Transform(json value) {
  name.resize(64);
  name = value["name"];
  uid = value["uid"];
  children = std::vector<Transform*>();
  components = std::vector<Component*>();
}

Transform::~Transform() {
  for (auto cmp : components) {
    delete cmp;
  }

  for (auto tr : children) {
    delete tr;
  }
}

Transform::Transform(std::string name) {
  name.resize(64);
  this->name = name;
  uid = GenerateUID();
  children = std::vector<Transform*>();
  components = std::vector<Component*>();
  position = glm::vec3(0.0f);
  rotation = glm::identity<glm::quat>();
  scale = glm::vec3(1.0f,1.0f,1.0f);
}

json Transform::Save() {
  json out;
  out["name"] = this->name.c_str();
  out["uid"] = this->uid;
  out["position"][0] = this->position.x;
  out["position"][1] = this->position.y;
  out["position"][2] = this->position.z;

  out["rotation"][0] = this->rotation.x;
  out["rotation"][1] = this->rotation.y;
  out["rotation"][2] = this->rotation.z;
  out["rotation"][3] = this->rotation.w;

  out["scale"][0] = this->scale.x;
  out["scale"][1] = this->scale.y;
  out["scale"][2] = this->scale.z;

  std::vector<json> serialized_components;
  for (auto comp : components) {
    serialized_components.push_back(comp->Save());
  }
  std::vector<json> serialized_children;
  for (auto child : children) {
    serialized_children.push_back(child->Save());
  }
  out["children"] = serialized_children;
  out["components"] = serialized_components;
  return out;
}

void Transform::ProcessRender() {
  for (auto comp : components) {
    comp->render();
  }
  for (auto child : children) {
    child->ProcessRender();
  }
}

uint64_t Transform::GetUID() {
  return uid;
}

std::string Transform::GetName() { return name; }


std::vector<Transform *> Transform::GetChildren() {
  return children;
}

void Transform::ProcessTick(float dt) {
  if (components.size() != 0) {
    for (auto comp : components) {
      comp->tick(dt);
    }
  }
  if (children.size() != 0) {
    for (auto child : children) {
      child->ProcessTick(dt);
    }
  }
}

void Transform::Translate(glm::vec3 offset) {
  this->position += offset;
}
void Transform::Scale(glm::vec3 amount) { this->scale *= amount; }

void Transform::Rotate(glm::vec3 axis, float amount) {
  this->rotation = glm::rotate(this->rotation,amount,axis);
}

glm::vec3 Transform::Forward() {
  return glm::vec3(0.0f,0.0f,1.0f) * this->rotation;
}
glm::vec3 Transform::Backward() {
  return -Forward();
}
glm::vec3 Transform::Up() {
  return glm::vec3(0.0f, 1.0f, 0.0f) * this->rotation;
}
glm::vec3 Transform::Down() {
  return -Up();
}
glm::vec3 Transform::Right() {
  return glm::vec3(1.0f,0.0f,0.0f) * this->rotation;
}
glm::vec3 Transform::Left() {
  return -Right();
}

glm::mat4 Transform::GetModelMatrix() {
  auto ident = glm::identity<glm::mat4>();
  glm::mat4 scl = glm::scale(ident,GetGlobalScale());
  glm::mat4 rot = glm::mat4_cast(GetGlobalRotation());
  glm::mat4 trns = glm::translate(ident,GetGlobalPosition());
  return trns  * rot * scl;
}

glm::mat4 Transform::GetModelMatrixUnscaled() {
  auto ident = glm::identity<glm::mat4>();
  glm::mat4 rot = glm::mat4_cast(GetGlobalRotation());
  glm::mat4 trns = glm::translate(ident,GetGlobalPosition());
  return trns  * rot;
}

glm::vec3 Transform::GetGlobalPosition() {
  glm::vec3 tot(0.0f, 0.0f, 0.0f);
  Transform *tr = this;
  while (tr != nullptr) {
    tot += tr->GetLocalPosition();
    tr = tr->parent;
  }
  return tot;
}

glm::vec3 Transform::GetLocalPosition() {
  return position;
}

glm::quat Transform::GetGlobalRotation() {
  glm::quat rot = glm::identity<glm::quat>();
  Transform *tr = this;
  while (tr != nullptr) {
    rot = tr->GetLocalRotation() * rot;
    tr = tr->parent;
  }
  return rot;
}

glm::quat Transform::GetLocalRotation() {
  return rotation;
}

glm::vec3 Transform::GetGlobalScale() {
  glm::vec3 tot(1.0f, 1.0f, 1.0f);
  Transform *tr = this;
  while (tr != nullptr) {
    tot *= tr->GetLocalScale();
    tr = tr->parent;
  }
  return tot;
}


glm::vec3 Transform::GetLocalScale() {
  return scale;
}

}
