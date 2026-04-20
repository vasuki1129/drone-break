#include "sound_manager.h"
#include <iostream>
namespace engine {

SoundManager::SoundManager() {
  ma_result result;
  engine = (ma_engine*) malloc(sizeof(*engine));
  result = ma_engine_init(NULL, engine);
  if (result != MA_SUCCESS) {
      std::cout << "Failed to initialize audio subsystem\n";
  }
}
SoundManager::~SoundManager() {
  ma_engine_uninit(engine);
  free(engine);
}

void SoundManager::PlaySound(std::string sound) {
  ma_engine_play_sound(engine, sound.c_str(), NULL);
}

}
