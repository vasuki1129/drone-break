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

ma_sound *SoundManager::LoadSound(std::string path) {
  ma_sound* snd = new ma_sound();
  ma_result result =
      ma_sound_init_from_file(engine, path.c_str(), 0, NULL, NULL, snd);
  if (result != MA_SUCCESS) {
    std::cout << "Failed to load sound: " << path << "\n";
  }
  return snd;
}



}
