#include <SCBW/api.h>
#include <hook_tools.h>
#include "datext.h"

// scbwdata modified by DatExt
DATEXT_VAR_REF(const LO_Header* const*, shieldOverlays_var);
DATEXT_VAR_REF(u8*, damageOverlayFrame_var);
DATEXT_VAR_REF(GrpHead* const*, imageGrpGraphics_var);
DATEXT_VAR_REF(ImagesDatExtraOverlayLO_Files*, lo_files_var);

namespace {

// List of address reference replacements.
s32 images_r[] = {/* grp */        0,  0x004D7262 +1,  0, 0,
                  /* turns */      0,  0x004D5A67 +2,  0, 0,
                  /* clickable */  0,  0x004D5A7C +2,  0, 0,
                  /* full is*/     0,  0x00498FDB +2, 0x004D6701 +2,  0, 0,
                  /* draw cloak */ 0,  0x004976E4 +2, 0x00498184 +2, 0x004D6EC7 +2, 0x004D7A60 +2, 0x004D7AC3 +2,  0, 0,
                  /* draw fxn */   0,  0x00498FCA +2, 0x004D5AD0 +2, 0x004D5AE0 +2, 0x004D66B8 +2,  0, 0,
                  /* remapping */  0,  0x004D5AE9 +3,  0, 0,
                  /* iscript id */ 0,  0x00498FFF +3, 0x004D6698 +3, 0x004D671C +3, 0x004D67A8 +3, 0x004D689C +3, 0x004D691E +3, 0x004D853F +3,  0, 0,
                  /* shield ol */  0,  0x004D7343 +1,  0, 0,
                  /* attack ol */  0,  0x004D728A +1,  0, 0,
                  /* damage ol */  0,  0x00467384 +3, 0x004798EF +3, 0x004993D1 +3, 0x00499591 +3, 0x004D72B7 +1,  0, 0,
                  /* special ol */ 0,  0x004D72DA +1,  0, 0,
                  /* landing ol */ 0,  0x004997EA +3, 0x004D72FD +1,  0, 0,
                  /* lifting ol */ 0,  0x0049982A +3, 0x004D7320 +1,  0, 0};


// Images.dat Arrays:
void* img_newArrs[4] = {0}; // one for each of the following:

           // ID offset, ptr, ptr, ptr, ..., 0, ...
u32 img_grpArr[] = {0,    0x0048D76D +3, 0x0048DAA7 +3, 0x004D4E20 +3, 0x004D50E1 +1, 0x004D5A57 +3, 0x004D5E20 +3, 0x004D6360 +3, 0x004D67EC +3, 0x004D682F +3, 0x004D701B +3, 0x004D7267 +1,  0, 
                    210,  0x004D5415 +2,  0, 
                    561,  0x004D6025 +3,  0, 
                    584,  0x00493367 +2, 0x004D4E10 +1,  0, 
                    0};

u32 img_loArr[] = {/* attack */  0x00401E0F +3, 0x00477FFD +3, 0x00478071 +3, 0x0049968F +3, 0x004D50F5 +1, 0x004D5788 +3, 0x004D728F +1,  0, 
                   /* damage */  0x0049941A +3, 0x004994C2 +3, 0x00499603 +3, 0x004D5C39 +3, 0x004D72BC +1,  0, 
                   /* special */ 0x00498BE5 +3, 0x0049F73E +3, 0x004D5A0A +3, 0x004D72DF +1,  0, 
                   /* lift */    0x0049826A +3, 0x0049829A +3, 0x004D7302 +1,  0, 
                   /* land */    0x004D7325 +1,  0};


u32 img_loShield[] = {/* 52E5C8 */ 0x0049938E +3, 0x004D511D +1, 0x004D5748 +3, 0x004D7348 +1, 0x004E614F +3,  0, 
                      /* 52F528 */ 0x0049731A +2, 0x00497331 +2, 0x00497348 +2, 0x004D4B87 +2, 0x004D56C9 +2, 0x004D56DF +2,  0};


u32 img_blgOlState[] = {/* 5240D0 */ 0x00496ED7 +2, 0x004994AA +3, 0x0049EF37 +2, 0x004D5C33 +2, 0x004D5C77 +2, 0x004E60B5 +3, 0x004E669A +2,  0};


                        // factor, add, size,       ptr, ptr, ptr, ...,  0,  ...
s32 img_consts[] = {/* null */  0,  0, sizeof(int), 0x0047AE42 +2, 0x0047AF42 +2, 0x004D5E12 +1, 0x004D6351 +1,  0,
            /* 999 *  1 + 0 */  1,  0, sizeof(short), 0x004EA60D +2, 0,
                                1,  0, sizeof(int), 0x00401DFA +2, 0x0047AE48 +2, 0x0047AF48 +2, 0x00499676 +2, 0x004D50DC +1, 0x004D5100 +1, 0x004D5118 +1, 0x004D5773 +2, 0x004D5C23 +1, 0x004D5E17 +1, 0x004D6356 +1, 0x004D725C +1, 0x004D7284 +1, 0x004D72B1 +1, 0x004D72D4 +1, 0x004D72F7 +1, 0x004D731A +1, 0x004D733D +1,  0,
            /* 999 * -4 - 8 */ -4, -8, sizeof(int), 0x004D724E +2, 0x004D7276 +2, 0x004D72A3 +2, 0x004D72C6 +2, 0x004D72E9 +2, 0x004D730C +2, 0x004D732F +2,  0,
            /* 999 *-24 - 8 */-24, -8, sizeof(int), 0x004D7255 +2, 0x004D727D +2, 0x004D72AA +2, 0x004D72CD +2, 0x004D72F0 +2, 0x004D7313 +2, 0x004D7336 +2,  0,
            /* 999 * 24 + 8 */ 24,  8, sizeof(int), 0x004D7183 +1,  0,
                          0,0,0,0};



};


namespace DatExt {

  void images_dat_doPatch(u32 newCount) {
    u32 i, j, offs;

    datTablePatch((DatLoad*)LoadTable::Images_Dat, images_r);


    // img_grpArr
    // - Null-terminated list of null-terminated lists of addresses
    img_newArrs[0] = malloc(newCount * 4);
    // - First value in list is the image ID referenced
    for(i=0; img_grpArr[i] != 0 || i == 0; i++){
      offs = (u32)img_newArrs[0] + img_grpArr[i++] * 4; // ID offset
      i += simpleReplace(&img_grpArr[i], offs);
    }

    // img_loArr
    img_newArrs[1] = malloc(newCount * 4 * 5);
    // - 5 null-terminated lists of addresses, one for each lo? type
    for(i=0,j=0; i < 5; i++,j++){
      offs = (u32)img_newArrs[1] + newCount * 4 * i;
      j += simpleReplace(&img_loArr[j], offs);
    }

    // img_loShield
    img_newArrs[2] = malloc(newCount * 4);
    // - 2 null-terminated lists of addresses, one references 0x52E5C8 and the other 0x52F528 (ID#984 ?) 
    for(i=0,j=0; i < 2; i++,j++){
      offs = (u32)img_newArrs[2] + i * 984 * 4;
      j += simpleReplace(&img_loShield[j], offs);
    }

    // img_blgOlState
    img_newArrs[3] = malloc(newCount);
    // - Null-terminated lists of addresses
    simpleReplace(img_blgOlState, (u32)img_newArrs[3]);
    

    // img_consts
    constReplace(img_consts, newCount);


    // Apply 'newArrs' to appropriate scbwdata.h variables
    imageGrpGraphics_var = (GrpHead* const*)img_newArrs[0];
    lo_files_var->attackOverlays = (LO_Header**)img_newArrs[1];
    lo_files_var->damageOverlays = &((LO_Header**)img_newArrs[1])[newCount];
    lo_files_var->specialOverlays = &((LO_Header**)img_newArrs[1])[newCount*2];
    lo_files_var->liftoffDustOverlays = &((LO_Header**)img_newArrs[1])[newCount*3];
    lo_files_var->landingDustOverlays = &((LO_Header**)img_newArrs[1])[newCount*4];
    shieldOverlays_var = (LO_Header* const*)img_newArrs[2];
    damageOverlayFrame_var = (u8*)img_newArrs[3];
  }

  
  void images_dat_unpatch() {
    for (int i = 0; i < 4; i++) {
      if (img_newArrs[i] != NULL) {
        free(img_newArrs[i]);
        img_newArrs[i] = NULL;
      }
    }
  }

};