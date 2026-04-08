#pragma once
#include "../json/json.hpp"
#include <glm/glm.hpp>
#include <variant>

using json = nlohmann::json;

namespace engine
{

using ConfigValue = std::variant<int, float, std::string,glm::vec2, glm::vec3, glm::vec4>;

class EngineConfig
{
public:
  EngineConfig();
  EngineConfig(json value);
  ~EngineConfig();
  std::map<std::string,ConfigValue> current_config;

  ConfigValue GetConfigValue(std::string val);


};

}
