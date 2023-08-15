#include "global.h"
#include "save.h"

// This file contains the backups for the save file of v1.
// Editing this file may cause unwanted behaviour.
// Please use make release in case problems arise.


bool8 UpdateSave_v1_v4(const struct SaveSectorLocation *locations)
{
    const struct SaveBlock2* sOldSaveBlock2Ptr = (struct SaveBlock2*)(locations[0].data); // SECTOR_ID_SAVEBLOCK2
    const struct SaveBlock1* sOldSaveBlock1Ptr = (struct SaveBlock1*)(locations[1].data); // SECTOR_ID_SAVEBLOCK1_START
    const struct PokemonStorage* sOldPokemonStoragePtr = (struct PokemonStorage*)(locations[5].data); // SECTOR_ID_PKMN_STORAGE_START
    u32 i;

    // SaveBlock2 
    *gSaveBlock2Ptr = *sOldSaveBlock2Ptr;

    // SaveBlock1 
    *gSaveBlock1Ptr = *sOldSaveBlock1Ptr;

    // PokemonStorage 
    *gPokemonStoragePtr = *sOldPokemonStoragePtr;

    gSaveBlock2Ptr->saveVersion = 4;

    SetContinueGameWarpStatus();
    gSaveBlock1Ptr->continueGameWarp = gSaveBlock1Ptr->lastHealLocation;

    return TRUE;
}
