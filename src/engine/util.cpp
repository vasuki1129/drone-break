#include "util.h"

uint64_t uid_ctr = 0; //start at 1 so 0 can still be null

uint64_t GenerateUID() {
  return ++uid_ctr;
}

void SetUIDOffset(uint64_t offset) {
  uid_ctr = offset;
}

glm::vec3 MoveTowards(glm::vec3 current, glm::vec3 target, float delta) {
    glm::vec3 direction = target - current;
    float dist = glm::length(direction);
    if (dist <= delta || dist == 0) {
        return target;
    }
    return current + (direction / dist) * delta;
}
