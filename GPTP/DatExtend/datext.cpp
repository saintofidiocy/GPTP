#include <SCBW/api.h>
#include <hook_tools.h>
#include "datext.h"


// from structures.h
int UNIT_TYPE_COUNT     = 228;
int TECH_TYPE_COUNT     = 44;
int UPGRADE_TYPE_COUNT  = 61;
int WEAPON_TYPE_COUNT   = 130;
int FLINGY_TYPE_COUNT   = 209;
int IMAGE_TYPE_COUNT    = 999;


namespace {
// why doesn't gptp have storm functions already
typedef void* (__stdcall *SMemAlloc_type)(int size, char* filename, int line, int value); // 401
typedef u32(__stdcall *SMemFree_type)(void* ptr, char* filename, int line, int idk);   // 403
typedef u32(__stdcall *SFileCloseFile_type)(HANDLE hFile); // 253
typedef u32(__stdcall *SFileGetFileSize_type)(HANDLE hFile); // 265
typedef u32(__stdcall *SFileOpenFileEx_type)(HANDLE hArchive, char *filename, int scope, HANDLE * hFile); // 268
typedef u32(__stdcall *SFileReadFile_type)(HANDLE hFile, void *buffer, int toRead, int *read, int idk); // 269
SMemAlloc_type SMemAlloc = (SMemAlloc_type)(0x0041006A);
SMemFree_type SMemFree = (SMemFree_type)(0x00410070);
SFileCloseFile_type SFileCloseFile = (SFileCloseFile_type)(0x004100B8);
SFileGetFileSize_type SFileGetFileSize = (SFileGetFileSize_type)(0x00410142);
SFileOpenFileEx_type SFileOpenFileEx = (SFileOpenFileEx_type)(0x004100C4);
SFileReadFile_type SFileReadFile = (SFileReadFile_type)(0x00410148);
};


namespace DatExt {

  struct {
    const u8  name[13];
    const u32 datTablePtr;
    const u32 defaultSize;
    const u32 entrySize;
         bool loaded;
  } datFiles[] = {
    { "units.dat",    LoadTable::Units_Dat,    19876, 97, false },
    { "weapons.dat",  LoadTable::Weapons_Dat,   5460, 42, false },
    { "flingy.dat",   LoadTable::Flingy_Dat,    3135, 15, false },
    { "sprites.dat",  LoadTable::Sprites_Dat,   3229,  7, false },
    { "images.dat",   LoadTable::Images_Dat,   37962, 38, false },
    { "upgrades.dat", LoadTable::Upgrades_Dat,  1281, 21, false },
    { "techdata.dat", LoadTable::Techdata_Dat,   836, 19, false },
    { "orders.dat",   LoadTable::Orders_Dat,    4158, 22, false },
    { "sfxdata.dat",  LoadTable::Sfxdata_Dat,  10296,  9, false },
    { "portdata.dat", LoadTable::Portdata_Dat,  1320, 12, false },
    { "mapdata.dat",  LoadTable::Mapdata_Dat,    260,  4, false },
  };


  StringTbl* unitNamesTbl = NULL;


  bool setDatSize(DatLoad* datTablePtr, u32 size) {
    u32 i,j;
    u32 newCount, memCount;
    void* newMem = NULL;

    // get dat file table index
    for (i = 0; i < DatFile::COUNT && (u32)datTablePtr != datFiles[i].datTablePtr; i++);

    // Unknown file; return success to load normally
    if (i == DatFile::COUNT) return true;

    // Default file; return success to load normally
    if (size == datFiles[i].defaultSize) return true;

    // Not an integer number of entries -- invalid file
    if ((size % datFiles[i].entrySize) != 0) return false;

    // Dat file already patched; return success
    if (datFiles[i].loaded) return true;

    // Get number of entries
    newCount = size / datFiles[i].entrySize;
    memCount = newCount;

    // units.dat special cases
    if (i == DatFile::Units_Dat) {
      // Count must be a multiple of 12, so round up
      if ((newCount % 12) != 0) {
        memCount += 12 - (newCount % 12);
      }

      // Maximum because of FireGraft
      if (memCount > 912) return false;

      datTablePtr[0].length = 2; // flingy ID to u16

      // these normally have a length of 2 and the number of entries multiplied accordingly, but for simplicity the length will be multiplied here instead
      datTablePtr[36].length = 4; // placement box
      datTablePtr[37].length = 4; // addon position
      datTablePtr[38].length = 8; // unit size
    }

    // portdata.dat special cases
    if (i == DatFile::Portdata_Dat) {
      // Count must be a multiple of 5, so round up
      if ((newCount % 5) != 0) {
        memCount += 5 - (newCount % 5);
      }
    }

    // Load new entry counts
    for (j = 0; datTablePtr[j].address != NULL; j++) {
      datTablePtr[j].entries = newCount;

      newMem = calloc(memCount, datTablePtr[j].length);
      if (newMem == NULL) {
        // error allocating memory
        return false; // or something
      }
      datTablePtr[j].address = newMem;
    }

    // Load patches for dat file
    switch (i) {
      case DatFile::Units_Dat:
        units_dat_doPatch(memCount); // rounded up to a multiple of 12
        UNIT_TYPE_COUNT = newCount;
        break;
      case DatFile::Weapons_Dat:
        weapons_dat_doPatch(newCount);
        WEAPON_TYPE_COUNT = newCount;
        break;
      case DatFile::Flingy_Dat:
        flingy_dat_doPatch(newCount);
        FLINGY_TYPE_COUNT = newCount;
        break;
      case DatFile::Sprites_Dat:
        sprites_dat_doPatch(newCount);
        break;
      case DatFile::Images_Dat:
        images_dat_doPatch(newCount);
        IMAGE_TYPE_COUNT = newCount;
        break;
      case DatFile::Upgrades_Dat:
        upgrades_dat_doPatch(newCount);
        UPGRADE_TYPE_COUNT = newCount;
        break;
      case DatFile::Techdata_Dat:
        techdata_dat_doPatch(newCount);
        TECH_TYPE_COUNT = newCount;
        break;
      case DatFile::Orders_Dat:
        orders_dat_doPatch(newCount);
        break;
      case DatFile::Sfxdata_Dat:
        sfxdata_dat_doPatch(newCount);
        break;
      case DatFile::Portdata_Dat:
        //portdata_dat_doPatch(memCount); // rounded up to a multiple of 5
        break;
      case DatFile::Mapdata_Dat:
        //mapdata_dat_doPatch(newCount);
        break;
    }

    datFiles[i].loaded = true;
    return true;
  }



  // Frees allocated memory
  void unloadDatFiles() {
    u32 i, j;
    DatLoad* datTablePtr;

    for (i = 0; i < DatFile::COUNT; i++) {
      datTablePtr = (DatLoad*)(datFiles[i].datTablePtr);
      if (i == DatFile::Units_Dat && datTablePtr[0].address != (void*)(0x0059CCCC)) { // Flingy ID
        if (datTablePtr[0].address != NULL) {
          free(datTablePtr[0].address);
          datTablePtr[0].address = (void*)(0x0059CCCC);
        }
      }
      if (datFiles[i].loaded == false) continue;
      for (j = 0; datTablePtr[j].entries != 0; j++) {
        if (datTablePtr[j].address != NULL) {
          free(datTablePtr[j].address);
          datTablePtr[j].address = NULL;
        }
      }
    }

    units_dat_unpatch();
    images_dat_unpatch();
    upgrades_dat_unpatch();
    techdata_dat_unpatch();

    if (unitNamesTbl != NULL) {
      SMemFree(unitNamesTbl, __FILE__, __LINE__, 0);
      unitNamesTbl = NULL;
    }
  }


  // Loads rez\unitnames.tbl, if it exists, for extended unit ID names
  void loadUnitNamesTbl() {
    HANDLE hFile = NULL;
    u32 size = 0;
    int read;
    void* data = NULL;

    if (unitNamesTbl != NULL) return; // already loaded

    if (SFileOpenFileEx(NULL, "rez\\unitnames.tbl", 0, &hFile)) {
      size = SFileGetFileSize(hFile);
      if (size > 2) {
        data = SMemAlloc(size, __FILE__, __LINE__, 0);
        if (data != NULL) {
          if (SFileReadFile(hFile, data, size, &read, 0)) {
            // successfully loaded
            unitNamesTbl = (StringTbl*)data;
          }
          else {
            // there was an error -- free memory
            SMemFree(data, __FILE__, __LINE__, 0);
          }
        }
      }
      SFileCloseFile(hFile);
    }
  }



  // general patching functions
  
  // Overwrites references to dat file arrays
  void datTablePatch(DatLoad* datTablePtr, s32* list) {
    u32 i, j;
    u32 offs;
    // Null-terminated list of null-terminated lists of addresses
    // First value is table offset for the sub-list (i.e., 12 would mean the new address + 12 bytes is written)

    for (i = 0, j = 0; datTablePtr[i].entries != 0; i++, j++) {
      do {
        // Get array offset
        if (list[j] == ARRAY_END) {
          offs = (u32)(datTablePtr[i].address) + datTablePtr[i].entries * datTablePtr[i].length;
        } else {
          offs = (u32)(datTablePtr[i].address) + list[j];
        }

        // Apply patches
        for (j++; list[j] != 0; j++) {
          memoryPatch(list[j], offs);
        }
        j++;
      } while (list[j] != 0);
    }
  }

  // Writes a value with a list of modifiers to a list of addresses, defined by "constList" struct
  void constReplace(s32* list, u32 val) {
    u32 i;
    s32 newVal;
    // - Null-terminated list of null-terminated lists of addresses
    // - First value is the #entries factor, second value is a value to be added to the product
    
    // cl->ptr[j] == 0 terminator of previous list, so cl->ptr[j+1] is the beginning of the next struct.
    for (constList *cl = (constList*)list; cl->ptr[0] != 0; cl = (constList*)&cl->ptr[i + 1]) {
      newVal = val * cl->factor + cl->add;
      for (i = 0; cl->ptr[i] != 0; i++) {
        memoryPatch(cl->ptr[i], (u8*)&newVal, cl->size);
      }
    }
  }

  // Writes a constant value to a list of addresses
  u32 simpleReplace(u32* list, u32 val) {
    u32 i;
    for (i = 0; list[i] != 0; i++) {
      memoryPatch(list[i], val);
    }
    return i;
  }


};
