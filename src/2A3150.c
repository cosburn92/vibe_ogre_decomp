#include "common.h"

/* 2A3150 */

u8 *func_80232E44_ovl_29A4C0(s32 a, s32 b);
/* --- end decls --- */

inline u8 *func_80233920_ovl_29A4C0(s32 a, s32 i, s32 b) {
    u8 *p = func_80232E44_ovl_29A4C0(a, b);

    if (p != NULL) {
        return (u8 *)(((s32 *)p)[i] + (s32)p);
    }
    return NULL;
}

extern u8 D_801CEEE0[];

/* Command lookup (as 1F0A30's func_801C1C1C) in the battle overlay's copy of the resource */
u8 func_80233968_ovl_29A4C0(s32 key, s32 layout, u32 k, s32 x, u8 *p0, u8 *p1, u8 *p2) {
    u8 *s = func_80233920_ovl_29A4C0(key, layout, x);
    u32 n = *s++;
    u32 i;

    for (i = 0; i < n; i++) {
        if (i == k) {
            switch (D_801CEEE0[s[0]]) {
            case 2:
                if (p0 != NULL) {
                    *p0 = s[1];
                }
                break;
            case 3:
                if (p0 != NULL) {
                    *p0 = s[1];
                }
                if (p1 != NULL) {
                    *p1 = s[2];
                }
                break;
            case 4:
                if (p0 != NULL) {
                    *p0 = s[1];
                }
                if (p1 != NULL) {
                    *p1 = s[2];
                }
                if (p2 != NULL) {
                    *p2 = s[3];
                }
                break;
            }
            return s[0];
        }
        s += D_801CEEE0[s[0]];
    }
    return 0;
}
