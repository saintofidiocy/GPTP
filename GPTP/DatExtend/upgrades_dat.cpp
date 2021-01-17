#include <SCBW/api.h>
#include <hook_tools.h>
#include "datext.h"


// scbwdata modified by DatExt
DATEXT_VAR_REF(_bwUpgrs*, UpgradesBw_var);


namespace {

// List of address reference replacements.
s32 upgrades_r[] = {/* minerals */   0,   0x00453F57 +3, 0x004540EF +3, 0x004541B6 +3, 0x0042D1CF +3, 0x004BF114 +1, 0x004BF11E +1, 0x004BF29C +1, 0x004BF452 +1, 0x004CA980 +4, 0x004CAAA0 +4, 0x004367F3 +3, 0,0,
                    /* min factor */ 0,   0x00453F50 +3, 0x004540E7 +4, 0x004541AE +4, 0x0042D1C7 +4, 0x004BF139 +1, 0x004BF143 +1, 0x004BF2AD +1, 0x004BF467 +1, 0x004CA990 +4, 0x004CAAB0 +4, 0x004367EB +4, 0,0,
                    /* gas */        0,   0x00453F07 +3, 0x00454142 +3, 0x004541F6 +3, 0x0042D20D +3, 0x004BF15E +1, 0x004BF168 +1, 0x004BF2BE +1, 0x004BF47C +1, 0x004CA9A0 +4, 0x004CAAC0 +4, 0x00436828 +3, 0,0,
                    /* gas factor */ 0,   0x00453F00 +3, 0x0045413A +4, 0x004541EE +4, 0x0042D205 +4, 0x004BF183 +1, 0x004BF18D +1, 0x004BF2CF +1, 0x004BF491 +1, 0x004CA9B0 +4, 0x004CAAD0 +4, 0x00436820 +4, 0,0,
                    /* time */       0,   0x00453FA7 +3, 0x004BF1A8 +1, 0x004BF1B2 +1, 0x004BF2E0 +1, 0x004BF4A6 +1, 0x004CA9BD +4, 0x004CAADD +4, 0,0,
                    /* time factor */0,   0x00453FA0 +3, 0x004BF1CD +1, 0x004BF1D7 +1, 0x004BF2F5 +1, 0x004BF4BB +1, 0x004CA9C5 +4, 0x004CAAE5 +4, 0,0,
                    /* reqs */       0,   0x0046D5C4 +4, 0x0046D5EC +1, 0x0046DFEE +4, 0x0046E0A6 +4, 0,
                                     ARRAY_END, 0x0046D5FE +1, 0,
                                     0,
                    /* icon */       0,   0x004256DC +4, 0x004265CD +4, 0,0,
                    /* label */      0,   0x004575D9 +4, 0x004575F2 +4, 0x00457865 +4, 0x004578C1 +4, 0,0,
                    /* race */       0,   0,0,
                    /* levels */     0,   0x0045957E +2, 0x004B21AE +2, 0x004CCD38 +1, 0x004CCD71 +1, 0x004CCDAE +1, 0x004CCDEA +1, 0x004CCE29 +1, 0x004CCE68 +1, 0,
                                     46,  0x004CCD41 +1, 0x004CCD7C +1, 0x004CCDB7 +1, 0x004CCDF3 +1, 0x004CCE32 +1, 0x004CCE71 +1, 0, // Code replacement "MOV ESI,upgDatLevels+46" value
                                     //46,  0x004CCD41 +2, 0x004CCD7C +2, 0x004CCDB7 +2, 0x004CCDF3 +2, 0x004CCE32 +2, 0x004CCE74 +2, 0, // Not needed due to code replacement
                                     //50,  0x004CCD4C +2, 0x004CCD86 +2, 0x004CCDC2 +2, 0x004CCDFE +2, 0x004CCE3D +2, 0x004CCE7C +2, 0,
                                     //54,  0x004CCD55 +2, 0x004CCD8F +2, 0x004CCDCB +2, 0x004CCE07 +2, 0x004CCE46 +2, 0x004CCE85 +2, 0,
                                     //58,  0x004CCD5E +3, 0x004CCD98 +3, 0x004CCDD4 +3, 0x004CCE10 +3, 0x004CCE4F +3, 0x004CCE8E +3, 0,
                                     60,  0x004CCCCA +2, 0, // really, it's unnecessary now but the code is still executed
                                     0,
                    /* bw */         0,   0,0};



// Upgrades.dat tables
void* upgs_newArrs[2] = {0};

           // ID offset, ptr, ptr, ptr, ..., 0, ...
s32 upgs_bwAvail[] = {0 -46, 0x00403418 +4, 0x004CBA97 +3, 0x004CBC1A +3, 0x004CE7E7 +3, 0x004CE80A +3, 0,
                         ARRAY_END, 0x004CCD21 +1, 0,
                      0};

           // ID offset, ptr, ptr, ptr, ..., 0, ...
s32 upgs_bwResearch[] = {0 -46, 0x004033F3 +3, 0x004257CD +3, 0x0042D1B7 +3, 0x0042D1FA +3, 0x004325BE +3, 0x004367DB +3, 0x00436815 +3, 0x00453EF2 +3, 0x00453F42 +3, 0x00453F92 +3, 0x00453FF4 +3, 0x0045405A +4, 0x004540D7 +3, 0x0045412F +3, 0x00454197 +3, 0x004541E3 +3, 0x00454702 +3, 0x0045474A +3, 0x00454ADF +3, 0x0046D9F9 +3, 0x00475E6E +3, 0x00475EF6 +3, 0x0047B369 +3, 0x0047B39F +3, 0x0048AD14 +3, 0x004B21A7 +3, 0x004B21C5 +3, 0x004B21E7 +3, 0x004CBA2B +3, 0x004CBA74 +3, 0x004CBBAE +3, 0x004CBBF7 +3, 0x004CE796 +3, 0x004CE7BA +3, 0x004E2BBC +3, 0x004E2FA9 +3, 0x004CCEC2 +1,  0,
                         1 -46, 0x0049196D +2,  0,
                         3 -46, 0x0049199B +2,  0,
                         5 -46, 0x00491984 +2,  0,
                         6 -46, 0x00454024 +2,  0,
                         7 -46, 0x0045446B +2,  0,
                         8 -46, 0x00475929 +2, 0x004760E0 +2, 0x004D78AF +2,  0,
                         ARRAY_END, 0x004CCECE +1,  0,
                         0};

            // factor, add, size,       ptr, ptr, ptr, ...,  0,  ...
s32 upgs_consts[] = {1, -46, sizeof(char),  0x004033F0 +2, 0x00403415 +2, 0x004CE7E4 +2, 0x004CE804 +2, 0x004257C7 +2, 0x0042D1B4 +2, 0x0042D1F7 +2, 0x004325BB +2, 0x004367D8 +2, 0x00436812 +2, 0x00453EEC +2, 0x00453F3C +2, 0x00453F8C +2, 0x00453FEE +2, 0x00454057 +2, 0x004540D4 +2, 0x0045412C +2, 0x00454194 +2, 0x004541E0 +2, 0x004546FF +2, 0x00454747 +2, 0x00454ADC +2, 0x0046D9F6 +2, 0x00475E6B +2, 0x00475EF3 +2, 0x0047B366 +2, 0x0047B39C +2, 0x0048AD0E +2, 0x004B221A +2, 0x004CE7B4 +2, 0x004CE790 +2, 0x004E2BB9 +2, 0x004E2FA3 +2, 0x0049196A +2, 0x00491998 +2, 0x00491981 +2, 0x00454021 +2, 0x00454468 +2, 0x00475926 +2, 0x004760DD +2, 0x004D78AC +2, 0x004CBB66 +2, 0x004CB9E3 +2,  0,
                     1,   0, sizeof(char),  0x004546C1 +2, 0x00454A87 +2, 0x00424AA2 +6, 0x00425C0E +6, 0x0042799D +6, 0x004287F4 +6, 0x0042890E +2, 0x00454226 +2, 0x00454268 +6, 0x00454297 +1, 0x004542D9 +6, 0x004547F9 +6, 0x0046D7BA +6, 0x0046E3B2 +6, 0x0046E411 +6, 0x0047CA66 +6, 0x00493892 +6, 0x0049E80A +1, 0x0049EED7 +6, 0x0049FD50 +6, 0x004C1663 +6, 0x004E2F78 +1, 0x0046D5B8 +3, 0x0046DFC4 +3, 0x004B2200 +2, 0x004CBB60 +2, 0x004CBB69 +2,  0, // Unless used for loading CHK ?
                     1,  -1, sizeof(char),  0x004B2190 +2,  0,
                     1,   0, sizeof(short), 0x004E2B9A +2,  0,
   /* (ct - 46)*12 */12,-12*46,sizeof(int), 0x004CBB4B +1, 0x004CB9CB +1,  0,
                     12,  0, sizeof(int), 0x004CBB55 +1,  0,
                     
                   // Code Replacements -- Whee!
                     0, 0xBE,   sizeof(char),  0x004CCD41 + 0, 0x004CCD7C + 0, 0x004CCDB7 + 0, 0x004CCDF3 + 0, 0x004CCE32 + 0, 0x004CCE71 + 0,  0, // MOV ESI, upgDatLevels + 46
                     // "upgDatLevels" defined in the fields
                     0, 0xB9,   sizeof(char),  0x004CCD41 + 5, 0x004CCD7C + 5, 0x004CCDB7 + 5, 0x004CCDF3 + 5, 0x004CCE32 + 5, 0x004CCE71 + 5,  0, // MOV ECX, datCount-46
                     1, -46,    sizeof(int),   0x004CCD41 + 6, 0x004CCD7C + 6, 0x004CCDB7 + 6, 0x004CCDF3 + 6, 0x004CCE32 + 6, 0x004CCE71 + 6,  0, //        ; datCount-46
                     0, 0xBA8D, sizeof(short), 0x004CCD41 +10,                 0x004CCDB7 +10, 0x004CCDF3 +10, 0x004CCE32 +10, 0x004CCE71 +10,  0, // LEA EDI, [EDX + (datCount-46)*(n-1)] ; idk, it's how it was already done
                    -1, 46,     sizeof(int),   0x004CCD41 +12,                                                                                  0, // ; n == 0
                     0, 0xFA8B, sizeof(short),                 0x004CCD7C +10,                                                                  0, // MOV EDI, EDX ; n == 1
                     1, -46,    sizeof(int),                                   0x004CCDB7 +12,                                                  0, // ; n == 2
                     2, -46*2,  sizeof(int),                                                   0x004CCDF3 +12,                                  0, // ; n == 3
                     3, -46*3,  sizeof(int),                                                                   0x004CCE32 +12,                  0, // ; n == 4
                     4, -46*4,  sizeof(int),                                                                                   0x004CCE71 +12,  0, // ; n == 5
                     0, 0xA4F3, sizeof(short), 0x004CCD41 +16, 0x004CCD7C +12, 0x004CCDB7 +16, 0x004CCDF3 +16, 0x004CCE32 +16, 0x004CCE71 +16,  0, // REP MOVS BYTE [EDI], BYTE [ESI]
                     0, 0x17EB, sizeof(short), 0x004CCD41 +18,                 0x004CCDB7 +18, 0x004CCDF3 +18, 0x004CCE32 +18,                  0, // JMP $+25
                     0, 0x1AEB, sizeof(short),                 0x004CCD7C +14,                                                                  0, // JMP $+28
                     0, 0x10EB, sizeof(short),                                                                                 0x004CCE71 +18,  0, // JMP $+18
                     0, 0xC281, sizeof(short), 0x004CCE9A,     0, // ADD EDX, (datCount-46)*6
                     6, -46*6,  sizeof(int),   0x004CCE9A +2,  0, //        ; (datCount-46)*6
                     0, 0x90,   sizeof(char),  0x004CCE9A +6,  0, // NOP
                     0, 0x00768D, 3,           0x004CCEA6,     0, // NOP-3
                     
                     12, -46*12, sizeof(int),  0x004CCEBD +1,  0,
                     0, 0xAA,   sizeof(char),  0x004CCEC7 +1,  0, // REP STOS BYTE [EDI]
                     
                     0,0,0,0};



};


namespace DatExt {

  void upgrades_dat_doPatch(u32 newCount) {
    u32 i, offs;

    datTablePatch((DatLoad*)LoadTable::Upgrades_Dat, upgrades_r);

    // upgs_bwAvail
    upgs_newArrs[0] = malloc((newCount - 46) * 12);
    // - Null-terminated list of null-terminated lists of addresses
    // - First value in list is the image ID referenced
    for(i=0; upgs_bwAvail[i] != 0 || i == 0; i++){
      if(upgs_bwAvail[i] == ARRAY_END){
        offs = (u32)upgs_newArrs[0] + newCount - 46;
        i++;
      }else{
        offs = (u32)upgs_newArrs[0] + upgs_bwAvail[i++];
      }
      i += simpleReplace((u32*)&upgs_bwAvail[i], offs);
    }

    // upgs_bwResearch
    upgs_newArrs[1] = malloc((newCount - 46) * 12);
    // - Null-terminated list of null-terminated lists of addresses
    // - First value in list is the image ID referenced
    for(i=0; upgs_bwResearch[i] != 0 || i == 0; i++){
      if(upgs_bwResearch[i] == ARRAY_END){
        offs = (u32)upgs_newArrs[1] + newCount - 46;
        i++;
      }else{
        offs = (u32)upgs_newArrs[1] + upgs_bwResearch[i++]; // ID offset
      }
      i += simpleReplace((u32*)&upgs_bwResearch[i], offs);
    }
    
    constReplace(upgs_consts, newCount);

    // Apply 'newArrs' to appropriate scbwdata.h variables
    for (i = 0; i < 12; i++) {
      UpgradesBw_var->maxLevel[i] = (u8*)(upgs_newArrs[0]) + (newCount - 46)*i;
      UpgradesBw_var->currentLevel[i] = (u8*)(upgs_newArrs[1]) + (newCount - 46)*i;
    }
  }

  
  void upgrades_dat_unpatch() {
    for (int i = 0; i < 2; i++) {
      if (upgs_newArrs[i] != NULL) {
        free(upgs_newArrs[i]);
        upgs_newArrs[i] = NULL;
      }
    }
  }

};