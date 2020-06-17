#include "debug.h"

#ifdef DEBUG_MENU

#include "global.h"
#include "list_menu.h"
#include "main.h"
#include "map_name_popup.h"
#include "menu.h"
#include "script.h"
#include "sound.h"
#include "strings.h"
#include "task.h"
#include "constants/songs.h"

#define DEBUG_MAIN_MENU_HEIGHT 9
#define DEBUG_MAIN_MENU_WIDTH 11

static void Debug_ShowMenu(void (*HandleInput)(u8), struct ListMenuTemplate LMtemplate);
void Debug_ShowMainMenu(void);
static void Debug_DestroyMenu(u8);
static void DebugAction_PlayBoo(u8);
static void DebugAction_CheckSaveBlock(u8);
static void DebugAction_Cancel(u8);
static void DebugAction_OpenSpaceManageMenu(u8);
static void DebugAction_OpenSub1(u8);
static void DebugTask_HandleMenuInput_Main(u8);
static void DebugTask_HandleMenuInput_SpaceManage(u8);
static void DebugTask_HandleMenuInput_Sub1(u8);

extern u8 Debug_CheckSaveBlock[];

enum DebugMenuOptions{
    DEBUG_MENU_ITEM_SPACEMANAGE,
    DEBUG_MENU_ITEM_OPTION_2,
    DEBUG_MENU_ITEM_OPTION_3,
    DEBUG_MENU_ITEM_OPTION_4,
    DEBUG_MENU_ITEM_OPTION_5,
    DEBUG_MENU_ITEM_OPTION_6,
    DEBUG_MENU_ITEM_CANCEL,
};

enum DebugMenuOptions_SaveBlocks{
    SAVEBLOCKS_MENU_ITEM_CHECKSAVEBLOCK,
    SAVEBLOCKS_MENU_ITEM_SAVEBLOCK2,
    SAVEBLOCKS_MENU_ITEM_PKMNSTORAGE,
};

// Main Menu
static const u8 gDebugText_SpaceManagement[] = _("Space Manage");
static const u8 gDebugText_Option2[] = _("Option 2");
static const u8 gDebugText_Option3[] = _("Option 3");
static const u8 gDebugText_Option4[] = _("Option 4");
static const u8 gDebugText_Option5[] = _("Option 5");
static const u8 gDebugText_Option6[] = _("Option 6");
static const u8 gDebugText_Cancel[] = _("Cancel");

static const u8 gDebugText_SaveBlocks[] = _("SaveBlocks");
static const u8 gDebugText_None[] = _("None");

// Sub Menu 1
static const u8 gDebugText__Sub1_OptionA[] = _("Option A");

static const struct ListMenuItem sDebugMenuItems[] =
{
    [DEBUG_MENU_ITEM_SPACEMANAGE] = {gDebugText_SpaceManagement, DEBUG_MENU_ITEM_SPACEMANAGE},
    [DEBUG_MENU_ITEM_OPTION_2] = {gDebugText_Option2, DEBUG_MENU_ITEM_OPTION_2},
    [DEBUG_MENU_ITEM_OPTION_3] = {gDebugText_Option3, DEBUG_MENU_ITEM_OPTION_3},
    [DEBUG_MENU_ITEM_OPTION_4] = {gDebugText_Option4, DEBUG_MENU_ITEM_OPTION_4},
    [DEBUG_MENU_ITEM_OPTION_5] = {gDebugText_Option5, DEBUG_MENU_ITEM_OPTION_5},
    [DEBUG_MENU_ITEM_OPTION_6] = {gDebugText_Option6, DEBUG_MENU_ITEM_OPTION_6},
    [DEBUG_MENU_ITEM_CANCEL] = {gDebugText_Cancel, DEBUG_MENU_ITEM_CANCEL}
};

static const struct ListMenuItem sDebugMenu_SpaceManage_Items[] =
{
    [SAVEBLOCKS_MENU_ITEM_CHECKSAVEBLOCK] = {gDebugText_SaveBlocks, SAVEBLOCKS_MENU_ITEM_CHECKSAVEBLOCK},
    [SAVEBLOCKS_MENU_ITEM_SAVEBLOCK2] = {gDebugText_None, SAVEBLOCKS_MENU_ITEM_SAVEBLOCK2},
    [SAVEBLOCKS_MENU_ITEM_PKMNSTORAGE] = {gDebugText_None, SAVEBLOCKS_MENU_ITEM_PKMNSTORAGE},
};

static const struct ListMenuItem sDebugMenu_Sub1_Items[] =
{
    [0] = {gDebugText__Sub1_OptionA, 0},
    [1] = {gDebugText_Cancel, 1}
};

static void (*const sDebugMenuActions[])(u8) =
{
    [DEBUG_MENU_ITEM_SPACEMANAGE] = DebugAction_OpenSpaceManageMenu,
    [DEBUG_MENU_ITEM_OPTION_2] = DebugAction_OpenSub1,
    [DEBUG_MENU_ITEM_OPTION_3] = NULL,
    [DEBUG_MENU_ITEM_OPTION_4] = NULL,
    [DEBUG_MENU_ITEM_OPTION_5] = NULL,
    [DEBUG_MENU_ITEM_OPTION_6] = NULL,
    [DEBUG_MENU_ITEM_CANCEL] = DebugAction_Cancel
};

static void (*const sDebugMenu_SaveBlocks_Actions[])(u8) =
{
    [SAVEBLOCKS_MENU_ITEM_CHECKSAVEBLOCK] = DebugAction_CheckSaveBlock,
    [SAVEBLOCKS_MENU_ITEM_SAVEBLOCK2] = NULL,
    [SAVEBLOCKS_MENU_ITEM_PKMNSTORAGE] = NULL,
};

static void (*const sDebugMenu_Sub1_Actions[])(u8) =
{
    [0] = DebugAction_PlayBoo,
    [1] = DebugAction_Cancel
};

static const struct WindowTemplate sDebugMenuWindowTemplate =
{
    .bg = 0,
    .tilemapLeft = 1,
    .tilemapTop = 1,
    .width = DEBUG_MAIN_MENU_WIDTH,
    .height = 2 * DEBUG_MAIN_MENU_HEIGHT,
    .paletteNum = 15,
    .baseBlock = 1,
};

static const struct ListMenuTemplate sDebugMenuListTemplate =
{
    .items = sDebugMenuItems,
    .moveCursorFunc = ListMenuDefaultCursorMoveFunc,
    .totalItems = ARRAY_COUNT(sDebugMenuItems),
};

static const struct ListMenuTemplate sDebugMenu_SpaceManage_ListTemplate =
{
    .items = sDebugMenu_SpaceManage_Items,
    .moveCursorFunc = ListMenuDefaultCursorMoveFunc,
    .totalItems = ARRAY_COUNT(sDebugMenu_SpaceManage_Items),
};

static const struct ListMenuTemplate sDebugMenu_Sub1_ListTemplate =
{
    .items = sDebugMenu_Sub1_Items,
    .moveCursorFunc = ListMenuDefaultCursorMoveFunc,
    .totalItems = ARRAY_COUNT(sDebugMenu_Sub1_Items),
};

void Debug_ShowMainMenu(void)
{
    Debug_ShowMenu(DebugTask_HandleMenuInput_Main, sDebugMenuListTemplate);
}

static void Debug_ShowMenu(void (*HandleInput)(u8), struct ListMenuTemplate LMtemplate)
{
    struct ListMenuTemplate menuTemplate;
    u8 windowId;
    u8 menuTaskId;
    u8 inputTaskId;

    // create window
    HideMapNamePopUpWindow();
    LoadMessageBoxAndBorderGfx();
    windowId = AddWindow(&sDebugMenuWindowTemplate);
    DrawStdWindowFrame(windowId, FALSE);

    // create list menu
    menuTemplate = LMtemplate;
    menuTemplate.maxShowed = DEBUG_MAIN_MENU_HEIGHT;
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

static void Debug_DestroyMenu(u8 taskId)
{
    DestroyListMenuTask(gTasks[taskId].data[0], NULL, NULL);
    ClearStdWindowAndFrame(gTasks[taskId].data[1], TRUE);
    RemoveWindow(gTasks[taskId].data[1]);
    DestroyTask(taskId);
}

// Handle Inputs
static void DebugTask_HandleMenuInput_Main(u8 taskId)
{
    void (*func)(u8);
    u32 input = ListMenu_ProcessInput(gTasks[taskId].data[0]);

    if (gMain.newKeys & A_BUTTON)
    {
        PlaySE(SE_SELECT);
        if ((func = sDebugMenuActions[input]) != NULL)
            func(taskId);
    }
    else if (gMain.newKeys & B_BUTTON)
    {
        PlaySE(SE_SELECT);
        Debug_DestroyMenu(taskId);
        EnableBothScriptContexts();
    }
}
static void DebugTask_HandleMenuInput_SpaceManage(u8 taskId)
{
    void (*func)(u8);
    u32 input = ListMenu_ProcessInput(gTasks[taskId].data[0]);

    if (gMain.newKeys & A_BUTTON)
    {
        PlaySE(SE_SELECT);
        if ((func = sDebugMenu_SaveBlocks_Actions[input]) != NULL)
            func(taskId);
    }
    else if (gMain.newKeys & B_BUTTON)
    {
        PlaySE(SE_SELECT);
        Debug_DestroyMenu(taskId);
        Debug_ShowMainMenu();
    }
}
static void DebugTask_HandleMenuInput_Sub1(u8 taskId)
{
    void (*func)(u8);
    u32 input = ListMenu_ProcessInput(gTasks[taskId].data[0]);

    if (gMain.newKeys & A_BUTTON)
    {
        PlaySE(SE_SELECT);
        if ((func = sDebugMenu_Sub1_Actions[input]) != NULL)
            func(taskId);
    }
    else if (gMain.newKeys & B_BUTTON)
    {
        PlaySE(SE_SELECT);
        Debug_DestroyMenu(taskId);
        Debug_ShowMainMenu();
    }
}

static void DebugAction_Cancel(u8 taskId)
{
    Debug_DestroyMenu(taskId);
    EnableBothScriptContexts();
}

static void DebugAction_OpenSpaceManageMenu(u8 taskId)
{
    Debug_DestroyMenu(taskId);
    Debug_ShowMenu(DebugTask_HandleMenuInput_SpaceManage, sDebugMenu_SpaceManage_ListTemplate);
}

static void DebugAction_OpenSub1(u8 taskId)
{
    Debug_DestroyMenu(taskId);
    Debug_ShowMenu(DebugTask_HandleMenuInput_Sub1, sDebugMenu_Sub1_ListTemplate);
}

static void DebugAction_PlayBoo(u8 taskId)
{
    PlayBGM(MUS_BATTLE33);
}

static void DebugAction_CheckSaveBlock(u8 taskId)
{
    Debug_DestroyMenu(taskId);
    ScriptContext2_Enable();
    ScriptContext1_SetupScript(Debug_CheckSaveBlock);
}

#endif
