#include "common.h"

extern u8 D_800A9890;     /* audio task enabled */
extern u8 D_800E7970[];   /* NuSystem client */

void func_80081908(s32 a, s32 b);
void func_80089124(void *c); /* nuScRemoveClient */

void func_80081080(s16 type, s32 arg) {
    if (type != 1) {
        if (type == 2) {
            func_80081908(2, 25);
            func_80081908(1, 25);
        }
    } else if (arg == 0x1C) {
        D_800A9890 = 0;
        func_80089124(D_800E7970);
    }
}
