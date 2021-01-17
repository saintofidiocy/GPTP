#pragma once

//#include <SCBW/api.h>

// Signifies the byte after the end of an array
#define ARRAY_END          (s32)0x80000000


// Used to define references to scbwdata.h variables that are modified by DatExt
#define DATEXT_VAR_REF(type, name)  extern type name;


namespace DatExt {

  namespace LoadTable {
    enum {
      Units_Dat    = 0x00513C30,
      Weapons_Dat  = 0x00513868,
      Flingy_Dat   = 0x00515A38,
      Sprites_Dat  = 0x00513FB8,
      Images_Dat   = 0x00514010,
      Upgrades_Dat = 0x005136E0,
      Techdata_Dat = 0x005137D8,
      Orders_Dat   = 0x00513EC8,
      Sfxdata_Dat  = 0x00515498,
      Portdata_Dat = 0x00513780,
      Mapdata_Dat  = 0x00512BA0
    };
  };

  namespace DatFile {
    enum {
      Units_Dat    = 0,
      Weapons_Dat  = 1,
      Flingy_Dat   = 2,
      Sprites_Dat  = 3,
      Images_Dat   = 4,
      Upgrades_Dat = 5,
      Techdata_Dat = 6,
      Orders_Dat   = 7,
      Sfxdata_Dat  = 8,
      Portdata_Dat = 9, 
      Mapdata_Dat  = 10,
      COUNT        = 11
    };
  };


  // Used in constReplace -- writes a `size`-byte value of `val*factor+add` to the zero-terminated list of pointers in `ptr`
  typedef struct {
    s32 factor;
    s32 add;
    u32 size; // 1, 2, 4
    u32 ptr[1]; // to make it an array -- zero-terminated list
  } constList;

  // Dat patching functions
  bool setDatSize(DatLoad* datTablePtr, u32 size);
  void unloadDatFiles();

  // general patching functions
  void datTablePatch(DatLoad* datTablePtr, s32* list);
  void constReplace(s32* list, u32 val);
  u32 simpleReplace(u32* list, u32 val);


  // dat patching functions -- defined in their repective .cpp files to reduce clutter
  void units_dat_doPatch(u32 newCount);
  void units_dat_flingyExpand();
  void weapons_dat_doPatch(u32 newCount);
  void flingy_dat_doPatch(u32 newCount);
  void sprites_dat_doPatch(u32 newCount);
  void images_dat_doPatch(u32 newCount);
  void upgrades_dat_doPatch(u32 newCount);
  void techdata_dat_doPatch(u32 newCount);

  void units_dat_unpatch();
  void images_dat_unpatch();
  void upgrades_dat_unpatch();
  void techdata_dat_unpatch();


}
