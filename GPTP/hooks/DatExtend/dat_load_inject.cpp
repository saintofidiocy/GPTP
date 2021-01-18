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


  void __declspec(naked) GetUnitName_Wrapper() {
    static u16 unitId;
    static char* retval;

    __asm {
      MOV unitId, CX
      PUSHAD
    }
    retval = CUnit::getName(unitId);
    __asm {
      POPAD
      MOV EAX, retval
      RETN
    }
  }


};


namespace hooks {

  void injectDatLoadHooks() {
    jmpPatch(LoadGameData_Wrapper, 0x004D2E80); // Custom .dat file loading function
    jmpPatch(GetUnitName_Wrapper, 0x0047B090); // Reroute get unit name to CUnit's getUnitName to allow for extended unit names
  }

};
