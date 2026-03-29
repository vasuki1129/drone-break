#include "util.h"

uint64_t uid_ctr = 0; //start at 1 so 0 can still be null

uint64_t GenerateUID() { return ++uid_ctr; }


void SetUIDOffset(uint64_t offset) {
  uid_ctr = offset;

}
