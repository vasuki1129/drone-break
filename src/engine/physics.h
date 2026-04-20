#pragma once
#include <glm/glm.hpp>
#include "camera_component.h"

namespace engine
{

class CollisionComponent;
class TriggerComponent;

struct Ray
{
  glm::vec3 position;
  glm::vec3 direction;
};



bool TestRayOBBIntersection(
    glm::vec3 ray_origin,    // Ray origin, in world space
    glm::vec3 ray_direction, // Ray direction (NOT target position!), in world
                             // space. Must be normalize()'d.
    glm::vec3 aabb_min, // Minimum X,Y,Z coords of the mesh when not transformed
                        // at all.
    glm::vec3 aabb_max, // Maximum X,Y,Z coords. Often aabb_min*-1 if your mesh
                        // is centered, but it's not always the case.
    glm::mat4 ModelMatrix, // Transformation applied to the mesh (which will
                           // thus be also applied to its bounding box)
    float &intersection_distance // Output : distance between ray_origin and the
                                 // intersection with the OBB
);

class PhysicsHandler {
public:
  bool CheckTrigger(CollisionComponent* collider, int trigger_group);

  void RegisterCollider(CollisionComponent* collider);
  void DeregisterCollider(CollisionComponent *collider);
  std::vector<CollisionComponent*>* GetColliders();

  void RegisterTrigger(TriggerComponent* trigger);
  void DeregisterTrigger(TriggerComponent* trigger);
  std::vector<TriggerComponent*>* GetTriggers();

private:
  std::vector<CollisionComponent*> registered_colliders;
  std::vector<TriggerComponent*> registered_triggers;
};












}
