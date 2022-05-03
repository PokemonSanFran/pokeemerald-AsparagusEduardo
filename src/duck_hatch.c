#include "global.h"
#include "pokemon.h"
#include "duck_hatch.h"
#include "pokedex.h"
#include "constants/items.h"
#include "script.h"
#include "decompress.h"
#include "task.h"
#include "palette.h"
#include "main.h"
#include "event_data.h"
#include "sound.h"
#include "constants/songs.h"
#include "text.h"
#include "text_window.h"
#include "string_util.h"
#include "menu.h"
#include "trig.h"
#include "random.h"
#include "malloc.h"
#include "dma3.h"
#include "gpu_regs.h"
#include "bg.h"
#include "m4a.h"
#include "window.h"
#include "graphics.h"
#include "constants/abilities.h"
#include "daycare.h"
#include "overworld.h"
#include "scanline_effect.h"
#include "field_weather.h"
#include "international_string_util.h"
#include "naming_screen.h"
#include "pokemon_storage_system.h"
#include "field_screen_effect.h"
#include "data.h"
#include "battle.h" // to get rid of later
#include "constants/rgb.h"

#define GFXTAG_DUCK       12345
#define GFXTAG_DUCK_SHARD 23456

#define PALTAG_DUCK       54321

#define DUCK_X (DISPLAY_WIDTH / 2)
#define DUCK_Y (DISPLAY_HEIGHT / 2 - 5)

struct DuckHatchData
{
    u8 duckSpriteId;
    u8 monSpriteId;
    u8 state;
    u8 delayTimer;
    u8 duckPartyId;
    u8 unused_5;
    u8 unused_6;
    u8 duckShardVelocityId;
    u8 windowId;
    u8 unused_9;
    u8 unused_A;
    u16 species;
    u8 textColor[3];
};

extern const u32 gTradePlatform_Tilemap[];
extern const u8 gText_HatchedFromDuck[];
extern const u8 gText_NicknameHatchPrompt[];

static void Task_DuckHatch(u8);
static void CB2_LoadDuckHatch(void);
static void CB2_DuckHatch(void);
static void SpriteCB_Duck_Shake1(struct Sprite*);
static void SpriteCB_Duck_Shake2(struct Sprite*);
static void SpriteCB_Duck_Shake3(struct Sprite*);
static void SpriteCB_Duck_WaitHatch(struct Sprite*);
static void SpriteCB_Duck_Hatch(struct Sprite*);
static void SpriteCB_Duck_Reveal(struct Sprite*);
static void SpriteCB_DuckShard(struct Sprite*);
static void DuckHatchPrintMessage(u8, u8*, u8, u8, u8);
static void CreateRandomDuckShardSprite(void);
static void CreateDuckShardSprite(u8, u8, s16, s16, s16, u8);

static struct DuckHatchData *sDuckHatchData;

static const u16 sDuckPalette[]  = INCBIN_U16("graphics/pokemon/duck/normal.gbapal");
static const u8 sDuckHatchTiles[] = INCBIN_U8("graphics/pokemon/duck/hatch.4bpp");
static const u8 sDuckShardTiles[] = INCBIN_U8("graphics/pokemon/duck/shard.4bpp");

static const struct OamData sOamData_Duck =
{
    .y = 0,
    .affineMode = ST_OAM_AFFINE_OFF,
    .objMode = ST_OAM_OBJ_NORMAL,
    .mosaic = 0,
    .bpp = ST_OAM_4BPP,
    .shape = SPRITE_SHAPE(32x32),
    .x = 0,
    .matrixNum = 0,
    .size = SPRITE_SIZE(32x32),
    .tileNum = 0,
    .priority = 1,
    .paletteNum = 0,
    .affineParam = 0,
};

static const union AnimCmd sSpriteAnim_Duck_Normal[] =
{
    ANIMCMD_FRAME(0, 5),
    ANIMCMD_END
};

static const union AnimCmd sSpriteAnim_Duck_Cracked1[] =
{
    ANIMCMD_FRAME(16, 5),
    ANIMCMD_END
};

static const union AnimCmd sSpriteAnim_Duck_Cracked2[] =
{
    ANIMCMD_FRAME(32, 5),
    ANIMCMD_END
};

static const union AnimCmd sSpriteAnim_Duck_Cracked3[] =
{
    ANIMCMD_FRAME(48, 5),
    ANIMCMD_END
};

enum {
    DUCK_ANIM_NORMAL,
    DUCK_ANIM_CRACKED_1,
    DUCK_ANIM_CRACKED_2,
    DUCK_ANIM_CRACKED_3,
};

static const union AnimCmd *const sSpriteAnimTable_Duck[] =
{
    [DUCK_ANIM_NORMAL]    = sSpriteAnim_Duck_Normal,
    [DUCK_ANIM_CRACKED_1] = sSpriteAnim_Duck_Cracked1,
    [DUCK_ANIM_CRACKED_2] = sSpriteAnim_Duck_Cracked2,
    [DUCK_ANIM_CRACKED_3] = sSpriteAnim_Duck_Cracked3,
};

static const struct SpriteSheet sDuckHatch_Sheet =
{
    .data = sDuckHatchTiles,
    .size = 0x800,
    .tag = GFXTAG_DUCK,
};

static const struct SpriteSheet sDuckShards_Sheet =
{
    .data = sDuckShardTiles,
    .size = 0x80,
    .tag = GFXTAG_DUCK_SHARD,
};

static const struct SpritePalette sDuck_SpritePalette =
{
    .data = sDuckPalette,
    .tag = PALTAG_DUCK
};

static const struct SpriteTemplate sSpriteTemplate_Duck =
{
    .tileTag = GFXTAG_DUCK,
    .paletteTag = PALTAG_DUCK,
    .oam = &sOamData_Duck,
    .anims = sSpriteAnimTable_Duck,
    .images = NULL,
    .affineAnims = gDummySpriteAffineAnimTable,
    .callback = SpriteCallbackDummy
};

static const struct OamData sOamData_DuckShard =
{
    .y = 0,
    .affineMode = ST_OAM_AFFINE_OFF,
    .objMode = ST_OAM_OBJ_NORMAL,
    .mosaic = 0,
    .bpp = ST_OAM_4BPP,
    .shape = SPRITE_SHAPE(8x8),
    .x = 0,
    .matrixNum = 0,
    .size = SPRITE_SIZE(8x8),
    .tileNum = 0,
    .priority = 2,
    .paletteNum = 0,
    .affineParam = 0,
};

static const union AnimCmd sSpriteAnim_DuckShard0[] =
{
    ANIMCMD_FRAME(0, 5),
    ANIMCMD_END
};

static const union AnimCmd sSpriteAnim_DuckShard1[] =
{
    ANIMCMD_FRAME(1, 5),
    ANIMCMD_END
};

static const union AnimCmd sSpriteAnim_DuckShard2[] =
{
    ANIMCMD_FRAME(2, 5),
    ANIMCMD_END
};

static const union AnimCmd sSpriteAnim_DuckShard3[] =
{
    ANIMCMD_FRAME(3, 5),
    ANIMCMD_END
};

static const union AnimCmd *const sSpriteAnimTable_DuckShard[] =
{
    sSpriteAnim_DuckShard0,
    sSpriteAnim_DuckShard1,
    sSpriteAnim_DuckShard2,
    sSpriteAnim_DuckShard3,
};

static const struct SpriteTemplate sSpriteTemplate_DuckShard =
{
    .tileTag = GFXTAG_DUCK_SHARD,
    .paletteTag = PALTAG_DUCK,
    .oam = &sOamData_DuckShard,
    .anims = sSpriteAnimTable_DuckShard,
    .images = NULL,
    .affineAnims = gDummySpriteAffineAnimTable,
    .callback = SpriteCB_DuckShard
};

static const struct BgTemplate sBgTemplates_DuckHatch[] =
{
    {
        .bg = 0,
        .charBaseIndex = 2,
        .mapBaseIndex = 24,
        .screenSize = 3,
        .paletteMode = 0,
        .priority = 0,
        .baseTile = 0
    },

    {
        .bg = 1,
        .charBaseIndex = 0,
        .mapBaseIndex = 8,
        .screenSize = 1,
        .paletteMode = 0,
        .priority = 2,
        .baseTile = 0
    },
};

static const struct WindowTemplate sWinTemplates_DuckHatch[] =
{
    {
        .bg = 0,
        .tilemapLeft = 2,
        .tilemapTop = 15,
        .width = 26,
        .height = 4,
        .paletteNum = 0,
        .baseBlock = 64
    },
    DUMMY_WIN_TEMPLATE
};

static const struct WindowTemplate sYesNoWinTemplate =
{
    .bg = 0,
    .tilemapLeft = 21,
    .tilemapTop = 9,
    .width = 5,
    .height = 4,
    .paletteNum = 15,
    .baseBlock = 424
};

static const s16 sDuckShardVelocities[][2] =
{
    // First shake
    {Q_8_8(-1.5),       Q_8_8(-3.75)},

    // Third shake
    {Q_8_8(-5),         Q_8_8(-3)},
    {Q_8_8(3.5),        Q_8_8(-3)},

    // Hatching
    {Q_8_8(-4),         Q_8_8(-3.75)},
    {Q_8_8(2),          Q_8_8(-1.5)},
    {Q_8_8(-0.5),       Q_8_8(-6.75)},
    {Q_8_8(5),          Q_8_8(-2.25)},
    {Q_8_8(-1.5),       Q_8_8(-3.75)},
    {Q_8_8(4.5),        Q_8_8(-1.5)},
    {Q_8_8(-1),         Q_8_8(-6.75)},
    {Q_8_8(4),          Q_8_8(-2.25)},
    {Q_8_8(-3.5),       Q_8_8(-3.75)},
    {Q_8_8(1),          Q_8_8(-1.5)},
    {Q_8_8(-3.515625),  Q_8_8(-6.75)},
    {Q_8_8(4.5),        Q_8_8(-2.25)},
    {Q_8_8(-0.5),       Q_8_8(-7.5)},
    {Q_8_8(1),          Q_8_8(-4.5)},
    {Q_8_8(-2.5),       Q_8_8(-2.25)},
    {Q_8_8(2.5),        Q_8_8(-7.5)},
};

static void CreateHatchedMon(struct Pokemon *duck, struct Pokemon *temp)
{
    u16 species;
    u32 personality, pokerus;
    u8 i, friendship, language, gameMet, markings, isEventLegal;
    u16 moves[MAX_MON_MOVES];
    u32 ivs[NUM_STATS];

    species = GetMonData(duck, MON_DATA_SPECIES);

    for (i = 0; i < MAX_MON_MOVES; i++)
        moves[i] = GetMonData(duck, MON_DATA_MOVE1 + i);

    personality = GetMonData(duck, MON_DATA_PERSONALITY);

    for (i = 0; i < NUM_STATS; i++)
        ivs[i] = GetMonData(duck, MON_DATA_HP_IV + i);

    // The language is initially read from the Duck but is later overwritten below
    language = GetMonData(duck, MON_DATA_LANGUAGE);
    gameMet = GetMonData(duck, MON_DATA_MET_GAME);
    markings = GetMonData(duck, MON_DATA_MARKINGS);
    pokerus = GetMonData(duck, MON_DATA_POKERUS);
    isEventLegal = GetMonData(duck, MON_DATA_EVENT_LEGAL);

    CreateMon(temp, species, DUCK_HATCH_LEVEL, USE_RANDOM_IVS, TRUE, personality, OT_ID_PLAYER_ID, 0);

    for (i = 0; i < MAX_MON_MOVES; i++)
        SetMonData(temp, MON_DATA_MOVE1 + i,  &moves[i]);

    for (i = 0; i < NUM_STATS; i++)
        SetMonData(temp, MON_DATA_HP_IV + i,  &ivs[i]);

    language = GAME_LANGUAGE;
    SetMonData(temp, MON_DATA_LANGUAGE, &language);
    SetMonData(temp, MON_DATA_MET_GAME, &gameMet);
    SetMonData(temp, MON_DATA_MARKINGS, &markings);

    friendship = 120;
    SetMonData(temp, MON_DATA_FRIENDSHIP, &friendship);
    SetMonData(temp, MON_DATA_POKERUS, &pokerus);
    SetMonData(temp, MON_DATA_EVENT_LEGAL, &isEventLegal);

    *duck = *temp;
}

static void AddHatchedMonToParty(u8 id)
{
    u8 isDuck = 0x46; // ?
    u16 species;
    u8 name[POKEMON_NAME_LENGTH + 1];
    u16 ball;
    u16 metLevel;
    u8 metLocation;
    struct Pokemon* mon = &gPlayerParty[id];

    CreateHatchedMon(mon, &gEnemyParty[0]);
    SetMonData(mon, MON_DATA_IS_DUCK, &isDuck);

    species = GetMonData(mon, MON_DATA_SPECIES);
    GetSpeciesName(name, species);
    SetMonData(mon, MON_DATA_NICKNAME, name);

    species = SpeciesToNationalPokedexNum(species);
    GetSetPokedexFlag(species, FLAG_SET_SEEN);
    GetSetPokedexFlag(species, FLAG_SET_CAUGHT);

    GetMonNickname2(mon, gStringVar1);

    ball = ITEM_POKE_BALL;
    SetMonData(mon, MON_DATA_POKEBALL, &ball);

    // A met level of 0 is interpreted on the summary screen as "hatched at"
    metLevel = 0;
    SetMonData(mon, MON_DATA_MET_LEVEL, &metLevel);

    metLocation = GetCurrentRegionMapSectionId();
    SetMonData(mon, MON_DATA_MET_LOCATION, &metLocation);

    MonRestorePP(mon);
    CalculateMonStats(mon);
}

void ScriptHatchMon(void)
{
    AddHatchedMonToParty(gSpecialVar_0x8004);
}

static bool8 _CheckDaycareMonReceivedMail(struct DayCare *daycare, u8 daycareId)
{
    u8 nickname[32];
    struct DaycareMon *daycareMon = &daycare->mons[daycareId];

    GetBoxMonNickname(&daycareMon->mon, nickname);
    if (daycareMon->mail.message.itemId != ITEM_NONE
        && (StringCompareWithoutExtCtrlCodes(nickname, daycareMon->mail.monName) != 0
         || StringCompareWithoutExtCtrlCodes(gSaveBlock2Ptr->playerName, daycareMon->mail.otName) != 0))
    {
        StringCopy(gStringVar1, nickname);
        TVShowConvertInternationalString(gStringVar2, daycareMon->mail.otName, daycareMon->mail.gameLanguage);
        TVShowConvertInternationalString(gStringVar3, daycareMon->mail.monName, daycareMon->mail.monLanguage);
        return TRUE;
    }
    return FALSE;
}

bool8 CheckDaycareMonReceivedMail(void)
{
    return _CheckDaycareMonReceivedMail(&gSaveBlock1Ptr->daycare, gSpecialVar_0x8004);
}

static u8 DuckHatchCreateMonSprite(u8 useAlt, u8 state, u8 partyId, u16* speciesLoc)
{
    u8 position = 0;
    u8 spriteId = 0;
    struct Pokemon* mon = NULL;

    if (useAlt == FALSE)
    {
        mon = &gPlayerParty[partyId];
        position = B_POSITION_OPPONENT_LEFT;
    }
    if (useAlt == TRUE)
    {
        // Alternate sprite allocation position. Never reached.
        mon = &gPlayerParty[partyId];
        position = B_POSITION_OPPONENT_RIGHT;
    }
    switch (state)
    {
    case 0:
        // Load mon sprite gfx
        {
            u16 species = GetMonData(mon, MON_DATA_SPECIES);
            u32 pid = GetMonData(mon, MON_DATA_PERSONALITY);
            HandleLoadSpecialPokePic(&gMonFrontPicTable[species],
                                     gMonSpritesGfxPtr->sprites.ptr[(useAlt * 2) + B_POSITION_OPPONENT_LEFT],
                                     species, pid);
            LoadCompressedSpritePalette(GetMonSpritePalStruct(mon));
            *speciesLoc = species; // handle forms?
        }
        break;
    case 1:
        // Create mon sprite
        SetMultiuseSpriteTemplateToPokemon(GetMonSpritePalStruct(mon)->tag, position);
        spriteId = CreateSprite(&gMultiuseSpriteTemplate, DUCK_X, DUCK_Y, 6);
        gSprites[spriteId].invisible = TRUE;
        gSprites[spriteId].callback = SpriteCallbackDummy;
        break;
    }
    return spriteId;
}

static void VBlankCB_DuckHatch(void)
{
    LoadOam();
    ProcessSpriteCopyRequests();
    TransferPlttBuffer();
}

void DuckHatch(void)
{
    if (gSaveBlock1Ptr->tx_Challenges_Nuzlocke)
        NuzlockeFlagSet(NuzlockeGetCurrentRegionMapSectionId());
    ScriptContext2_Enable();
    CreateTask(Task_DuckHatch, 10);
    FadeScreen(FADE_TO_BLACK, 0);
}

static void Task_DuckHatch(u8 taskId)
{
    if (!gPaletteFade.active)
    {
        CleanupOverworldWindowsAndTilemaps();
        SetMainCallback2(CB2_LoadDuckHatch);
        gFieldCallback = FieldCB_ContinueScriptHandleMusic;
        DestroyTask(taskId);
    }
}

static void CB2_LoadDuckHatch(void)
{
    switch (gMain.state)
    {
    case 0:
        SetGpuReg(REG_OFFSET_DISPCNT, 0);

        sDuckHatchData = Alloc(sizeof(*sDuckHatchData));
        AllocateMonSpritesGfx();
        sDuckHatchData->duckPartyId = gSpecialVar_0x8004;
        sDuckHatchData->duckShardVelocityId = 0;

        SetVBlankCallback(VBlankCB_DuckHatch);
        gSpecialVar_0x8005 = GetCurrentMapMusic();

        ResetTempTileDataBuffers();
        ResetBgsAndClearDma3BusyFlags(0);
        InitBgsFromTemplates(0, sBgTemplates_DuckHatch, ARRAY_COUNT(sBgTemplates_DuckHatch));

        ChangeBgX(1, 0, BG_COORD_SET);
        ChangeBgY(1, 0, BG_COORD_SET);
        ChangeBgX(0, 0, BG_COORD_SET);
        ChangeBgY(0, 0, BG_COORD_SET);

        SetBgAttribute(1, BG_ATTR_PRIORITY, 2);
        SetBgTilemapBuffer(1, Alloc(0x1000));
        SetBgTilemapBuffer(0, Alloc(0x2000));

        DeactivateAllTextPrinters();
        ResetPaletteFade();
        FreeAllSpritePalettes();
        ResetSpriteData();
        ResetTasks();
        ScanlineEffect_Stop();
        m4aSoundVSyncOn();
        gMain.state++;
        break;
    case 1:
        InitWindows(sWinTemplates_DuckHatch);
        sDuckHatchData->windowId = 0;
        gMain.state++;
        break;
    case 2:
        DecompressAndLoadBgGfxUsingHeap(0, gBattleTextboxTiles, 0, 0, 0);
        CopyToBgTilemapBuffer(0, gBattleTextboxTilemap, 0, 0);
        LoadCompressedPalette(gBattleTextboxPalette, 0, 0x20);
        gMain.state++;
        break;
    case 3:
        LoadSpriteSheet(&sDuckHatch_Sheet);
        LoadSpriteSheet(&sDuckShards_Sheet);
        LoadSpritePalette(&sDuck_SpritePalette);
        gMain.state++;
        break;
    case 4:
        CopyBgTilemapBufferToVram(0);
        AddHatchedMonToParty(sDuckHatchData->duckPartyId);
        gMain.state++;
        break;
    case 5:
        DuckHatchCreateMonSprite(FALSE, 0, sDuckHatchData->duckPartyId, &sDuckHatchData->species);
        gMain.state++;
        break;
    case 6:
        sDuckHatchData->monSpriteId = DuckHatchCreateMonSprite(FALSE, 1, sDuckHatchData->duckPartyId, &sDuckHatchData->species);
        gMain.state++;
        break;
    case 7:
        SetGpuReg(REG_OFFSET_DISPCNT, DISPCNT_OBJ_ON | DISPCNT_OBJ_1D_MAP);
        LoadPalette(gTradeGba2_Pal, 0x10, 0xA0);
        LoadBgTiles(1, gTradeGba_Gfx, 0x1420, 0);
        CopyToBgTilemapBuffer(1, gTradePlatform_Tilemap, 0x1000, 0);
        CopyBgTilemapBufferToVram(1);
        gMain.state++;
        break;
    case 8:
        SetMainCallback2(CB2_DuckHatch);
        sDuckHatchData->state = 0;
        break;
    }
    RunTasks();
    RunTextPrinters();
    AnimateSprites();
    BuildOamBuffer();
    UpdatePaletteFade();
}

static void DuckHatchSetMonNickname(void)
{
    SetMonData(&gPlayerParty[gSpecialVar_0x8004], MON_DATA_NICKNAME, gStringVar3);
    FreeMonSpritesGfx();
    Free(sDuckHatchData);
    SetMainCallback2(CB2_ReturnToField);
}

#define tTimer data[0]

static void Task_DuckHatchPlayBGM(u8 taskId)
{
    if (gTasks[taskId].tTimer == 0)
    {
        StopMapMusic();
        PlayRainStoppingSoundEffect();
    }

    if (gTasks[taskId].tTimer == 1)
        PlayBGM(MUS_EVOLUTION_INTRO);

    if (gTasks[taskId].tTimer > 60)
    {
        PlayBGM(MUS_EVOLUTION);
        DestroyTask(taskId);
    }
    gTasks[taskId].tTimer++;
}

static void CB2_DuckHatch(void)
{
    u16 species;
    u8 gender;
    u32 personality;

    switch (sDuckHatchData->state)
    {
    case 0:
        BeginNormalPaletteFade(PALETTES_ALL, 0, 16, 0, RGB_BLACK);
        sDuckHatchData->duckSpriteId = CreateSprite(&sSpriteTemplate_Duck, DUCK_X, DUCK_Y, 5);
        ShowBg(0);
        ShowBg(1);
        sDuckHatchData->state++;
        CreateTask(Task_DuckHatchPlayBGM, 5);
        break;
    case 1:
        if (!gPaletteFade.active)
        {
            FillWindowPixelBuffer(sDuckHatchData->windowId, PIXEL_FILL(0));
            sDuckHatchData->delayTimer = 0;
            sDuckHatchData->state++;
        }
        break;
    case 2:
        if (++sDuckHatchData->delayTimer > 30)
        {
            // Start hatching animation
            sDuckHatchData->state++;
            gSprites[sDuckHatchData->duckSpriteId].callback = SpriteCB_Duck_Shake1;
        }
        break;
    case 3:
        // Wait for hatching animation to finish
        if (gSprites[sDuckHatchData->duckSpriteId].callback == SpriteCallbackDummy)
        {
            species = GetMonData(&gPlayerParty[sDuckHatchData->duckPartyId], MON_DATA_SPECIES);
            DoMonFrontSpriteAnimation(&gSprites[sDuckHatchData->monSpriteId], species, FALSE, 1);
            sDuckHatchData->state++;
        }
        break;
    case 4:
        // Wait for Pokémon's front sprite animation
        if (gSprites[sDuckHatchData->monSpriteId].callback == SpriteCallbackDummy)
            sDuckHatchData->state++;
        break;
    case 5:
        // "{mon} hatched from duck" message/fanfare
        GetMonNickname2(&gPlayerParty[sDuckHatchData->duckPartyId], gStringVar1);
        StringExpandPlaceholders(gStringVar4, gText_HatchedFromDuck);
        DuckHatchPrintMessage(sDuckHatchData->windowId, gStringVar4, 0, 3, TEXT_SKIP_DRAW);
        PlayFanfare(MUS_EVOLVED);
        sDuckHatchData->state++;
        PutWindowTilemap(sDuckHatchData->windowId);
        CopyWindowToVram(sDuckHatchData->windowId, COPYWIN_FULL);
        break;
    case 6:
        if (IsFanfareTaskInactive())
            sDuckHatchData->state++;
        break;
    case 7: // Twice?
        if (IsFanfareTaskInactive())
            sDuckHatchData->state++;
        break;
    case 8:
        // Ready the nickname prompt
        GetMonNickname2(&gPlayerParty[sDuckHatchData->duckPartyId], gStringVar1);
        if (!gSaveBlock1Ptr->tx_Challenges_Nuzlocke) //tx_randomizer_and_challenges
        {
            StringExpandPlaceholders(gStringVar4, gText_NicknameHatchPrompt);
            DuckHatchPrintMessage(sDuckHatchData->windowId, gStringVar4, 0, 2, 1);
        }
        sDuckHatchData->state++;
        break;
    case 9:
        // Print the nickname prompt
        if (!IsTextPrinterActive(sDuckHatchData->windowId))
        {
            LoadUserWindowBorderGfx(sDuckHatchData->windowId, 0x140, 0xE0);
            if (!gSaveBlock1Ptr->tx_Challenges_Nuzlocke) //tx_randomizer_and_challenges
                CreateYesNoMenu(&sYesNoWinTemplate, 0x140, 0xE, 0);
            sDuckHatchData->state++;
        }
        break;
    case 10:
        if (gSaveBlock1Ptr->tx_Challenges_Nuzlocke) //tx_randomizer_and_challenges
        {
            GetMonNickname2(&gPlayerParty[sDuckHatchData->duckPartyId], gStringVar3);
            species = GetMonData(&gPlayerParty[sDuckHatchData->duckPartyId], MON_DATA_SPECIES);
            gender = GetMonGender(&gPlayerParty[sDuckHatchData->duckPartyId]);
            personality = GetMonData(&gPlayerParty[sDuckHatchData->duckPartyId], MON_DATA_PERSONALITY, 0);
            DoNamingScreen(NAMING_SCREEN_NICKNAME, gStringVar3, species, gender, personality, DuckHatchSetMonNickname);
        }
        // Handle the nickname prompt input
        switch (Menu_ProcessInputNoWrapClearOnChoose())
        {
        case 0: // Yes
            GetMonNickname2(&gPlayerParty[sDuckHatchData->duckPartyId], gStringVar3);
            species = GetMonData(&gPlayerParty[sDuckHatchData->duckPartyId], MON_DATA_SPECIES);
            gender = GetMonGender(&gPlayerParty[sDuckHatchData->duckPartyId]);
            personality = GetMonData(&gPlayerParty[sDuckHatchData->duckPartyId], MON_DATA_PERSONALITY, 0);
            DoNamingScreen(NAMING_SCREEN_NICKNAME, gStringVar3, species, gender, personality, DuckHatchSetMonNickname);
            break;
        case 1: // No
        case MENU_B_PRESSED:
            sDuckHatchData->state++;
            break;
        }
        break;
    case 11:
        BeginNormalPaletteFade(PALETTES_ALL, 0, 0, 16, RGB_BLACK);
        sDuckHatchData->state++;
        break;
    case 12:
        if (!gPaletteFade.active)
        {
            FreeMonSpritesGfx();
            RemoveWindow(sDuckHatchData->windowId);
            UnsetBgTilemapBuffer(0);
            UnsetBgTilemapBuffer(1);
            Free(sDuckHatchData);
            SetMainCallback2(CB2_ReturnToField);
        }
        break;
    }

    RunTasks();
    RunTextPrinters();
    AnimateSprites();
    BuildOamBuffer();
    UpdatePaletteFade();
}

#define sTimer      data[0]
#define sSinIdx     data[1]
#define sDelayTimer data[2]

static void SpriteCB_Duck_Shake1(struct Sprite* sprite)
{
    if (++sprite->sTimer > 20)
    {
        sprite->callback = SpriteCB_Duck_Shake2;
        sprite->sTimer = 0;
    }
    else
    {
        // Shake duck
        sprite->sSinIdx = (sprite->sSinIdx + 20) & 0xFF;
        sprite->x2 = Sin(sprite->sSinIdx, 1);
        if (sprite->sTimer == 15)
        {
            // First duck crack
            PlaySE(SE_BALL);
            StartSpriteAnim(sprite, DUCK_ANIM_CRACKED_1);
            CreateRandomDuckShardSprite();
        }
    }
}

static void SpriteCB_Duck_Shake2(struct Sprite* sprite)
{
    if (++sprite->sDelayTimer > 30)
    {
        if (++sprite->sTimer > 20)
        {
            sprite->callback = SpriteCB_Duck_Shake3;
            sprite->sTimer = 0;
            sprite->sDelayTimer = 0;
        }
        else
        {
            // Shake duck
            sprite->sSinIdx = (sprite->sSinIdx + 20) & 0xFF;
            sprite->x2 = Sin(sprite->sSinIdx, 2);
            if (sprite->sTimer == 15)
            {
                // Second duck crack
                PlaySE(SE_BALL);
                StartSpriteAnim(sprite, DUCK_ANIM_CRACKED_2);
            }
        }
    }
}

static void SpriteCB_Duck_Shake3(struct Sprite* sprite)
{
    if (++sprite->sDelayTimer > 30)
    {
        if (++sprite->sTimer > 38)
        {
            u16 species;
            sprite->callback = SpriteCB_Duck_WaitHatch;
            sprite->sTimer = 0;
            species = GetMonData(&gPlayerParty[sDuckHatchData->duckPartyId], MON_DATA_SPECIES);
            gSprites[sDuckHatchData->monSpriteId].x2 = 0;
            gSprites[sDuckHatchData->monSpriteId].y2 = 0;
        }
        else
        {
            // Shake duck
            sprite->sSinIdx = (sprite->sSinIdx + 20) & 0xFF;
            sprite->x2 = Sin(sprite->sSinIdx, 2);
            if (sprite->sTimer == 15)
            {
                // Third duck crack
                // This ineffectually sets the animation to the frame it's already using.
                // They likely meant to use the 3rd and final cracked frame of the duck, which goes unused as a result.
                PlaySE(SE_BALL);
            #ifdef BUGFIX
                StartSpriteAnim(sprite, DUCK_ANIM_CRACKED_3);
            #else
                StartSpriteAnim(sprite, DUCK_ANIM_CRACKED_2);
            #endif
                CreateRandomDuckShardSprite();
                CreateRandomDuckShardSprite();
            }
            if (sprite->sTimer == 30)
                PlaySE(SE_BALL);
        }
    }
}

static void SpriteCB_Duck_WaitHatch(struct Sprite* sprite)
{
    if (++sprite->sTimer > 50)
    {
        sprite->callback = SpriteCB_Duck_Hatch;
        sprite->sTimer = 0;
    }
}

static void SpriteCB_Duck_Hatch(struct Sprite* sprite)
{
    s16 i;

    // Fade to white to hide transition from duck to Pokémon
    if (sprite->sTimer == 0)
        BeginNormalPaletteFade(PALETTES_ALL, -1, 0, 16, RGB_WHITEALPHA);

    // Create a shower of 16 duck shards in 4 groups of 4
    if ((u32)sprite->sTimer < 4)
    {
        for (i = 0; i < 4; i++)
            CreateRandomDuckShardSprite();
    }

    sprite->sTimer++;

    if (!gPaletteFade.active)
    {
        // Screen is hidden by the fade to white, hide duck
        PlaySE(SE_DUCK_HATCH);
        sprite->invisible = TRUE;
        sprite->callback = SpriteCB_Duck_Reveal;
        sprite->sTimer = 0;
    }
}

static void SpriteCB_Duck_Reveal(struct Sprite* sprite)
{
    if (sprite->sTimer == 0)
    {
        // Reveal hatched Pokémon
        gSprites[sDuckHatchData->monSpriteId].invisible = FALSE;
        StartSpriteAffineAnim(&gSprites[sDuckHatchData->monSpriteId], BATTLER_AFFINE_EMERGE);
    }

    // Fade back from white for reveal
    if (sprite->sTimer == 8)
        BeginNormalPaletteFade(PALETTES_ALL, -1, 16, 0, RGB_WHITEALPHA);

    if (sprite->sTimer <= 9)
        gSprites[sDuckHatchData->monSpriteId].y--;

    if (sprite->sTimer > 40)
        sprite->callback = SpriteCallbackDummy; // Finished

    sprite->sTimer++;
}

#define sVelocX data[1]
#define sVelocY data[2]
#define sAccelY data[3]
#define sDeltaX data[4]
#define sDeltaY data[5]

static void SpriteCB_DuckShard(struct Sprite* sprite)
{
    sprite->sDeltaX += sprite->sVelocX;
    sprite->sDeltaY += sprite->sVelocY;

    sprite->x2 = sprite->sDeltaX / 256;
    sprite->y2 = sprite->sDeltaY / 256;

    sprite->sVelocY += sprite->sAccelY;

    if (sprite->y + sprite->y2 > sprite->y + 20 && sprite->sVelocY > 0)
        DestroySprite(sprite);
}

static void CreateRandomDuckShardSprite(void)
{
    u16 spriteAnimIndex;

    s16 velocityX = sDuckShardVelocities[sDuckHatchData->duckShardVelocityId][0];
    s16 velocityY = sDuckShardVelocities[sDuckHatchData->duckShardVelocityId][1];
    sDuckHatchData->duckShardVelocityId++;

    // Randomly choose one of the 4 shard images
    spriteAnimIndex = Random() % ARRAY_COUNT(sSpriteAnimTable_DuckShard);

    CreateDuckShardSprite(DUCK_X, DUCK_Y - 15, velocityX, velocityY, 100, spriteAnimIndex);
}

static void CreateDuckShardSprite(u8 x, u8 y, s16 velocityX, s16 velocityY, s16 acceleration, u8 spriteAnimIndex)
{
    u8 spriteId = CreateSprite(&sSpriteTemplate_DuckShard, x, y, 4);
    gSprites[spriteId].sVelocX = velocityX;
    gSprites[spriteId].sVelocY = velocityY;
    gSprites[spriteId].sAccelY = acceleration;
    StartSpriteAnim(&gSprites[spriteId], spriteAnimIndex);
}

static void DuckHatchPrintMessage(u8 windowId, u8* string, u8 x, u8 y, u8 speed)
{
    FillWindowPixelBuffer(windowId, PIXEL_FILL(15));
    sDuckHatchData->textColor[0] = 0;
    sDuckHatchData->textColor[1] = 5;
    sDuckHatchData->textColor[2] = 6;
    AddTextPrinterParameterized4(windowId, FONT_NORMAL, x, y, 0, 0, sDuckHatchData->textColor, speed, string);
}

u8 GetDuckCyclesToSubtract(void)
{
    u8 count, i;
    for (count = CalculatePlayerPartyCount(), i = 0; i < count; i++)
    {
        if (!GetMonData(&gPlayerParty[i], MON_DATA_SANITY_IS_DUCK))
        {
            u16 ability = GetMonAbility(&gPlayerParty[i]);
            if (ability == ABILITY_MAGMA_ARMOR
             || ability == ABILITY_FLAME_BODY
             || ability == ABILITY_STEAM_ENGINE)
                return 2;
        }
    }
    return 1;
}

u16 CountPartyAliveNonDuckMons(void)
{
    u16 aliveNonDuckMonsCount = CountStorageNonDuckMons();
    aliveNonDuckMonsCount += CountPartyAliveNonDuckMonsExcept(PARTY_SIZE);
    return aliveNonDuckMonsCount;
}
