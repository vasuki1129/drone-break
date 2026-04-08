#include "engine_config.h"


namespace engine
{


  EngineConfig::EngineConfig()
  {
    current_config["editor_grid_lines_major_color"] = glm::vec3(1.0,1.0,1.0);
    current_config["editor_grid_lines_minor_color"] = glm::vec3(0.4,0.4,0.4);
    current_config["editor_grid_size"] = 1.0f;
    current_config["editor_grid_lod_fade"] = 2.0f;
  }

  EngineConfig::EngineConfig(json value){


  }

  EngineConfig::~EngineConfig(){

  }

  ConfigValue EngineConfig::GetConfigValue(std::string val)
  {

  }


}
