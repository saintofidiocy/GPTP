#include <SCBW/api.h>
#include <hook_tools.h>
#include "datext.h"


namespace {

// List of address reference replacements.
s32 weapons_r[] = {/* label */        0,   0x00457720 +4, 0x00457788 +4, 0x004577FB +4, 0,0,
                   /* graphics */     0,   0x00475A33 +3, 0x00479C38 +3, 0x00479D14 +3, 0x0048BED7 +3, 0,0,
                   /* unused */       0,   0,0,
                   /* target flags */ 0,   0x00475CEE +4, 0x00475D19 +4, 0,0,
                   /* min range */    0,   0x004400F0 +3, 0x00440586 +3, 0x00440590 +3, 0x004405A5 +3, 0x004405BA +3, 0x00462FCB +3, 0x00466077 +3, 0x00476525 +3, 0x00476682 +3, 0x004768FB +3, 0x00477C48 +3, 0x004787A4 +3, 0x00478C15 +3, 0x0047BB44 +3, 0x0047C5D4 +3, 0x0047C688 +3, 0,0,
                   /* max range */    0,   0x004758B5 +3, 0x004758D6 +3, 0x004758F7 +3, 0x00475910 +3, 0x00475945 +3, 0x0048C16B +3, 0x0049E059 +3, 0x0049E078 +3, 0x0049E0B6 +3, 0x0049E0D5 +3, 0x0049E115 +3, 0x0049E134 +3, 0x0049E172 +3, 0x0049E191 +3, 0x004312C0 +3, 0,0,
                   /* dmg upgrade */  0,   0x0042579D +4, 0x00475E47 +4, 0x00475EC7 +4, 0x0048ACE5 +4, 0,0,
                   /* weapon type */  0,   0x0047978E +2, 0x004799D2 +2, 0x00479A05 +2, 0x00479A43 +3, 0x00479A99 +2, 0,0,
                   /* wpn behavior */ 0,   0x004418E5 +2, 0x0044190C +3, 0x00479C99 +2, 0x0048B7AE +2, 0x0048BD67 +2, 0x0048C02C +3, 0,0,
                   /* remove after */ 0,   0x0048BF1B +2, 0,0,
                   /* expl type */    0,   0x0048ACD8 +2, 0x0048B58C +2, 0x0048B77E +3, 0,0,
                   /* inner splash */ 0,   0x00465EC6 +4, 0x0048B195 +3, 0x0048B5FF +4, 0x0048B6B3 +4, 0,
                                      66,  0x00492BAB +2, 0,
                                      0,
                   /* med splash */   0,   0x0048B647 +4, 0,0,
                   /* outer splash */ 0,   0x0048B181 +3, 0x0048B5C0 +4, 0x0048B828 +4, 0x0048B8CC +4, 0,
                                      108, 0x004789D3 +3, 0x00478AC6 +3, 0,
                                      0,
                   /* dmg amount */   0,   0x00475F41 +4, 0x00479BB3 +4, 0x0048ACF1 +4, 0x004BF0CE +1, 0x004BF0D3 +1, 0x004BF277 +1, 0x004BF425 +1, 0x004CAC5B +3, 0x004CAC8C +3, 0x004CAE1B +3, 0x004CAE4C +3, 0x00431211 +4, 0x004312B8 +4, 0,
                                      68,  0x0045550D +3, 0x0045559D +3, 0,
                                      120, 0x00493094 +3, 0x004F4B7C +3, 0,
                                      0,
                   /* dmg bonus */    0,   0x00475E9D +4, 0x00475EE4 +4, 0x00475EFF +4, 0x0048AD1B +4, 0x004BF0F4 +1, 0x004BF0F9 +1, 0x004BF28B +1, 0x004BF43D +1, 0x004CAC6A +3, 0x004CAC9B +3, 0x004CAE2A +3, 0x004CAE5B +3, 0,0,
                   /* wpn cooldown */ 0,   0x00475DCC +3, 0x00431219 +3, 0x004312B0 +3, 0,
                                      22,  0x00454E53 +2, 0x00455515 +3, 0x00455594 +3, 0,
                                      0,
                   /* dmg factor */   0,   0x00475E50 +2, 0x00475F1B +2, 0x00479C65 +2, 0x00479D4C +2, 0x00479DB0 +2, 0x004D80ED +2, 0x0043120A +3, 0x004312A8 +3, 0,0,
                   /* attack angle */ 0,   0x004675E0 +3, 0x00467E3F +3, 0x00475C67 +3, 0x00478C73 +3, 0,0,
                   /* launch spin */  0,   0x0048BF52 +2, 0,0,
                   /* fwd offset */   0,   0x00479CDD +3, 0x004D819A +2, 0,0,
                   /* upward offs */  0,   0x00479CF1 +3, 0,0,
                   /* target error */ 0,   0x0046F02B +4, 0,0,
                   /* icon */         0,   0x00425840 +4, 0,0};



s32 weapons_consts[] = {2, 0, sizeof(int),   0x004BF438 +1, 0x004BF286 +1, 0x004BF272 +1, 0x004BF420 +1, 0,

                    // Code replacements
                      // replace JNB with JE
                      0, 0x74,       sizeof(char),  0x00475CE5, 0x004400EB, 0x00462FC6, 0x00466072, 0x004768F6, 0x00477C43, 0x0047879F, 0x0047BB3F, 0x0047C5CF, 0x0047C683, 0x0049E057, 0x0049E076, 0x0049E0B4, 0x0049E0D3, 0x0049E113, 0x0049E132, 0x0049E170, 0x0049E18F, 0,
                      
                      0,0,0,0};

};


namespace DatExt {

  void weapons_dat_doPatch(u32 newCount) {
    datTablePatch((DatLoad*)LoadTable::Weapons_Dat, weapons_r);
    constReplace(weapons_consts, newCount);
  }

};