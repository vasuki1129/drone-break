#pragma once


#include "../json/json.hpp"
using json = nlohmann::json;


#define PROPERTY_SAVE(prop) value[#prop] = prop;

#define PROPERTY_LOAD(prop) if(value.contains(#prop)) { \
prop = value[#prop]; \
} else { \
std::cout << "property `" << #prop << "` failed to load on component " << this->name.c_str() <<" UID: " << this->uid << "\n"; \
  return false; }

#define PROPERTY_CHECK(prop) if(!value.contains(#prop)) { \
std::cout << "property `" << #prop << "` failed to load on component " << this->name.c_str() <<" UID: " << this->uid << "\n"; \
  return false;}



namespace engine {
class Saveable {
  virtual json Save() =0;
  virtual bool Load(json value)=0;
};
}
