#ifndef GUARD_MATH_UTIL_H
#define GUARD_MATH_UTIL_H

s16 MathUtil_Mul16(s16 x, s16 y);
s16 MathUtil_Mul16Shift(u8 s, s16 x, s16 y);
int MathUtil_Mul32(int x, int y);
s16 MathUtil_Div16(s16 x, s16 y);
s16 MathUtil_Div16Shift(u8 s, s16 x, s16 y);
int MathUtil_Div32(int x, int y);
s16 MathUtil_Inv16(s16 y);
s16 MathUtil_Inv16Shift(u8 s, s16 y);
int MathUtil_Inv32(int y);

#endif // GUARD_MATH_UTIL_H
