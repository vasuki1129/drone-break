#pragma once
#include "../miniaudio/miniaudio.h"
#include <string>


namespace engine {
class SoundManager {
public:
  SoundManager();
  ~SoundManager();
  void PlaySound(std::string sound);
private:
    ma_engine* engine;
};

}
