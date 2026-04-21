#pragma once
#include "../miniaudio/miniaudio.h"
#include <string>


namespace engine {
class SoundManager {
public:
  SoundManager();
  ~SoundManager();
  void PlaySound(std::string sound);
  ma_sound* LoadSound(std::string path);
private:
    ma_engine* engine;
};

}
