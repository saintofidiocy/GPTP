#include <SCBW/api.h>
#include <hook_tools.h>
#include "datext.h"


namespace {

  // List of address reference replacements.
s32 sfxdata_r[] = {/* sound */ 0,   0x004BC5E9 +3, 0x004BC68D +3, 0x004BCA04 +1, 0x004BCA39 +3, 0x004DB0E5 +1,  0,
                               60,  0x004BCB29 +1,  0,
                               84,  0x0046116C +1,  0,
                               88,  0x0046102C +1,  0,
                               0,
                   /* unk1 */  0,   0x004BBEC1 +2, 0x004BC0D1 +2, 0x004BC811 +2,  0, 0,
                   /* unk2 */  0,   0x004BB970 +2, 0x004BBC52 +2, 0x004BBC65 +2, 0x004BBF15 +2, 0x004BBF1E +2, 0x004BBFF1 +2, 0x004BC06A +2, 0x004BC0BE +2, 0x004BC7AC +2, 0x004BC808 +2, 0x004BC844 +2, 0x004BCAD4 +2, 0x004BCAF1 +2, 0x004BCB09 +2, 0x004BCD42 +2,  0, 0,
                   /* unk3 */  0,   0x0048F123 +4, 0x0048F200 +4, 0x0048F2E7 +4, 0x0048F3CE +4, 0x0048F49C +4, 0x0048F56E +4, 0x0048F603 +4, 0x0048F693 +4, 0x0048F72E +4, 0x0048F81E +4, 0x0048FAE7 +4,  0,
                               260, 0x0048F8E0 +3,  0,
                               270, 0x0048F373 +3, 0x0048F418 +3,  0,
                               0,
                   /* unk4 */  0,   0x00455BD9 +3, 0x0048ECEA +3, 0x0048EDD4 +3, 0x0048EE59 +3, 0x0048EFA2 +3, 0x0048F025 +3, 0x0048F0C7 +3, 0x0048F1A4 +3, 0x004E3EB2 +3, 0x004E3F52 +3,  0,
                               2,   0x0048D169 +3,  0,
                               23,  0x0048D0ED +3, 0x0048D406 +3,  0,
                               0,0};


// Sfxdata.dat tables
            // factor, add, size,       ptr, ptr, ptr, ...,  0,  ...
s32 sfx_consts[] = {1,  0, sizeof(int), 0x004BBEB5 +2, 0x004BCA96 +2, 0x004BCD28 +2,  0,
                    1, -1, sizeof(int), 0x004BBC2A +3,  0,
                    0,0,0,0};

};


namespace DatExt {

  void sfxdata_dat_doPatch(u32 newCount) {
    datTablePatch((DatLoad*)LoadTable::Portdata_Dat, sfxdata_r);
    constReplace(sfx_consts, newCount);
  }


  //void sfxdata_dat_unpatch() {
  //}

};