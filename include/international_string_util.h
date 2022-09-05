#ifndef GUARD_INTERNATIONAL_STRING_UTIL_H
#define GUARD_INTERNATIONAL_STRING_UTIL_H

#include "menu.h"
#include "list_menu.h"

void ConvertInternationalPlayerName(u8 *src);
void TVShowConvertInternationalString(u8 *dest, const u8 *src, s32 language);
s32 GetStringCenterAlignXOffset(s32 fontId, const u8 *str, s32 totalWidth);
s32 GetStringRightAlignXOffset(s32 fontId, const u8 *str, s32 totalWidth);
s32 GetStringCenterAlignXOffsetWithLetterSpacing(s32 fontId, const u8 *str, s32 totalWidth, s32 letterSpacing);
s32 GetStringWidthDifference(s32 fontId, const u8 *str, s32 totalWidth, s32 letterSpacing);
s32 GetMaxWidthInMenuTable(const struct MenuAction *actions, s32 numActions);
s32 GetMaxWidthInSubsetOfMenuTable(const struct MenuAction *actions, const u8 *actionIds, s32 numActions);
s32 Intl_GetListMenuWidth(const struct ListMenuTemplate *listMenu);
void CopyMonCategoryText(s32 dexNum, u8 *dest);
u8 *GetStringClearToWidth(u8 *dest, s32 fontId, const u8 *str, s32 totalStringWidth);
void PadNameString(u8 *dest, u8 padChar);
void ConvertInternationalPlayerNameStripChar(u8 *, u8);
void ConvertInternationalContestantName(u8 *);
s32 GetNicknameLanguage(u8 *);
void FillWindowTilesByRow(s32 windowId, s32 columnStart, s32 rowStart, s32 numFillTiles, s32 numRows);

#endif // GUARD_INTERNATIONAL_STRING_UTIL_H
