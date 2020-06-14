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

#define DEBUG_MAIN_MENU_HEIGHT 7
#define DEBUG_MAIN_MENU_WIDTH 11

static void Debug_ShowMenu(void (*HandleInput)(u8), struct WindowTemplate WTemplate, struct ListMenuTemplate LMtemplate);
void Debug_ShowMainMenu(void);
static void Debug_DestroyMainMenu(u8);
static void DebugAction_PlayBoo(u8);
static void DebugAction_Cancel(u8);
static void DebugAction_OpenSub1(u8);
static void DebugTask_HandleMainMenuInput(u8);
static void DebugTask_HandleSub1MenuInput(u8);

enum {
    DEBUG_MENU_ITEM_OPTION_1,
    DEBUG_MENU_ITEM_OPTION_2,
    DEBUG_MENU_ITEM_OPTION_3,
    DEBUG_MENU_ITEM_OPTION_4,
    DEBUG_MENU_ITEM_OPTION_5,
    DEBUG_MENU_ITEM_OPTION_6,
    DEBUG_MENU_ITEM_OPTION_7,
    DEBUG_MENU_ITEM_OPTION_8,
    DEBUG_MENU_ITEM_OPTION_9,
    DEBUG_MENU_ITEM_OPTION_10,
    DEBUG_MENU_ITEM_OPTION_11,
    DEBUG_MENU_ITEM_CANCEL,
};

// Main Menu
static const u8 gDebugText_Option1[] = _("Option 1");
static const u8 gDebugText_Option2[] = _("Option 2");
static const u8 gDebugText_Option3[] = _("Option 3");
static const u8 gDebugText_Option4[] = _("Option 4");
static const u8 gDebugText_Option5[] = _("Option 5");
static const u8 gDebugText_Option6[] = _("Option 6");
static const u8 gDebugText_Option7[] = _("Option 7");
static const u8 gDebugText_Option8[] = _("Option 8");
static const u8 gDebugText_Option9[] = _("Option 9");
static const u8 gDebugText_Option10[] = _("Option 10");
static const u8 gDebugText_Option11[] = _("Option 11");
static const u8 gDebugText_Cancel[] = _("Cancel");

// Sub Menu 1
static const u8 gDebugText__Sub1_OptionA[] = _("Option A");

static const struct ListMenuItem sDebugMenuItems[] =
{
    [DEBUG_MENU_ITEM_OPTION_1] = {gDebugText_Option1, DEBUG_MENU_ITEM_OPTION_1},
    [DEBUG_MENU_ITEM_OPTION_2] = {gDebugText_Option2, DEBUG_MENU_ITEM_OPTION_2},
    [DEBUG_MENU_ITEM_OPTION_3] = {gDebugText_Option3, DEBUG_MENU_ITEM_OPTION_3},
    [DEBUG_MENU_ITEM_OPTION_4] = {gDebugText_Option4, DEBUG_MENU_ITEM_OPTION_4},
    [DEBUG_MENU_ITEM_OPTION_5] = {gDebugText_Option5, DEBUG_MENU_ITEM_OPTION_5},
    [DEBUG_MENU_ITEM_OPTION_6] = {gDebugText_Option6, DEBUG_MENU_ITEM_OPTION_6},
    [DEBUG_MENU_ITEM_OPTION_7] = {gDebugText_Option7, DEBUG_MENU_ITEM_OPTION_7},
    [DEBUG_MENU_ITEM_OPTION_8] = {gDebugText_Option8, DEBUG_MENU_ITEM_OPTION_8},
    [DEBUG_MENU_ITEM_OPTION_9] = {gDebugText_Option9, DEBUG_MENU_ITEM_OPTION_9},
    [DEBUG_MENU_ITEM_OPTION_10] = {gDebugText_Option10, DEBUG_MENU_ITEM_OPTION_10},
    [DEBUG_MENU_ITEM_OPTION_11] = {gDebugText_Option11, DEBUG_MENU_ITEM_OPTION_11},
    [DEBUG_MENU_ITEM_CANCEL] = {gDebugText_Cancel, DEBUG_MENU_ITEM_CANCEL}
};

static const struct ListMenuItem sDebugMenu_Sub1_Items[] =
{
    [0] = {gDebugText__Sub1_OptionA, 0},
    [1] = {gDebugText_Cancel, 1}
};

static void (*const sDebugMenuActions[])(u8) =
{
    [DEBUG_MENU_ITEM_OPTION_1] = DebugAction_OpenSub1,
    [DEBUG_MENU_ITEM_OPTION_2] = NULL,
    [DEBUG_MENU_ITEM_OPTION_3] = NULL,
    [DEBUG_MENU_ITEM_OPTION_4] = NULL,
    [DEBUG_MENU_ITEM_OPTION_5] = NULL,
    [DEBUG_MENU_ITEM_OPTION_6] = NULL,
    [DEBUG_MENU_ITEM_OPTION_7] = NULL,
    [DEBUG_MENU_ITEM_OPTION_8] = NULL,
    [DEBUG_MENU_ITEM_OPTION_9] = NULL,
    [DEBUG_MENU_ITEM_OPTION_10] = NULL,
    [DEBUG_MENU_ITEM_OPTION_11] = NULL,
    [DEBUG_MENU_ITEM_CANCEL] = DebugAction_Cancel
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
    .maxShowed = DEBUG_MAIN_MENU_HEIGHT,
    .windowId = 0,
    .header_X = 0,
    .item_X = 8,
    .cursor_X = 0,
    .upText_Y = 1,
    .cursorPal = 2,
    .fillValue = 1,
    .cursorShadowPal = 3,
    .lettersSpacing = 1,
    .itemVerticalPadding = 0,
    .scrollMultiple = LIST_NO_MULTIPLE_SCROLL,
    .fontId = 1,
    .cursorKind = 0
};

static const struct ListMenuTemplate sDebugMenu_Sub1_ListTemplate =
{
    .items = sDebugMenu_Sub1_Items,
    .moveCursorFunc = ListMenuDefaultCursorMoveFunc,
    .totalItems = ARRAY_COUNT(sDebugMenu_Sub1_Items),
    .maxShowed = DEBUG_MAIN_MENU_HEIGHT,
    .windowId = 0,
    .header_X = 0,
    .item_X = 8,
    .cursor_X = 0,
    .upText_Y = 1,
    .cursorPal = 2,
    .fillValue = 1,
    .cursorShadowPal = 3,
    .lettersSpacing = 1,
    .itemVerticalPadding = 0,
    .scrollMultiple = LIST_NO_MULTIPLE_SCROLL,
    .fontId = 1,
    .cursorKind = 0
};

void Debug_ShowMainMenu(void)
{
    Debug_ShowMenu(DebugTask_HandleMainMenuInput, sDebugMenuWindowTemplate, sDebugMenuListTemplate);
}

static void Debug_ShowMenu(void (*HandleInput)(u8), struct WindowTemplate WTemplate, struct ListMenuTemplate LMtemplate)
{
    struct ListMenuTemplate menuTemplate;
    u8 windowId;
    u8 menuTaskId;
    u8 inputTaskId;

    // create window
    HideMapNamePopUpWindow();
    LoadMessageBoxAndBorderGfx();
    windowId = AddWindow(&WTemplate);
    DrawStdWindowFrame(windowId, FALSE);

    // create list menu
    menuTemplate = LMtemplate;
    menuTemplate.windowId = windowId;
    menuTaskId = ListMenuInit(&menuTemplate, 0, 0);

    // draw everything
    CopyWindowToVram(windowId, 3);

    // create input handler task
    inputTaskId = CreateTask(HandleInput, 3);
    gTasks[inputTaskId].data[0] = menuTaskId;
    gTasks[inputTaskId].data[1] = windowId;
}

static void Debug_DestroyMainMenu(u8 taskId)
{
    DestroyListMenuTask(gTasks[taskId].data[0], NULL, NULL);
    ClearStdWindowAndFrame(gTasks[taskId].data[1], TRUE);
    RemoveWindow(gTasks[taskId].data[1]);
    DestroyTask(taskId);
}

static void DebugTask_HandleMainMenuInput(u8 taskId)
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
        Debug_DestroyMainMenu(taskId);
        EnableBothScriptContexts();
    }
}

static void DebugTask_HandleSub1MenuInput(u8 taskId)
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
        Debug_DestroyMainMenu(taskId);
        EnableBothScriptContexts();
    }
}

static void DebugAction_Cancel(u8 taskId)
{
    Debug_DestroyMainMenu(taskId);
    EnableBothScriptContexts();
}

static void DebugAction_OpenSub1(u8 taskId)
{
    Debug_DestroyMainMenu(taskId);
    Debug_ShowMenu(DebugTask_HandleSub1MenuInput, sDebugMenuWindowTemplate, sDebugMenu_Sub1_ListTemplate);
}

static void DebugAction_PlayBoo(u8 taskId)
{
    PlayBGM(MUS_BATTLE33);
}
