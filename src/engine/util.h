#pragma once
#include <stdint.h>


//simple incremental uid, there could (theoretically) be collisions if it rolls over
uint64_t GenerateUID();


//should only be called after a fresh wipe and load, and should be set to the highest UID
//in the loaded scene, to prevent collisions with loaded objects
void SetUIDOffset(uint64_t offset);
