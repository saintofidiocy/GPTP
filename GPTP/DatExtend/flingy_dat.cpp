#include <SCBW/api.h>
#include <hook_tools.h>
#include "datext.h"


namespace {

// List of address reference replacements.
s32 flingy_r[] = {/* sprite */ 0,  0x00463A78+4, 0x004683CD+4, 0x0048D75D+4, 0x0048DA97+4, 0x00496411+4, 0x0049714F+4, 0x00497176+4, 0x0049719D+4, 0x004971C4+4, 0x004971EB+4, 0x00497212+4, 0x004E9A17+4,  0, 0,
                  /* speed */  0,  0x00454334 +3, 0x0047B8FB +3, 0x00494FA3 +3, 0x0049637E +3,  0, 0,
                  /* accel */  0,  0x0047B8AB+4, 0x00494FB0+4, 0x00496388+4,  0, 0,
                  /* halt */   0,  0x00494FBA+3,  0, 0,
                  /* turn */   0,  0x0047B85B+3, 0x00496397+2,  0, 0,
                  /* unused */ 0,  0,0,
                  /* move */   0,  0x0045431E +2, 0x004963A0 +2,  0, 0};

};


namespace DatExt {

  void flingy_dat_doPatch(u32 newCount) {
    datTablePatch((DatLoad*)LoadTable::Flingy_Dat, flingy_r);
  }

};