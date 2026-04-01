#include "asset_manager.h"

namespace engine {

void AssetManager::Rescan() {

  for (auto model : loaded_models) {
    delete model.second;
  }






}


}
