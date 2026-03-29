#pragma once


#include "../json/json.hpp"

using json = nlohmann::json;



namespace engine {
class Saveable {
  virtual json Save() =0;
};
}
