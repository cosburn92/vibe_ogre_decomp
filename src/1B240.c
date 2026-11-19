#include "common.h"

/* NuSystem nucontpakcodeset.c */

extern u16 D_800AA010; /* nuContPakCompanyCode */
extern u32 D_800AA014; /* nuContPakGameCode */

void _bcopy(const void *src, void *dst, s32 len);

/* nuContPakCodeSet */
void func_8008AE40(u8 *companyCode, u8 *gameCode) {
    _bcopy(companyCode, &D_800AA010, 2);
    _bcopy(gameCode, &D_800AA014, 4);
}
