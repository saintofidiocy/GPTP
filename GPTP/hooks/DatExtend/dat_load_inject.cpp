#include "dat_load.h"
#include <SCBW/api.h>
#include <hook_tools.h>


namespace {

  void __declspec(naked) LoadGameData_Wrapper() {
    static DatLoad* datTable;
    static u8* filename;

    __asm {
      MOV datTable, EAX
      MOV ECX, [ESP+4]
      MOV filename, ECX
      PUSHAD
    }
    hooks::LoadGameData(datTable, filename);
    __asm {
      POPAD
      RETN 4
    }
  }

};


namespace hooks {

  void injectDatLoadHooks() {
    jmpPatch(LoadGameData_Wrapper, 0x004D2E80);
  }

};
