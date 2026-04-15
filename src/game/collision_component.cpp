#include "collision_component.h"
#include "../engine/input.h"
#include "../engine/engine.h"
#include "../engine/mesh.h"
#include "../engine/physics.h"

namespace engine {
class PhysicsHandler;

CollisionComponent::CollisionComponent() :engine::Component(){
  this->name = "CollisionComponent";
  this->component_type="CollisionComponent";
}

void CollisionComponent::tick(float dt) {

    for(auto col : *engine::Engine()->GetPhysics()->GetColliders())
    {
        if(CheckCollision(col, nullptr))
        {
            colliding = true;
            break;
        }
        else
        {
            colliding = false;
        }
    }

}

void CollisionComponent::DrawWidget() {
  ImGui::Text("Bounds");
  ImGui::InputFloat("X",&this->bounds.x);
  ImGui::InputFloat("Y",&this->bounds.y);
  ImGui::InputFloat("Z",&this->bounds.z);

  ImGui::Text("%d", colliding);

}

json CollisionComponent::Save() {
  json j;
  j["name"] = name;
  j["uid"] = uid;
  j["component_type"] = component_type;
  j["offset"][0] = offset.x;
  j["offset"][1] = offset.y;
  j["offset"][2] = offset.z;
  j["bounds"][0] = bounds.x;
  j["bounds"][1] = bounds.y;
  j["bounds"][2] = bounds.z;

  return j;
}


bool CollisionComponent::Load(json value) {

  PROPERTY_LOAD(name)
  PROPERTY_LOAD(uid)
  PROPERTY_LOAD(component_type)

  this->offset.x = value["offset"][0];
  this->offset.y = value["offset"][1];
  this->offset.z = value["offset"][2];
  this->bounds.x = value["bounds"][0];
  this->bounds.y = value["bounds"][1];
  this->bounds.z = value["bounds"][2];

  return true;
}


bool CollisionComponent::CheckCollision(CollisionComponent *other,
                                        glm::vec3 *vector_out) {
//so we need like the 6 face normals first, which are just the direction vectors of the model matrix
//and their negatives

  float ra, rb;
  glm::mat3 R, AbsR;

  glm::vec3 basis_vectors_a[3] ={ this->owner->Right(), this->owner->Up(), this->owner->Forward()};
  glm::vec3 basis_vectors_b[3] ={ other->GetOwner()->Right(), other->GetOwner()->Up(), other->GetOwner()->Forward()};

  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      R[i][j] = glm::dot(basis_vectors_a[i],basis_vectors_b[j]);
    }
  }
  glm::vec3 t = other->GetOwner()->GetGlobalPosition() -
           this->GetOwner()->GetGlobalPosition();
  t = glm::vec3(glm::dot(t, basis_vectors_a[0]),
                glm::dot(t, basis_vectors_a[1]),
                glm::dot(t, basis_vectors_a[2]));

  for (int i = 0; i < 3; i++)
    for (int j = 0; j < 3; j++)
      AbsR[i][j] = std::abs(R[i][j]) + FLT_EPSILON;


  //test A normals
  ra = this->bounds.x;
  rb = other->bounds.x * AbsR[0][0] + other->bounds.y * AbsR[0][1] +
       other->bounds.z * AbsR[0][2];
  if(std::abs(t[0])>ra + rb) return false;

  ra = this->bounds.y;
  rb = other->bounds.x * AbsR[1][0] + other->bounds.y * AbsR[1][1] +
       other->bounds.z * AbsR[1][2];
  if(std::abs(t[1])>ra + rb) return false;

  ra = this->bounds.z;
  rb = other->bounds.x * AbsR[2][0] + other->bounds.y * AbsR[2][1] +
       other->bounds.z * AbsR[2][2];
  if(std::abs(t[2])>ra + rb) return false;

  //test B normals
  ra = this->bounds.x * AbsR[0][0] + this->bounds.y * AbsR[1][0] +
       this->bounds.z * AbsR[2][0];
  rb = other->bounds.x;
  if (std::abs(t[0] * R[0][0] + t[1] * R[1][0] + t[2] * R[2][0]) > ra + rb)
    return false;

  ra = this->bounds.x * AbsR[0][1] + this->bounds.y * AbsR[1][1] +
       this->bounds.z * AbsR[2][1];
  rb = other->bounds.y;
  if (std::abs(t[0] * R[0][1] + t[1] * R[1][1] + t[2] * R[2][1]) > ra + rb)
    return false;

  ra = this->bounds.x * AbsR[0][2] + this->bounds.y * AbsR[1][2] +
       this->bounds.z * AbsR[2][2];
  rb = other->bounds.z;
  if (std::abs(t[0] * R[0][2] + t[1] * R[1][2] + t[2] * R[2][2]) > ra + rb)
    return false;

  return true;
}




void CollisionComponent::init()
{
    Engine()->GetPhysics()->RegisterCollider(this);
}



void CollisionComponent::destroy()
{

    Engine()->GetPhysics()->DeregisterCollider(this);
}


void CollisionComponent::editor_render() {
  engine::Mesh* mesh = engine::Engine()->GetAssetManager()->GetMeshOrNull("editor_shapes.box");
  engine::Material *material =
      engine::Engine()->GetAssetManager()->GetMaterialOrNull("editor_box_mtl");

  glm::mat4 model_mat = glm::scale(this->owner->GetModelMatrixUnscaled(),this->bounds);

  BaseUniforms base{
      .model = model_mat,
      .camera = engine::Engine()
                    ->GetSceneLoader()
                    ->GetCurrentScene()
                    ->GetCurrentCameraMatrix(),
  };
  glLineWidth(1.0);
  glDisable(GL_CULL_FACE);
  mesh->DrawWireframe(base, material);
  glEnable(GL_CULL_FACE);
}

FACTORY_DEF(CollisionComponent);
}
