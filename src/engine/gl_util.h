#include <glm/glm.hpp>



//these are the uniforms that are to be implemented by all
//shaders, as such, they need to be present in every draw call
struct BaseUniforms {
  glm::mat4 model;
  glm::mat4 view;
  glm::mat4 projection;
};



