#include "common.h"
#include "nusys.h"

/* NuSystem nucontdatagetall.c, nucontqueryread.c, nucontreadfuncset.c */

extern OSContPad D_800C4BF0[4];  /* nuContData */
extern void (*D_800A9FE0)(u32);  /* nuContReadFunc */

void nuContDataClose(void);
void func_8008A37C(void); /* nuContDataOpen */
void _bcopy(const void *src, void *dst, s32 len);
u32 osSetIntMask(u32 mask);

/* nuContDataGetAll */
void func_8008A600(OSContPad *contdata) {
    nuContDataClose();
    _bcopy(D_800C4BF0, contdata, sizeof(OSContPad) * 4);
    func_8008A37C();
}

/* nuContQueryRead */
void func_8008A640(void) {
    func_80089CF8(0x103, NULL); /* NU_CONT_QUERY_MSG */
}

/* nuContReadFuncSet */
void func_8008A660(void (*func)(u32)) {
    u32 mask;

    mask = osSetIntMask(1);
    D_800A9FE0 = func;
    osSetIntMask(mask);
}
