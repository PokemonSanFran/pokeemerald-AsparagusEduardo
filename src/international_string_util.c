#include "global.h"
#include "international_string_util.h"
#include "list_menu.h"
#include "pokedex.h"
#include "script_menu.h"
#include "string_util.h"
#include "strings.h"
#include "text.h"
#include "window.h"

extern const struct PokedexEntry gPokedexEntries[];

s32 GetStringCenterAlignXOffset(s32 fontId, const u8 *str, s32 totalWidth)
{
    return GetStringCenterAlignXOffsetWithLetterSpacing(fontId, str, totalWidth, 0);
}

s32 GetStringRightAlignXOffset(s32 fontId, const u8 *str, s32 totalWidth)
{
    return GetStringWidthDifference(fontId, str, totalWidth, 0);
}

s32 GetStringCenterAlignXOffsetWithLetterSpacing(s32 fontId, const u8 *str, s32 totalWidth, s32 letterSpacing)
{
    return GetStringWidthDifference(fontId, str, totalWidth, letterSpacing) / 2;
}

s32 GetStringWidthDifference(s32 fontId, const u8 *str, s32 totalWidth, s32 letterSpacing)
{
    s32 stringWidth = GetStringWidth(fontId, str, letterSpacing);
    if (totalWidth > stringWidth)
        return totalWidth - stringWidth;
    else
        return 0;
}

s32 GetMaxWidthInMenuTable(const struct MenuAction *actions, s32 numActions)
{
    s32 i, maxWidth;

    for (maxWidth = 0, i = 0; i < numActions; i++)
    {
        s32 stringWidth = GetStringWidth(FONT_NORMAL, actions[i].text, 0);
        if (stringWidth > maxWidth)
            maxWidth = stringWidth;
    }

    return ConvertPixelWidthToTileWidth(maxWidth);
}

s32 GetMaxWidthInSubsetOfMenuTable(const struct MenuAction *actions, const u8 *actionIds, s32 numActions)
{
    s32 i, maxWidth;

    for (maxWidth = 0, i = 0; i < numActions; i++)
    {
        s32 stringWidth = GetStringWidth(FONT_NORMAL, actions[actionIds[i]].text, 0);
        if (stringWidth > maxWidth)
            maxWidth = stringWidth;
    }

    return ConvertPixelWidthToTileWidth(maxWidth);
}

s32 Intl_GetListMenuWidth(const struct ListMenuTemplate *listMenu)
{
    s32 i, maxWidth, finalWidth;
    const struct ListMenuItem *items = listMenu->items;

    maxWidth = 0;
    for (i = 0; i < listMenu->totalItems; i++)
    {
        s32 width = GetStringWidth(listMenu->fontId, items[i].name, 0);
        if (width > maxWidth)
            maxWidth = width;
    }

    finalWidth = maxWidth + listMenu->item_X + 9;
    if (finalWidth < 0)
        finalWidth += 7;

    finalWidth >>= 3;
    if (finalWidth > 28)
        finalWidth = 28;

    return finalWidth;
}

void CopyMonCategoryText(s32 dexNum, u8 *dest)
{
    u8 *str = StringCopy(dest, gPokedexEntries[dexNum].categoryName);
    *str = CHAR_SPACE;
    StringCopy(str + 1, gText_Pokemon);
}

u8 *GetStringClearToWidth(u8 *dest, s32 fontId, const u8 *str, s32 totalStringWidth)
{
    u8 *buffer;
    s32 width;
    s32 clearWidth;

    if (str)
    {
        buffer = StringCopy(dest, str);
        width = GetStringWidth(fontId, str, 0);
    }
    else
    {
        buffer = dest;
        width = 0;
    }

    clearWidth = totalStringWidth - width;
    if (clearWidth > 0)
    {
        *(buffer++) = EXT_CTRL_CODE_BEGIN;
        *(buffer++) = EXT_CTRL_CODE_CLEAR;
        *(buffer++) = clearWidth;
        *buffer = EOS;
    }

    return buffer;
}

void PadNameString(u8 *dest, u8 padChar)
{
    u8 length;

    StripExtCtrlCodes(dest);
    length = StringLength(dest);
    if (padChar == EXT_CTRL_CODE_BEGIN)
    {
        while (length < PLAYER_NAME_LENGTH - 1)
        {
            dest[length] = EXT_CTRL_CODE_BEGIN;
            dest[length + 1] = EXT_CTRL_CODE_RESET_SIZE;
            length += 2;
        }
    }
    else
    {
        while (length < PLAYER_NAME_LENGTH - 1)
        {
            dest[length] = padChar;
            length++;
        }
    }

    dest[length] = EOS;
}

void ConvertInternationalPlayerName(u8 *str)
{
    if (StringLength(str) < PLAYER_NAME_LENGTH - 1)
        ConvertInternationalString(str, LANGUAGE_JAPANESE);
    else
        StripExtCtrlCodes(str);
}

void ConvertInternationalPlayerNameStripChar(u8 *str, u8 removeChar)
{
    u8 *buffer;
    if (StringLength(str) < PLAYER_NAME_LENGTH - 1)
    {
        ConvertInternationalString(str, LANGUAGE_JAPANESE);
    }
    else if (removeChar == EXT_CTRL_CODE_BEGIN)
    {
        StripExtCtrlCodes(str);
    }
    else
    {
        buffer = str;
        while (buffer[1] != EOS)
            buffer++;

        while (buffer >= str && buffer[0] == removeChar)
        {
            buffer[0] = EOS;
            buffer--;
        }
    }
}

void ConvertInternationalContestantName(u8 *str)
{
    if (*str++ == EXT_CTRL_CODE_BEGIN && *str++ == EXT_CTRL_CODE_JPN)
    {
        while (*str != EOS)
        {
            if (str[0] == EXT_CTRL_CODE_BEGIN && str[1] == EXT_CTRL_CODE_ENG)
                return;

            str++;
        }

        *str++ = EXT_CTRL_CODE_BEGIN;
        *str++ = EXT_CTRL_CODE_ENG;
        *str = EOS;
    }
}

void TVShowConvertInternationalString(u8 *dest, const u8 *src, s32 language)
{
    StringCopy(dest, src);
    ConvertInternationalString(dest, language);
}

// It's impossible to distinguish between Latin languages just from a string alone, so the function defaults to LANGUAGE_ENGLISH. This is the case in all of the versions of the game.
s32 GetNicknameLanguage(u8 *str)
{
    if (str[0] == EXT_CTRL_CODE_BEGIN && str[1] == EXT_CTRL_CODE_JPN)
        return LANGUAGE_JAPANESE;
    else
        return LANGUAGE_ENGLISH;
}

// Used by Pokénav's Match Call to erase the previous trainer's flavor text when switching between their info pages.
void FillWindowTilesByRow(s32 windowId, s32 columnStart, s32 rowStart, s32 numFillTiles, s32 numRows)
{
    u8 *windowTileData;
    s32 fillSize, windowRowSize, i;
    struct Window *window = &gWindows[windowId];

    fillSize = numFillTiles * TILE_SIZE_4BPP;
    windowRowSize = window->window.width * TILE_SIZE_4BPP;
    windowTileData = window->tileData + (rowStart * windowRowSize) + (columnStart * TILE_SIZE_4BPP);
    if (numRows > 0)
    {
        for (i = numRows; i != 0; i--)
        {
            CpuFastFill8(0x11, windowTileData, fillSize);
            windowTileData += windowRowSize;
        }
    }
}
