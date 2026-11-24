#include "common.h"

/* 145210 */

typedef struct {
    s32 key;
    s32 val;
} Pair145;

extern Pair145 D_801FCF40_ovl_145210[];
extern u8 D_801FCE94_ovl_145210[];
extern s32 D_801FCD50_ovl_145210[];
/* --- end decls --- */

s32 func_801F4030_ovl_145210(s32 a, s32 alt) {
    s32 r = -1;
    u32 i;

    if (alt) {
        for (i = 0; i < 5; i++) {
            if (D_801FCF40_ovl_145210[i].key == a) {
                r = D_801FCF40_ovl_145210[i].val;
                break;
            }
        }
    } else {
        r = D_801FCD50_ovl_145210[D_801FCE94_ovl_145210[a]];
    }
    return r;
}

s32 func_801F40A0_ovl_145210(s32 a) {
    return a == 0x87;
}
