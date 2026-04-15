#pragma once
#include <stdint.h>
#include <glm/glm.hpp>

//simple incremental uid, there could (theoretically) be collisions if it rolls over
uint64_t GenerateUID();

//should only be called after a fresh wipe and load, and should be set to the highest UID
//in the loaded scene, to prevent collisions with loaded objects
void SetUIDOffset(uint64_t offset);

glm::vec3 MoveTowards(glm::vec3 current, glm::vec3 target, float delta);
