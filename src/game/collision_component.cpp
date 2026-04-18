#include "collision_component.h"
#include "player_component.h"
#include "../engine/input.h"
#include "../engine/engine.h"
#include "../engine/mesh.h"
#include "../engine/physics.h"
#include "enemy_component.h"
#include <iostream>
namespace engine {
class PhysicsHandler;

CollisionComponent::CollisionComponent() :engine::Component(){
  this->name = "CollisionComponent";
  this->component_type="CollisionComponent";
}

void CollisionComponent::tick(float dt) {
  if(!should_tick) return;
  for (auto col : *engine::Engine()->GetPhysics()->GetColliders()) {
    if (col->GetUID() == this->uid)
      continue;
    glm::vec3 mtv = glm::vec3(0.0f,0.0f,0.0f);
    if (CheckCollision(col, &mtv)) {
      this->GetOwner()->Translate(-mtv);
      PlayerComponent *ply =
          (PlayerComponent *)this->GetOwner()->GetComponent("PlayerComponent");
      if (ply == nullptr) {
        EnemyComponent *enmy =
            (EnemyComponent *)this->GetOwner()->GetComponent("EnemyComponent");

      } else {
        ply->SetVelocity(0.99f * ply->GetVelocity() );
      }
    } else {
    }
  }
}

void CollisionComponent::DrawWidget() {
  ImGui::Text("Bounds");
  ImGui::InputFloat("X",&this->bounds.x);
  ImGui::InputFloat("Y",&this->bounds.y);
  ImGui::InputFloat("Z",&this->bounds.z);
  ImGui::Checkbox("Should Tick", &this->should_tick);
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
  j["should_tick"] = should_tick;
  return j;
}

bool CollisionComponent::Load(json value) {

  PROPERTY_LOAD(name)
  PROPERTY_LOAD(uid)
  PROPERTY_LOAD(component_type)
  PROPERTY_LOAD(should_tick)

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

  glm::vec3 bounds_a = this->bounds / 2.0f;
  glm::vec3 bounds_b = other->bounds / 2.0f;
  float t_proj;
  float overlap;
  float min_overlap = 1000000;
  glm::vec3 mtv = glm::vec3(0,0,0);
  bool collided = true;



  //test A normals
  ra = bounds_a.x;
  rb = bounds_b.x * AbsR[0][0] + bounds_b.y * AbsR[0][1] +
       bounds_b.z * AbsR[0][2];
  t_proj = t[0];
  overlap = (ra + rb) - std::abs(t_proj);
  if (overlap < min_overlap) {
    min_overlap = overlap;
    mtv = t_proj < 0 ? -this->GetOwner()->Right()*overlap : this->GetOwner()->Right()*overlap;
  }
  if(std::abs(t[0])>ra + rb) collided = false;

  ra = bounds_a.y;
  rb = bounds_b.x * AbsR[1][0] + bounds_b.y * AbsR[1][1] +
       bounds_b.z * AbsR[1][2];
  t_proj = t[1];
  overlap = (ra + rb) - std::abs(t_proj);
  if (overlap < min_overlap) {
    min_overlap = overlap;
    mtv = t_proj < 0 ? -this->GetOwner()->Up()*overlap : this->GetOwner()->Up()*overlap;
  }
  if(std::abs(t[1])>ra + rb) collided = false;

  ra = bounds_a.z;
  rb = bounds_b.x * AbsR[2][0] + bounds_b.y * AbsR[2][1] +
       bounds_b.z * AbsR[2][2];
  t_proj = t[2];
  overlap = (ra + rb) - std::abs(t_proj);
  if (overlap < min_overlap) {
    min_overlap = overlap;
    mtv = t_proj < 0 ? -this->GetOwner()->Forward()*overlap : this->GetOwner()->Forward()*overlap;
  }
  if(std::abs(t[2])>ra + rb) collided = false;


  //test B normals
  ra = bounds_a.x * AbsR[0][0] + bounds_a.y * AbsR[1][0] +
       bounds_a.z * AbsR[2][0];
  rb = bounds_b.x;
  t_proj = t[0] * R[0][0] + t[1] * R[1][0] + t[2] * R[2][0];

  overlap = (ra + rb) - std::abs(t_proj);
  if (overlap < min_overlap) {
    min_overlap = overlap;
    mtv = t_proj < 0 ? -other->GetOwner()->Right()*overlap : other->GetOwner()->Right()*overlap;
  }
  if (std::abs(t_proj) > ra + rb)
    collided = false;

  ra = bounds_a.x * AbsR[0][1] + bounds_a.y * AbsR[1][1] +
       bounds_a.z * AbsR[2][1];
  rb = bounds_b.y;
  t_proj = t[0] * R[0][1] + t[1] * R[1][1] + t[2] * R[2][1];
  overlap = (ra + rb) - std::abs(t_proj);
  if (overlap < min_overlap) {
    min_overlap = overlap;
    mtv = t_proj < 0 ? -other->GetOwner()->Up()*overlap : other->GetOwner()->Up()*overlap;
  }
  if (std::abs(t_proj) > ra + rb)
    collided = false;

  ra = bounds_a.x * AbsR[0][2] + bounds_a.y * AbsR[1][2] +
       bounds_a.z * AbsR[2][2];
  rb = bounds_b.z;
  t_proj = t[0] * R[0][2] + t[1] * R[1][2] + t[2] * R[2][2];
  overlap = (ra + rb) - std::abs(t_proj);
  if (overlap < min_overlap) {
    min_overlap = overlap;
    mtv = t_proj < 0 ? -other->GetOwner()->Forward()*overlap : other->GetOwner()->Forward()*overlap;
  }
  if (std::abs(t_proj) > ra + rb)
    collided = false;

  //cross-product axes

  ra = bounds_a.y * AbsR[2][0] + bounds_a.z * AbsR[1][0];
  rb = bounds_b.y * AbsR[0][2] + bounds_b.z * AbsR[0][1];
  t_proj = t[2] * R[1][0] - t[1] * R[2][0];
  overlap = (ra + rb) - std::abs(t_proj);
  if (overlap < min_overlap) {
    min_overlap = overlap;
    glm::vec3 axis = glm::normalize(glm::cross(this->GetOwner()->Right(), other->GetOwner()->Right())) * overlap;
    mtv = t_proj < 0 ? -axis : axis;

  }
  if(std::abs(t_proj) > ra+rb) collided = false;

  ra = bounds_a.y * AbsR[2][1] + bounds_a.z * AbsR[1][1];
  rb = bounds_b.x * AbsR[0][2] + bounds_b.z * AbsR[0][0];
  t_proj = t[2] * R[1][1] - t[1] * R[2][1];
  overlap = (ra + rb) - std::abs(t_proj);
  if (overlap < min_overlap) {
    min_overlap = overlap;
    glm::vec3 axis = glm::normalize(glm::cross(this->GetOwner()->Right(), other->GetOwner()->Up())) * overlap;
    mtv = t_proj < 0 ? -axis : axis;
  }
  if (std::abs(t_proj) > ra + rb) collided = false;

  ra = bounds_a.y * AbsR[2][2] + bounds_a.z * AbsR[1][2];
  rb = bounds_b.x * AbsR[0][1] + bounds_b.y * AbsR[0][0];
  t_proj = t[2] * R[1][2] - t[1] * R[2][2];
  overlap = (ra + rb) - std::abs(t_proj);
  if (overlap < min_overlap) {
    min_overlap = overlap;
    glm::vec3 axis = glm::normalize(glm::cross(this->GetOwner()->Right(), other->GetOwner()->Forward())) * overlap;
    mtv = t_proj < 0 ? -axis : axis;
  }
  if (std::abs(t_proj) > ra + rb) collided = false;

  ra = bounds_a.x * AbsR[2][0] + bounds_a.z * AbsR[0][0];
  rb = bounds_b.y * AbsR[1][2] + bounds_b.z * AbsR[1][1];
  t_proj = t[0] * R[2][0] - t[2] * R[0][0];
  overlap = (ra + rb) - std::abs(t_proj);
  if (overlap < min_overlap) {
    min_overlap = overlap;
    glm::vec3 axis = glm::normalize(glm::cross(this->GetOwner()->Up(), other->GetOwner()->Right())) * overlap;
    mtv = t_proj < 0 ? -axis : axis;
  }
  if (std::abs(t_proj) > ra + rb) collided = false;

  ra = bounds_a.x * AbsR[2][1] + bounds_a.z * AbsR[0][1];
  rb = bounds_b.x * AbsR[1][2] + bounds_b.z * AbsR[1][0];
  t_proj = t[0] * R[2][1] - t[2] * R[0][1];
  overlap = (ra + rb) - std::abs(t_proj);
  if (overlap < min_overlap) {
    min_overlap = overlap;
    glm::vec3 axis = glm::normalize(glm::cross(this->GetOwner()->Up(), other->GetOwner()->Up())) * overlap;
    mtv = t_proj < 0 ? -axis : axis;
  }
  if (std::abs(t_proj) > ra + rb) collided = false;

  ra = bounds_a.x * AbsR[2][2] + bounds_a.z * AbsR[0][2];
  rb = bounds_b.x * AbsR[1][1] + bounds_b.y * AbsR[1][0];
  t_proj = t[0] * R[2][2] - t[2] * R[0][2];
  overlap = (ra + rb) - std::abs(t_proj);
  if (overlap < min_overlap) {
    min_overlap = overlap;
    glm::vec3 axis = glm::normalize(glm::cross(this->GetOwner()->Up(), other->GetOwner()->Forward())) * overlap;
    mtv = t_proj < 0 ? -axis : axis;
  }
  if (std::abs(t_proj) > ra + rb) collided = false;

  ra = bounds_a.x * AbsR[1][1] + bounds_a.y * AbsR[0][1];
  rb = bounds_b.x * AbsR[2][2] + bounds_b.z * AbsR[2][0];
  t_proj = t[1] * R[0][1] - t[0] * R[1][1];
  overlap = (ra + rb) - std::abs(t_proj);
  if (overlap < min_overlap) {
    min_overlap = overlap;
    glm::vec3 axis = glm::normalize(glm::cross(this->GetOwner()->Forward(), other->GetOwner()->Up())) * overlap;
    mtv = t_proj < 0 ? -axis : axis;
  }
  if (std::abs(t_proj) > ra + rb) collided = false;

  ra = bounds_a.x * AbsR[1][2] + bounds_a.y * AbsR[0][2];
  rb = bounds_b.x * AbsR[2][1] + bounds_b.y * AbsR[2][0];
  t_proj = t[1] * R[0][2] - t[0] * R[1][2];
  overlap = (ra + rb) - std::abs(t_proj);
  if (overlap < min_overlap) {
    min_overlap = overlap;
    glm::vec3 axis = glm::normalize(glm::cross(this->GetOwner()->Forward(), other->GetOwner()->Forward())) * overlap;
    mtv = t_proj < 0 ? -axis : axis;
  }
  if (std::abs(t_proj) > ra + rb) collided = false;


  ra = bounds_a.x * AbsR[1][0] + bounds_a.y * AbsR[0][0];
  rb = bounds_b.y * AbsR[2][2] + bounds_b.z * AbsR[2][1];
  t_proj = t[1] * R[0][0] - t[0] * R[1][0];
  overlap = (ra + rb) - std::abs(t_proj);
  if (overlap < min_overlap) {
    min_overlap = overlap;
    glm::vec3 axis = glm::normalize(glm::cross(this->GetOwner()->Forward(), other->GetOwner()->Right())) * overlap;
    mtv = t_proj < 0 ? -axis : axis;
  }
  if (std::abs(t_proj) > ra + rb) collided = false;

  if (collided) {
    if (vector_out != nullptr) {
      *vector_out = mtv;
    }
    return true;
  } else {
    return false;
  }

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
