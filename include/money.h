#ifndef GUARD_MONEY_H
#define GUARD_MONEY_H

u32 GetMoney(u32 *moneyPtr);
void SetMoney(u32 *moneyPtr, u32 newValue);
bool8 IsEnoughMoney(u32 *moneyPtr, u32 cost);
void AddMoney(u32 *moneyPtr, u32 toAdd);
void RemoveMoney(u32 *moneyPtr, u32 toSub);
bool8 IsEnoughForCostInVar0x8005(void);
void SubtractMoneyFromVar0x8005(void);
void PrintMoneyAmountInMoneyBox(u8 windowId, s32 amount, u8 speed);
void PrintMoneyAmount(u8 windowId, u8 x, u8 y, s32 amount, u8 speed);
void PrintMoneyAmountInMoneyBoxWithBorder(u8 windowId, u16 tileStart, u8 pallete, s32 amount);
void ChangeAmountInMoneyBox(s32 amount);
void DrawMoneyBox(s32 amount, u8 x, u8 y);
void HideMoneyBox(void);
void AddMoneyLabelObject(u16 x, u16 y);
void RemoveMoneyLabelObject(void);

#endif // GUARD_MONEY_H
