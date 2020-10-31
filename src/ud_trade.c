#include "global.h"
#include "ud_trade.h"
#include "data.h"
#include "event_data.h"
#include "event_object_movement.h"
#include "event_scripts.h"
#include "field_message_box.h"
#include "field_screen_effect.h"
#include "international_string_util.h"
#include "item.h"
#include "item_icon.h"
#include "list_menu.h"
#include "main.h"
#include "map_name_popup.h"
#include "menu.h"
#include "overworld.h"
#include "pokedex.h"
#include "pokemon.h"
#include "pokemon_icon.h"
#include "pokemon_storage_system.h"
#include "random.h"
#include "region_map.h"
#include "rtc.h"
#include "script.h"
#include "script_pokemon_util.h"
#include "sound.h"
#include "strings.h"
#include "string_util.h"
#include "task.h"
#include "pokemon_summary_screen.h"
#include "constants/abilities.h"
#include "constants/flags.h"
#include "constants/items.h"
#include "constants/map_groups.h"
#include "constants/songs.h"
#include "constants/species.h"

// Constants
#define UDTRADE_MAIN_MENU_WIDTH 13
#define UDTRADE_MAIN_MENU_HEIGHT 2

// Define functions
static void UDTrade_ShowMenu(void (*HandleInput)(u8), struct ListMenuTemplate LMtemplate);
void UDTrade_ShowMainMenu(void);
static void UDTrade_DestroyMenu(u8);
static void UDTradeAction_Cancel(u8);
static void UDTradeAction_DestroyExtraWindow(u8 taskId);

static void UDTradeTask_HandleMenuInput_Main(u8);

static void UDTradeAction_VanillaDimension(u8 taskId);

static void UDTradeTask_HandleMenuInput(u8 taskId, void (*HandleInput)(u8));
static void UDTradeAction_OpenSubMenu(u8 taskId, struct ListMenuTemplate LMtemplate);

extern u8 UDTrade_EventScript_UDTradeCenter[];
extern u8 CableClub_EventScript_AbortLink[];

// *******************************
// Enums
enum { // Main
    UDTRADE_VANILLA_DIMENSION,
    UDTRADE_MENU_CANCEL
};

// Text
// Main Menu
static const u8 gUDTradeText_VanillaDimension[] =   _("Vanilla Dimension");
static const u8 gUDTradeText_Cancel[] =               _("Cancel");

// *******************************
// List Menu Items
static const struct ListMenuItem sUDTradeMenu_Items_Main[] =
{
    [UDTRADE_VANILLA_DIMENSION]  = {gUDTradeText_VanillaDimension,   UDTRADE_VANILLA_DIMENSION},
    [UDTRADE_MENU_CANCEL]        = {gUDTradeText_Cancel,             UDTRADE_MENU_CANCEL}
};

// *******************************
// Menu Actions
static void (*const sUDTradeMenu_Actions_Main[])(u8) =
{
    [UDTRADE_VANILLA_DIMENSION]  = UDTradeAction_VanillaDimension,
    [UDTRADE_MENU_CANCEL]        = UDTradeAction_Cancel
};

// *******************************
// Windows
static const struct WindowTemplate sUDTradeMenuWindowTemplate =
{
    .bg = 0,
    .tilemapLeft = 1,
    .tilemapTop = 1,
    .width = UDTRADE_MAIN_MENU_WIDTH,
    .height = 2 * UDTRADE_MAIN_MENU_HEIGHT,
    .paletteNum = 15,
    .baseBlock = 1,
};

// *******************************
// List Menu Templates
static const struct ListMenuTemplate sUDTradeMenu_ListTemplate_Main =
{
    .items = sUDTradeMenu_Items_Main,
    .moveCursorFunc = ListMenuDefaultCursorMoveFunc,
    .totalItems = ARRAY_COUNT(sUDTradeMenu_Items_Main),
};

// *******************************
// Functions universal
void UDTrade_ShowMainMenu(void)
{
    UDTrade_ShowMenu(UDTradeTask_HandleMenuInput_Main, sUDTradeMenu_ListTemplate_Main);
}
static void UDTrade_ShowMenu(void (*HandleInput)(u8), struct ListMenuTemplate LMtemplate)
{
    struct ListMenuTemplate menuTemplate;
    u8 windowId;
    u8 menuTaskId;
    u8 inputTaskId;

    // create window
    HideMapNamePopUpWindow();
    LoadMessageBoxAndBorderGfx();
    windowId = AddWindow(&sUDTradeMenuWindowTemplate);
    DrawStdWindowFrame(windowId, FALSE);

    // create list menu
    menuTemplate = LMtemplate;
    menuTemplate.maxShowed = UDTRADE_MAIN_MENU_HEIGHT;
    menuTemplate.windowId = windowId;
    menuTemplate.header_X = 0;
    menuTemplate.item_X = 8;
    menuTemplate.cursor_X = 0;
    menuTemplate.upText_Y = 1;
    menuTemplate.cursorPal = 2;
    menuTemplate.fillValue = 1;
    menuTemplate.cursorShadowPal = 3;
    menuTemplate.lettersSpacing = 1;
    menuTemplate.itemVerticalPadding = 0;
    menuTemplate.scrollMultiple = LIST_NO_MULTIPLE_SCROLL;
    menuTemplate.fontId = 1;
    menuTemplate.cursorKind = 0;
    menuTaskId = ListMenuInit(&menuTemplate, 0, 0);

    // draw everything
    CopyWindowToVram(windowId, 3);

    // create input handler task
    inputTaskId = CreateTask(HandleInput, 3);
    gTasks[inputTaskId].data[0] = menuTaskId;
    gTasks[inputTaskId].data[1] = windowId;
}
static void UDTrade_DestroyMenu(u8 taskId)
{
    DestroyListMenuTask(gTasks[taskId].data[0], NULL, NULL);
    ClearStdWindowAndFrame(gTasks[taskId].data[1], TRUE);
    RemoveWindow(gTasks[taskId].data[1]);
    DestroyTask(taskId);
}
static void UDTradeAction_Cancel(u8 taskId)
{
    VarSet(VAR_DIMENSION_LINK, 0);
    UDTrade_DestroyMenu(taskId);
    ScriptContext2_Enable();
    ScriptContext1_SetupScript(CableClub_EventScript_AbortLink);
}
static void UDTradeAction_DestroyExtraWindow(u8 taskId)
{
    ClearStdWindowAndFrame(gTasks[taskId].data[1], TRUE);
    RemoveWindow(gTasks[taskId].data[1]);

    ClearStdWindowAndFrame(gTasks[taskId].data[2], TRUE);
    RemoveWindow(gTasks[taskId].data[2]);

    DestroyTask(taskId);
    EnableBothScriptContexts();
}


// *******************************
// Handle Inputs
static void UDTradeTask_HandleMenuInput_Main(u8 taskId)
{
    void (*func)(u8);
    u32 input = ListMenu_ProcessInput(gTasks[taskId].data[0]);

    if (gMain.newKeys & A_BUTTON)
    {
        PlaySE(SE_SELECT);
        if ((func = sUDTradeMenu_Actions_Main[input]) != NULL)
            func(taskId);
    }
    else if (gMain.newKeys & B_BUTTON)
    {
        PlaySE(SE_SELECT);
        UDTrade_DestroyMenu(taskId);
        ScriptContext2_Enable();
        ScriptContext1_SetupScript(CableClub_EventScript_AbortLink);
    }
}

static void UDTradeAction_VanillaDimension(u8 taskId)
{
    PlaySE(SE_SELECT);
    VarSet(VAR_DIMENSION_LINK, 1);
    UDTrade_DestroyMenu(taskId);
    ScriptContext2_Enable();
    ScriptContext1_SetupScript(UDTrade_EventScript_UDTradeCenter);
}


