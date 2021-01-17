#include "dat_load.h"
#include <SCBW/api.h>
#include <DatExtend/datext.h>


//helper functions def
namespace {
  void* fastFileRead(u32 arg1, u32* psize, const u8* filename, u32 arg4, u32 arg5, const char* dbg_file, u32 dbg_line);
  void SysWarn_FileNotFound(u32 code, const u8* filename);
  typedef u32(__stdcall *SMemFree_type)(void* ptr, char* filename, int line, int idk); // why doesn't gptp have storm functions already
  SMemFree_type SMemFree = (SMemFree_type)(0x00410070);
};

namespace hooks {

  void LoadGameData(DatLoad* datTable, u8* filename) {
    u32 size = 0;
    u32 i;
    u8* data;
    u32 length;
    u32 pos;

    data = (u8*)fastFileRead(0, &size, filename, 0, 0, "Starcraft\\SWAR\\lang\\gamedata.cpp", 356);
    pos = 0;
    
    // DatExt -- Patch dat file
    if (DatExt::setDatSize(datTable, size) == false) {
      SysWarn_FileNotFound(24, filename); // invalid file
    }

    for (i = 0; datTable[i].address != NULL; i++) {
      length = datTable[i].entries * datTable[i].length;
      if (length > size) break;
      memcpy(datTable[i].address, data + pos, length);
      size -= length;
      pos += length;
    }

    if (size != 0) {
      SysWarn_FileNotFound(24, filename);
    }

    SMemFree(data, "Starcraft\\SWAR\\lang\\gamedata.cpp", 402, 0);

    // Apply Flingy Expand patch to default units.dat file, so that flingy datatype will be consistent whether DatExt is used or not
    if (datTable == (DatLoad*)DatExt::LoadTable::Units_Dat && datTable[0].length == 1) {
      DatExt::units_dat_flingyExpand();
    }
  }

}; // hooks


//helper functions def
namespace {
  const u32 Func__fastFileRead = 0x004D2D10;
  const u32 Func__SysWarn_FileNotFound = 0x004212C0;

  void* fastFileRead(u32 arg1, u32* psize, const u8* filename, u32 arg4, u32 arg5, const char* dbg_file, u32 dbg_line) {
    static void* result;
    __asm {
      PUSHAD
      MOV ECX, arg1
      MOV EAX, psize
      PUSH dbg_line
      PUSH dbg_file
      PUSH arg5
      PUSH arg4
      PUSH filename
      CALL Func__fastFileRead
      MOV result, EAX
      POPAD
    }
    return result;
  }

  void SysWarn_FileNotFound(u32 code, const u8* filename) {
    __asm {
      MOV EBX, code
      PUSH filename
      CALL Func__SysWarn_FileNotFound
    }
  }
}; // unnamed namespace
