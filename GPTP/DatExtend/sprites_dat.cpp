#include <SCBW/api.h>
#include <hook_tools.h>
#include "datext.h"


namespace {

// List of address reference replacements.
s32 sprites_r[] = {/* image */   0,    0x00463A87 +4, 0x004683D5 +4, 0x0048D765 +4, 0x0048DA9F +4, 0x0049907D +4, 0x004D7A58 +4, 0x004D7ABB +4, 0x004E4CC5 +4, 0x004E4FDB +4, 0x004E5018 +4, 0x004E6640 +4,  0, 0,
                   /* health */  /*-130*/0, 0x0047A871 +2, 0x0047A90D +2, 0x0047AA6B +3, 0x004D6043 +2,  0, 0,
                   /* unknown */ 0,    0,0,
                   /* visible */ 0,    0x0049906B +2,  0, 0,
                   /* sel img */ /*-130*/0, 0x004D601E +3, 0x004D681A +4,  0, 0,
                   /* sel ofs */ /*-130*/0, 0x004D6032 +2, 0x004D6840 +2,  0, 0};

};


namespace DatExt {

  void sprites_dat_doPatch(u32 newCount) {
    datTablePatch((DatLoad*)LoadTable::Sprites_Dat, sprites_r);
  }

};