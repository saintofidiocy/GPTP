#pragma once
#include <SCBW/api.h>

namespace hooks {
  void LoadGameData(DatLoad* datTable, u8* filename);

  void injectDatLoadHooks();
};
