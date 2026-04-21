#pragma once
#include "asset.h"
#include "../miniaudio/miniaudio.h"


namespace engine
{

class Sound : public Asset {
public:
  Sound(std::string path);
  void PlayLooped();

private:
    ma_sound* sound_handle;
};


    

}
