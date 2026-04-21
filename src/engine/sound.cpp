#include "sound.h"
#include "engine.h"
namespace engine {

Sound::Sound(std::string path) {
   ma_sound* snd = Engine()->GetSoundManager()->LoadSound(path);
   this->sound_handle = snd;
   if (snd != nullptr) {
       this->valid =true;

   }
}

void Sound::PlayLooped() {
    ma_sound_stop(sound_handle);
    ma_sound_set_looping(sound_handle, MA_TRUE);
    ma_sound_start(sound_handle);
}


}
