#include <SCBW/api.h>
#include <hook_tools.h>
#include "datext.h"


// scbwdata modified by DatExt
DATEXT_VAR_REF(_bwTechs*, TechBw_var);


namespace {

// List of address reference replacements.
s32 techdata_r[] = {/* minerals */ 0,   0x00447B78 +4, 0x004486C9 +3, 0x0042CDD5 +4, 0x00453D3A +3, 0x00453D98 +3, 0x00453E4E +3, 0x00454B7F +4, 0x0042D249 +3, 0x00459618 +3, 0x004BF1F5 +1, 0x004BF1FA +1, 0x004BF30A +1, 0x004BF4D0 +1, 0x004CA77C +4, 0x004CA87C +4, 0x00436840 +4,  0, 0,
                    /* gas */      0,   0x00447B89 +4, 0x004486D0 +3, 0x0042CDE4 +4, 0x00453D5B +3, 0x00453D9F +3, 0x00453E55 +3, 0x00454B92 +4, 0x0042D250 +3, 0x00459611 +3, 0x004BF214 +1, 0x004BF219 +1, 0x004BF31F +1, 0x004BF4E5 +1, 0x004CA789 +4, 0x004CA88C +4, 0x00436848 +4,  0, 0,
                    /* time */     0,   0x00426749 +4, 0x00454C00 +4, 0x004BF233 +1, 0x004BF238 +1, 0x004BF334 +1, 0x004BF4FA +1, 0x004CA796 +4, 0x004CA899 +4,  0, 0,
                    /* energy */   0,   0x004235B1 +3, 0x00423669 +4, 0x004595CB +4, 0x004595DF +4, 0x004595F6 +4, 0x0046F624 +4, 0x00491B8A +4, 0x00492714 +4, 0x00492929 +3, 0x0049E1D0 +4, 0x004A11F5 +4, 0x004BF252 +1, 0x004BF257 +1, 0x004BF349 +1, 0x004BF50F +1, 0x004CA79E +4, 0x004CA8A1 +4,  0,
                                   2*4, 0x0043C6BF +2, 0x00464E57 +2, 0x00464FAF +2,  0,
                                   2*21, 0x0045C600 +3, 0x0049450F +2,  0,
                                   2*25, 0x0045C5AA +3,  0,
                                   0,
                    /* req 1 */    0,   0x0046D559 +4, 0x0046D57E +1, 0x0046DEB6 +4, 0x0046DF77 +4,  0,
                                   44,  0x0046D590 +1,  0,
                                   0,
                    /* req 2 */    0,   0x0046D4E9 +4, 0x0046D50E +1, 0x0046DDAA +4, 0x0046DE59 +4,  0,
                                   44,  0x0046D520 +1,  0,
                                   0,
                    /* icon */     0,   0x004267B0 +4,  0, 0,
                    /* label */    0,   0x00457622 +4,  0, 0,
                    /* race */     0,   0, 0,
                    /* unused */   0,   0, 0,
                    /* broodwar */ 0,   0, 0};



// Techdata.dat tables
void* tech_newArrs[2] = {0};

           // ID offset, ptr, ptr, ptr, ..., 0, ...
s32 tech_bwAvail[] = {0 -24, 0x004CB755 +3, 0x004CB781 +3, 0x004CB8B8 +3, 0x004CB8E4 +3, 0x004CE897 +3, 0x004CE8BA +3,  0,
                        ARRAY_END, 0x004CCCF4 +1,  0,
                      0};

           // ID offset, ptr, ptr, ptr, ..., 0, ...
s32 tech_bwResearch[] = {0 -24, 0x0043254C +3, 0x0045490B +3, 0x00454959 +3, 0x0046D767 +3, 0x0047B3EB +3, 0x0047B422 +3, 0x004CB7AA +3, 0x004CB90D +3, 0x004CE846 +3, 0x004CE86A +3, 0x004E2C72 +3,  0,
                         0,     0x004CCD0E +1,  0,
                         ARRAY_END, 0x004E2C99 +2,  0,
                         0};

            // factor, add, size,       ptr, ptr, ptr, ...,  0,  ...
//TODO: This
s32 tech_consts[] = {0,   0,  0,  0,
                     0,0,0,0};



};


namespace DatExt {

  void techdata_dat_doPatch(u32 newCount) {
    u32 i, offs;

    datTablePatch((DatLoad*)LoadTable::Techdata_Dat, techdata_r);
    
    // tech_bwAvail
    tech_newArrs[0] = malloc((newCount - 24) * 12);
    // - Null-terminated list of null-terminated lists of addresses
    // - First value in list is the image ID referenced
    for(i=0; tech_bwAvail[i] != 0 || i == 0; i++){
      if(tech_bwAvail[i] == ARRAY_END){
        offs = (u32)tech_newArrs[0] + newCount - 24;
        i++;
      }else{
        offs = (u32)tech_newArrs[0] + tech_bwAvail[i++]; // ID offset
      }
      i += simpleReplace((u32*)&tech_bwAvail[i], offs);
    }

    // tech_bwResearch
    tech_newArrs[1] = malloc((newCount - 24) * 12);
    // - Null-terminated list of null-terminated lists of addresses
    // - First value in list is the image ID referenced
    for(i=0; tech_bwResearch[i] != 0 || i == 0; i++){
      if(tech_bwResearch[i] == ARRAY_END){
        offs = (u32)tech_newArrs[1] + newCount - 24;
        i++;
      }else{
        offs = (u32)tech_newArrs[1] + tech_bwResearch[i++]; // ID offset
      }
      i += simpleReplace((u32*)&tech_bwResearch[i], offs);
    }
    
    
    constReplace(tech_consts, newCount);

    // Apply 'newArrs' to appropriate scbwdata.h variables
    for (i = 0; i < 12; i++) {
      TechBw_var->isEnabled[i] = (u8*)(tech_newArrs[0]) + (newCount - 24)*i;
      TechBw_var->isResearched[i] = (u8*)(tech_newArrs[1]) + (newCount - 24) *i;
    }

  }

  
  void techdata_dat_unpatch() {
    for (int i = 0; i < 2; i++) {
      if (tech_newArrs[i] != NULL) {
        free(tech_newArrs[i]);
        tech_newArrs[i] = NULL;
      }
    }
  }

};