#include "global.h"
#include "save.h"

// This file contains the backups for the save file of v1.
// Editing this file may cause unwanted behaviour.
// Please use make release in case problems arise.

struct SaveBlock1_v1
{
    struct Coords16 pos;
    struct WarpData location;
    struct WarpData continueGameWarp;
    struct WarpData dynamicWarp;
    struct WarpData lastHealLocation;
    struct WarpData escapeWarp;
    u16 savedMusic;
    u8 weather;
    u8 weatherCycleStage;
    u8 flashLevel;
    u16 mapLayoutId;
    u16 mapView[256];
    u8 playerPartyCount;
    struct Pokemon playerParty[6];
    u32 money;
    u16 coins;
    u16 registeredItem;
    struct ItemSlot pcItems[50];
    struct ItemSlot bagPocket_Items[30];
    struct ItemSlot bagPocket_KeyItems[30];
    struct ItemSlot bagPocket_PokeBalls[16];
    struct ItemSlot bagPocket_TMHM[64];
    struct ItemSlot bagPocket_Berries[46];
    struct Pokeblock pokeblocks[40];
    u8 filler1[52];
    u16 berryBlenderRecords[3];
    u8 unused_9C2[6];
    u16 trainerRematchStepCounter;
    u8 trainerRematches[100];
    struct ObjectEvent objectEvents[16];
    struct ObjectEventTemplate objectEventTemplates[64];
    u8 flags[300];
    u16 vars[256];
    u32 gameStats[64];
    struct BerryTree berryTrees[128];
    struct SecretBase secretBases[20];
    u8 playerRoomDecorations[12];
    u8 playerRoomDecorationPositions[12];
    u8 decorationDesks[10];
    u8 decorationChairs[10];
    u8 decorationPlants[10];
    u8 decorationOrnaments[30];
    u8 decorationMats[30];
    u8 decorationPosters[10];
    u8 decorationDolls[40];
    u8 decorationCushions[10];
    TVShow tvShows[25];
    PokeNews pokeNews[16];
    u16 outbreakPokemonSpecies;
    u8 outbreakLocationMapNum;
    u8 outbreakLocationMapGroup;
    u8 outbreakPokemonLevel;
    u8 outbreakUnused1;
    u16 outbreakUnused2;
    u16 outbreakPokemonMoves[4];
    u8 outbreakUnused3;
    u8 outbreakPokemonProbability;
    u16 outbreakDaysLeft;
    struct GabbyAndTyData gabbyAndTyData;
    u16 easyChatProfile[6];
    u16 easyChatBattleStart[6];
    u16 easyChatBattleWon[6];
    u16 easyChatBattleLost[6];
    struct Mail mail[16];
    u8 unlockedTrendySayings[5];
    OldMan oldMan;
    struct DewfordTrend dewfordTrends[5];
    struct ContestWinner contestWinners[13];
    struct DayCare daycare;
    struct LinkBattleRecords linkBattleRecords;
    u8 giftRibbons[11];
    struct ExternalEventData externalEventData;
    struct ExternalEventFlags externalEventFlags;
    struct Roamer roamer;
    struct EnigmaBerry enigmaBerry;
    struct MysteryGiftSave mysteryGift;
    u8 dexSeen[114];
    u8 dexCaught[114];
    u32 trainerHillTimes[4];
    struct RamScript ramScript;
    struct RecordMixingGift recordMixingGift;
    LilycoveLady lilycoveLady;
    struct TrainerNameRecord trainerNameRecords[20];
    u8 registeredTexts[10][21];
    struct TrainerHillSave trainerHill;
    struct WaldaPhrase waldaPhrase;
};


bool8 UpdateSave_v1_v3(const struct SaveSectorLocation *locations)
{
    const struct SaveBlock2* sOldSaveBlock2Ptr = (struct SaveBlock2*)(locations[0].data); // SECTOR_ID_SAVEBLOCK2
    const struct SaveBlock1_v1* sOldSaveBlock1Ptr = (struct SaveBlock1_v1*)(locations[1].data); // SECTOR_ID_SAVEBLOCK1_START
    const struct PokemonStorage* sOldPokemonStoragePtr = (struct PokemonStorage*)(locations[5].data); // SECTOR_ID_PKMN_STORAGE_START
    u32 i;

    // SaveBlock2 
    *gSaveBlock2Ptr = *sOldSaveBlock2Ptr;

    // SaveBlock1 
    gSaveBlock1Ptr->pos = sOldSaveBlock1Ptr->pos;
    gSaveBlock1Ptr->location = sOldSaveBlock1Ptr->location;
    gSaveBlock1Ptr->continueGameWarp = sOldSaveBlock1Ptr->continueGameWarp;
    gSaveBlock1Ptr->dynamicWarp = sOldSaveBlock1Ptr->dynamicWarp;
    gSaveBlock1Ptr->lastHealLocation = sOldSaveBlock1Ptr->lastHealLocation;
    gSaveBlock1Ptr->escapeWarp = sOldSaveBlock1Ptr->escapeWarp;
    gSaveBlock1Ptr->playerPartyCount = sOldSaveBlock1Ptr->playerPartyCount;
    CpuCopy16(&sOldSaveBlock1Ptr->playerParty, &gSaveBlock1Ptr->playerParty, min(sizeof(gSaveBlock1Ptr->playerParty), sizeof(sOldSaveBlock1Ptr->playerParty)));
    gSaveBlock1Ptr->money = sOldSaveBlock1Ptr->money;
    gSaveBlock1Ptr->coins = sOldSaveBlock1Ptr->coins;
    gSaveBlock1Ptr->registeredItem = sOldSaveBlock1Ptr->registeredItem;
    CpuCopy16(&sOldSaveBlock1Ptr->pcItems, &gSaveBlock1Ptr->pcItems, min(sizeof(gSaveBlock1Ptr->pcItems), sizeof(sOldSaveBlock1Ptr->pcItems)));
    CpuCopy16(&sOldSaveBlock1Ptr->bagPocket_Items, &gSaveBlock1Ptr->bagPocket_Items, min(sizeof(gSaveBlock1Ptr->bagPocket_Items), sizeof(sOldSaveBlock1Ptr->bagPocket_Items)));
    CpuCopy16(&sOldSaveBlock1Ptr->bagPocket_KeyItems, &gSaveBlock1Ptr->bagPocket_KeyItems, min(sizeof(gSaveBlock1Ptr->bagPocket_KeyItems), sizeof(sOldSaveBlock1Ptr->bagPocket_KeyItems)));
    CpuCopy16(&sOldSaveBlock1Ptr->bagPocket_PokeBalls, &gSaveBlock1Ptr->bagPocket_PokeBalls, min(sizeof(gSaveBlock1Ptr->bagPocket_PokeBalls), sizeof(sOldSaveBlock1Ptr->bagPocket_PokeBalls)));
    CpuCopy16(&sOldSaveBlock1Ptr->bagPocket_TMHM, &gSaveBlock1Ptr->bagPocket_TMHM, min(sizeof(gSaveBlock1Ptr->bagPocket_TMHM), sizeof(sOldSaveBlock1Ptr->bagPocket_TMHM)));
    CpuCopy16(&sOldSaveBlock1Ptr->bagPocket_Berries, &gSaveBlock1Ptr->bagPocket_Berries, min(sizeof(gSaveBlock1Ptr->bagPocket_Berries), sizeof(sOldSaveBlock1Ptr->bagPocket_Berries)));
    CpuCopy16(&sOldSaveBlock1Ptr->pokeblocks, &gSaveBlock1Ptr->pokeblocks, min(sizeof(gSaveBlock1Ptr->pokeblocks), sizeof(sOldSaveBlock1Ptr->pokeblocks)));
    for(i = 0; i < min(ARRAY_COUNT(gSaveBlock1Ptr->filler1), ARRAY_COUNT(sOldSaveBlock1Ptr->filler1)); i++) gSaveBlock1Ptr->filler1[i] = sOldSaveBlock1Ptr->filler1[i];
    for(i = 0; i < min(ARRAY_COUNT(gSaveBlock1Ptr->berryBlenderRecords), ARRAY_COUNT(sOldSaveBlock1Ptr->berryBlenderRecords)); i++) gSaveBlock1Ptr->berryBlenderRecords[i] = sOldSaveBlock1Ptr->berryBlenderRecords[i];
    for(i = 0; i < min(ARRAY_COUNT(gSaveBlock1Ptr->unused_9C2), ARRAY_COUNT(sOldSaveBlock1Ptr->unused_9C2)); i++) gSaveBlock1Ptr->unused_9C2[i] = sOldSaveBlock1Ptr->unused_9C2[i];
    gSaveBlock1Ptr->trainerRematchStepCounter = sOldSaveBlock1Ptr->trainerRematchStepCounter;
    for(i = 0; i < min(ARRAY_COUNT(gSaveBlock1Ptr->trainerRematches), ARRAY_COUNT(sOldSaveBlock1Ptr->trainerRematches)); i++) gSaveBlock1Ptr->trainerRematches[i] = sOldSaveBlock1Ptr->trainerRematches[i];
    for(i = 0; i < min(ARRAY_COUNT(gSaveBlock1Ptr->flags), ARRAY_COUNT(sOldSaveBlock1Ptr->flags)); i++) gSaveBlock1Ptr->flags[i] = sOldSaveBlock1Ptr->flags[i];
    for(i = 0; i < min(ARRAY_COUNT(gSaveBlock1Ptr->vars), ARRAY_COUNT(sOldSaveBlock1Ptr->vars)); i++) gSaveBlock1Ptr->vars[i] = sOldSaveBlock1Ptr->vars[i];
    for(i = 0; i < min(ARRAY_COUNT(gSaveBlock1Ptr->gameStats), ARRAY_COUNT(sOldSaveBlock1Ptr->gameStats)); i++) gSaveBlock1Ptr->gameStats[i] = sOldSaveBlock1Ptr->gameStats[i];
    CpuCopy16(&sOldSaveBlock1Ptr->berryTrees, &gSaveBlock1Ptr->berryTrees, min(sizeof(gSaveBlock1Ptr->berryTrees), sizeof(sOldSaveBlock1Ptr->berryTrees)));
    CpuCopy16(&sOldSaveBlock1Ptr->secretBases, &gSaveBlock1Ptr->secretBases, min(sizeof(gSaveBlock1Ptr->secretBases), sizeof(sOldSaveBlock1Ptr->secretBases)));
    for(i = 0; i < min(ARRAY_COUNT(gSaveBlock1Ptr->playerRoomDecorations), ARRAY_COUNT(sOldSaveBlock1Ptr->playerRoomDecorations)); i++) gSaveBlock1Ptr->playerRoomDecorations[i] = sOldSaveBlock1Ptr->playerRoomDecorations[i];
    for(i = 0; i < min(ARRAY_COUNT(gSaveBlock1Ptr->playerRoomDecorationPositions), ARRAY_COUNT(sOldSaveBlock1Ptr->playerRoomDecorationPositions)); i++) gSaveBlock1Ptr->playerRoomDecorationPositions[i] = sOldSaveBlock1Ptr->playerRoomDecorationPositions[i];
    for(i = 0; i < min(ARRAY_COUNT(gSaveBlock1Ptr->decorationDesks), ARRAY_COUNT(sOldSaveBlock1Ptr->decorationDesks)); i++) gSaveBlock1Ptr->decorationDesks[i] = sOldSaveBlock1Ptr->decorationDesks[i];
    for(i = 0; i < min(ARRAY_COUNT(gSaveBlock1Ptr->decorationChairs), ARRAY_COUNT(sOldSaveBlock1Ptr->decorationChairs)); i++) gSaveBlock1Ptr->decorationChairs[i] = sOldSaveBlock1Ptr->decorationChairs[i];
    for(i = 0; i < min(ARRAY_COUNT(gSaveBlock1Ptr->decorationPlants), ARRAY_COUNT(sOldSaveBlock1Ptr->decorationPlants)); i++) gSaveBlock1Ptr->decorationPlants[i] = sOldSaveBlock1Ptr->decorationPlants[i];
    for(i = 0; i < min(ARRAY_COUNT(gSaveBlock1Ptr->decorationOrnaments), ARRAY_COUNT(sOldSaveBlock1Ptr->decorationOrnaments)); i++) gSaveBlock1Ptr->decorationOrnaments[i] = sOldSaveBlock1Ptr->decorationOrnaments[i];
    for(i = 0; i < min(ARRAY_COUNT(gSaveBlock1Ptr->decorationMats), ARRAY_COUNT(sOldSaveBlock1Ptr->decorationMats)); i++) gSaveBlock1Ptr->decorationMats[i] = sOldSaveBlock1Ptr->decorationMats[i];
    for(i = 0; i < min(ARRAY_COUNT(gSaveBlock1Ptr->decorationPosters), ARRAY_COUNT(sOldSaveBlock1Ptr->decorationPosters)); i++) gSaveBlock1Ptr->decorationPosters[i] = sOldSaveBlock1Ptr->decorationPosters[i];
    for(i = 0; i < min(ARRAY_COUNT(gSaveBlock1Ptr->decorationDolls), ARRAY_COUNT(sOldSaveBlock1Ptr->decorationDolls)); i++) gSaveBlock1Ptr->decorationDolls[i] = sOldSaveBlock1Ptr->decorationDolls[i];
    for(i = 0; i < min(ARRAY_COUNT(gSaveBlock1Ptr->decorationCushions), ARRAY_COUNT(sOldSaveBlock1Ptr->decorationCushions)); i++) gSaveBlock1Ptr->decorationCushions[i] = sOldSaveBlock1Ptr->decorationCushions[i];
    for(i = 0; i < min(ARRAY_COUNT(gSaveBlock1Ptr->tvShows), ARRAY_COUNT(sOldSaveBlock1Ptr->tvShows)); i++) gSaveBlock1Ptr->tvShows[i] = sOldSaveBlock1Ptr->tvShows[i];
    for(i = 0; i < min(ARRAY_COUNT(gSaveBlock1Ptr->pokeNews), ARRAY_COUNT(sOldSaveBlock1Ptr->pokeNews)); i++) gSaveBlock1Ptr->pokeNews[i] = sOldSaveBlock1Ptr->pokeNews[i];
    gSaveBlock1Ptr->outbreakPokemonSpecies = sOldSaveBlock1Ptr->outbreakPokemonSpecies;
    gSaveBlock1Ptr->outbreakLocationMapNum = sOldSaveBlock1Ptr->outbreakLocationMapNum;
    gSaveBlock1Ptr->outbreakLocationMapGroup = sOldSaveBlock1Ptr->outbreakLocationMapGroup;
    gSaveBlock1Ptr->outbreakPokemonLevel = sOldSaveBlock1Ptr->outbreakPokemonLevel;
    gSaveBlock1Ptr->outbreakUnused1 = sOldSaveBlock1Ptr->outbreakUnused1;
    gSaveBlock1Ptr->outbreakUnused2 = sOldSaveBlock1Ptr->outbreakUnused2;
    for(i = 0; i < min(ARRAY_COUNT(gSaveBlock1Ptr->outbreakPokemonMoves), ARRAY_COUNT(sOldSaveBlock1Ptr->outbreakPokemonMoves)); i++) gSaveBlock1Ptr->outbreakPokemonMoves[i] = sOldSaveBlock1Ptr->outbreakPokemonMoves[i];
    gSaveBlock1Ptr->outbreakUnused3 = sOldSaveBlock1Ptr->outbreakUnused3;
    gSaveBlock1Ptr->outbreakPokemonProbability = sOldSaveBlock1Ptr->outbreakPokemonProbability;
    gSaveBlock1Ptr->outbreakDaysLeft = sOldSaveBlock1Ptr->outbreakDaysLeft;
    gSaveBlock1Ptr->gabbyAndTyData = sOldSaveBlock1Ptr->gabbyAndTyData;
    for(i = 0; i < min(ARRAY_COUNT(gSaveBlock1Ptr->easyChatProfile), ARRAY_COUNT(sOldSaveBlock1Ptr->easyChatProfile)); i++) gSaveBlock1Ptr->easyChatProfile[i] = sOldSaveBlock1Ptr->easyChatProfile[i];
    for(i = 0; i < min(ARRAY_COUNT(gSaveBlock1Ptr->easyChatBattleStart), ARRAY_COUNT(sOldSaveBlock1Ptr->easyChatBattleStart)); i++) gSaveBlock1Ptr->easyChatBattleStart[i] = sOldSaveBlock1Ptr->easyChatBattleStart[i];
    for(i = 0; i < min(ARRAY_COUNT(gSaveBlock1Ptr->easyChatBattleWon), ARRAY_COUNT(sOldSaveBlock1Ptr->easyChatBattleWon)); i++) gSaveBlock1Ptr->easyChatBattleWon[i] = sOldSaveBlock1Ptr->easyChatBattleWon[i];
    for(i = 0; i < min(ARRAY_COUNT(gSaveBlock1Ptr->easyChatBattleLost), ARRAY_COUNT(sOldSaveBlock1Ptr->easyChatBattleLost)); i++) gSaveBlock1Ptr->easyChatBattleLost[i] = sOldSaveBlock1Ptr->easyChatBattleLost[i];
    CpuCopy16(&sOldSaveBlock1Ptr->mail, &gSaveBlock1Ptr->mail, min(sizeof(gSaveBlock1Ptr->mail), sizeof(sOldSaveBlock1Ptr->mail)));
    for(i = 0; i < min(ARRAY_COUNT(gSaveBlock1Ptr->unlockedTrendySayings), ARRAY_COUNT(sOldSaveBlock1Ptr->unlockedTrendySayings)); i++) gSaveBlock1Ptr->unlockedTrendySayings[i] = sOldSaveBlock1Ptr->unlockedTrendySayings[i];
    gSaveBlock1Ptr->oldMan = sOldSaveBlock1Ptr->oldMan;
    CpuCopy16(&sOldSaveBlock1Ptr->dewfordTrends, &gSaveBlock1Ptr->dewfordTrends, min(sizeof(gSaveBlock1Ptr->dewfordTrends), sizeof(sOldSaveBlock1Ptr->dewfordTrends)));
    CpuCopy16(&sOldSaveBlock1Ptr->contestWinners, &gSaveBlock1Ptr->contestWinners, min(sizeof(gSaveBlock1Ptr->contestWinners), sizeof(sOldSaveBlock1Ptr->contestWinners)));
    gSaveBlock1Ptr->daycare = sOldSaveBlock1Ptr->daycare;
    gSaveBlock1Ptr->linkBattleRecords = sOldSaveBlock1Ptr->linkBattleRecords;
    for(i = 0; i < min(ARRAY_COUNT(gSaveBlock1Ptr->giftRibbons), ARRAY_COUNT(sOldSaveBlock1Ptr->giftRibbons)); i++) gSaveBlock1Ptr->giftRibbons[i] = sOldSaveBlock1Ptr->giftRibbons[i];
    gSaveBlock1Ptr->externalEventData = sOldSaveBlock1Ptr->externalEventData;
    gSaveBlock1Ptr->externalEventFlags = sOldSaveBlock1Ptr->externalEventFlags;
    gSaveBlock1Ptr->roamer = sOldSaveBlock1Ptr->roamer;
    gSaveBlock1Ptr->enigmaBerry = sOldSaveBlock1Ptr->enigmaBerry;
    gSaveBlock1Ptr->mysteryGift = sOldSaveBlock1Ptr->mysteryGift;
    for(i = 0; i < min(ARRAY_COUNT(gSaveBlock1Ptr->dexSeen), ARRAY_COUNT(sOldSaveBlock1Ptr->dexSeen)); i++) gSaveBlock1Ptr->dexSeen[i] = sOldSaveBlock1Ptr->dexSeen[i];
    for(i = 0; i < min(ARRAY_COUNT(gSaveBlock1Ptr->dexCaught), ARRAY_COUNT(sOldSaveBlock1Ptr->dexCaught)); i++) gSaveBlock1Ptr->dexCaught[i] = sOldSaveBlock1Ptr->dexCaught[i];
    for(i = 0; i < min(ARRAY_COUNT(gSaveBlock1Ptr->trainerHillTimes), ARRAY_COUNT(sOldSaveBlock1Ptr->trainerHillTimes)); i++) gSaveBlock1Ptr->trainerHillTimes[i] = sOldSaveBlock1Ptr->trainerHillTimes[i];
    gSaveBlock1Ptr->ramScript = sOldSaveBlock1Ptr->ramScript;
    gSaveBlock1Ptr->recordMixingGift = sOldSaveBlock1Ptr->recordMixingGift;
    gSaveBlock1Ptr->lilycoveLady = sOldSaveBlock1Ptr->lilycoveLady;
    CpuCopy16(&sOldSaveBlock1Ptr->trainerNameRecords, &gSaveBlock1Ptr->trainerNameRecords, min(sizeof(gSaveBlock1Ptr->trainerNameRecords), sizeof(sOldSaveBlock1Ptr->trainerNameRecords)));
    CpuCopy16(&sOldSaveBlock1Ptr->registeredTexts, &gSaveBlock1Ptr->registeredTexts, min(sizeof(gSaveBlock1Ptr->registeredTexts), sizeof(sOldSaveBlock1Ptr->registeredTexts)));
    gSaveBlock1Ptr->trainerHill = sOldSaveBlock1Ptr->trainerHill;
    gSaveBlock1Ptr->waldaPhrase = sOldSaveBlock1Ptr->waldaPhrase;

    // PokemonStorage 
    *gPokemonStoragePtr = *sOldPokemonStoragePtr;

    gSaveBlock2Ptr->saveVersion = 3;

    SetContinueGameWarpStatus();
    gSaveBlock1Ptr->continueGameWarp = gSaveBlock1Ptr->lastHealLocation;

    return TRUE;
}
