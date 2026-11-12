#include "common.h"
#include "scene.h"
extern u16 D_800C49D0;
extern void *D_800AF0B0;
extern void *D_800E7A68[];
extern void *D_800E7A90[];
extern char D_800ADF88[];
void func_800775EC(void);
void func_80077BF8(void);
void func_8007819C(void);
void func_80173BA0(void *p);
void *func_80173B60(void *p);
void osSyncPrintf(const char *fmt, ...);
void _bcopy(const void *src, void *dst, s32 n);
void HFree(void *p);





INCLUDE_ASM("asm/nonmatchings/68E0", func_800764E0);

INCLUDE_ASM("asm/nonmatchings/68E0", func_800765D8);

INCLUDE_ASM("asm/nonmatchings/68E0", func_80076AE8);

void func_80076DC8(void) {
    if (D_800C49D0) {
        func_800775EC();
        func_80077BF8();
        func_8007819C();
    }
}

void func_80076E00(void) {
    func_80173BA0(D_800AF0B0);
    D_800AF0B0 = NULL;
}

void func_80076E2C(void) {
    D_800AF0B0 = func_80173B60(D_800AF0B0);
}

/* First free scene slot; hangs when all six are in use. */
u16 func_80076E58(void) {
    u16 i;

    for (i = 0; i < 6; i++) {
        if (!(D_800E82C8[i].flags & 0x8000)) {
            return i;
        }
    }
    for (;;) {
    }
}

/* Next free scene slot after start; hangs if none. */
u16 func_80076EAC(u16 start) {
    u16 i;

    for (i = start + 1; i < 6; i++) {
        if (!(D_800E82C8[i].flags & 0x8000)) {
            return i;
        }
    }
    for (;;) {
    }
}

/* One past the last used scene slot below 5; hangs if none. */
u16 func_80076F00(void) {
    s16 i;

    for (i = 4; i >= 0; i--) {
        if (D_800E82C8[i].flags & 0x8000) {
            return i + 1;
        }
    }
    for (;;) {
    }
}

INCLUDE_ASM("asm/nonmatchings/68E0", func_80076F5C);

INCLUDE_ASM("asm/nonmatchings/68E0", func_8007705C);

INCLUDE_ASM("asm/nonmatchings/68E0", func_80077160);

INCLUDE_ASM("asm/nonmatchings/68E0", func_80077200);

INCLUDE_ASM("asm/nonmatchings/68E0", func_80077288);

s32 func_80077314(void *owner) {
    s32 i;

    for (i = 0; i < 6; i++) {
        if ((D_800E82C8[i].flags & 0x8000) && D_800E82C8[i].owner == owner) {
            return i;
        }
    }
    return -1;
}

s32 func_80077368(s32 scene) {
    s32 i;

    for (i = 0; i < 10; i++) {
        if (D_800E82C8[scene].slotsA[i] == NULL) {
            return i;
        }
    }
    osSyncPrintf(D_800ADF88);
    for (;;) {
    }
}

s32 func_800773D4(void) {
    s32 i;

    for (i = 0; i < 10; i++) {
        if (D_800E7A68[i] == NULL) {
            return i;
        }
    }
    return -1;
}

s32 func_8007740C(s32 scene) {
    s32 i;

    for (i = 0; i < 10; i++) {
        if (D_800E82C8[scene].slotsB[i] == NULL) {
            return i;
        }
    }
    return -1;
}

s32 func_8007745C(void) {
    s32 i;

    for (i = 0; i < 10; i++) {
        if (D_800E7A90[i] == NULL) {
            return i;
        }
    }
    return -1;
}

INCLUDE_ASM("asm/nonmatchings/68E0", func_80077494);

INCLUDE_ASM("asm/nonmatchings/68E0", func_800775EC);

INCLUDE_ASM("asm/nonmatchings/68E0", func_80077BF8);

void func_80077F80(void) {
}

INCLUDE_ASM("asm/nonmatchings/68E0", func_80077F88);

INCLUDE_ASM("asm/nonmatchings/68E0", func_800780D4);

/* Copies a packet's payload (u16 size at +2, data at +6) to dst and frees the packet. */
void func_80078164(u8 *p, void *dst) {
    if (p != NULL) {
        _bcopy(p + 6, dst, *(u16 *)(p + 2));
        HFree(p);
    }
}

INCLUDE_ASM("asm/nonmatchings/68E0", func_8007819C);

void func_800782EC(void) {
}

INCLUDE_RODATA("asm/nonmatchings/68E0", D_800ADF88);
