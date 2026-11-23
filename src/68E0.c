#include "common.h"
#include "scene.h"
extern u16 D_800C49D0;
extern void *D_800AF0B0;
extern u16 D_800E810E;
extern u8 D_800C4C10[];
extern s32 D_800E79A0;
typedef struct {
    /* 0x0 */ u16 h0;
    /* 0x2 */ u8 b2;
    /* 0x3 */ u8 b3;
    /* 0x4 */ u8 b4;
} Pad0A0;
extern Pad0A0 D_800AF0A0;
extern u8 D_800AF0A2;
extern u8 D_800AF0A3;
extern u8 D_800AF0A4;
extern u16 D_800AF0A6[];
extern Pad0A0 *D_800AF090[];
u64 osGetTime(void);
void func_8009C7C0(u32 seed);
void bzero(void *p, s32 n);
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





#define SCENE_PARENT(i) (D_800E82C8[i].parent)
extern s32 D_800C4C20;
extern u16 D_800C4C26;
extern u8 D_800E7A32;
void func_80077F88(s32 i);
void *HMallocBack(s32 size);
/* --- end decls --- */

/* Scene system init: clears the six scene slots and the input state, seeds the random generator */
void func_800764E0(void) {
    u16 i;

    osGetTime();
    bzero(D_800E82C8, 0x3F0);
    bzero(D_800C4C10, 0xC);
    D_800C4C20 = 1;
    D_800E79A0 = 8;
    D_800C49D0 = 0;
    D_800AF0B0 = NULL;
    D_800AF0A0.h0 = 0;
    D_800AF0A0.b3 = 0;
    D_800AF0A0.b2 = 0;
    D_800AF0A0.b4 = 0;
    for (i = 0; i < 4; i++) {
        D_800AF0A6[i] = 0;
        D_800AF090[i] = &D_800AF0A0;
    }
    func_8009C7C0(osGetTime());
    D_800AF0B0 = func_80173B60(D_800AF0B0);
    func_8007819C();
}

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

static inline u16 SceneFindFree(void) {
    u16 i;

    for (i = 0; i < 6; i++) {
        if (!(D_800E82C8[i].flags & 0x8000)) {
            return i;
        }
    }
    for (;;);
}

static inline u16 SceneFindAfterLast(void) {
    s16 i;

    for (i = 4; i >= 0; i--) {
        if (D_800E82C8[i].flags & 0x8000) {
            return i + 1;
        }
    }
    for (;;);
}

/* Opens a scene in the lowest free slot (hangs when all six are in use) */
u16 func_80076F5C(u16 flags, void *fn, s16 x, s16 y, u16 x2, u16 y2, u16 z) {
    u16 i = SceneFindFree();

    D_800E82C8[i].flags = flags;
    D_800E82C8[i].owner = fn;
    D_800E82C8[i].x = x;
    D_800E82C8[i].y = y;
    D_800E82C8[i].x2 = x2;
    D_800E82C8[i].y2 = y2;
    D_800E82C8[i].unk0E = z;
    D_800E82C8[i].parent = D_800C4C20;
    *(u16 *)D_800E82C8[i].unkA4 = D_800E810E;
    return i;
}

/* Opens a scene in the slot after the highest one in use */
u16 func_8007705C(u16 flags, void *fn, s16 x, s16 y, u16 x2, u16 y2, u16 z) {
    u16 i = SceneFindAfterLast();

    D_800E82C8[i].flags = flags;
    D_800E82C8[i].owner = fn;
    D_800E82C8[i].x = x;
    D_800E82C8[i].y = y;
    D_800E82C8[i].x2 = x2;
    D_800E82C8[i].y2 = y2;
    D_800E82C8[i].unk0E = z;
    D_800E82C8[i].parent = D_800C4C20;
    *(u16 *)D_800E82C8[i].unkA4 = D_800E810E;
    return i;
}

/* Closes every child scene of the current scene (D_800C4C20) */
void func_80077160(void) {
    s32 i;

    if (D_800C4C20 < 0) {
        return;
    }
    for (i = 0; i < 6; i++) {
        if (i == D_800C4C20) {
            continue;
        }
        if (!(D_800E82C8[i].flags & 0x8000)) {
            continue;
        }
        if (SCENE_PARENT(i) != D_800C4C20) {
            continue;
        }
        func_80077F88(i);
    }
    {
        u8 *p = &D_800E7A32;

        *p |= 2;
    }
}

/* Closes every child scene of scene id */
void func_80077200(s32 id) {
    s32 i;

    if (id < 0) {
        return;
    }
    for (i = 0; i < 6; i++) {
        if (i == id) {
            continue;
        }
        if (!(D_800E82C8[i].flags & 0x8000)) {
            continue;
        }
        if (SCENE_PARENT(i) != id) {
            continue;
        }
        func_80077F88(i);
    }
}

#ifdef NON_MATCHING
/* lhu result is re-masked with andi in the original */
void func_80077288(void) {
    s32 i;

    func_80077F80();
    if (D_800C4C26 == 0xFFFF) {
        return;
    }
    for (i = 0; i < 6; i++) {
        if (!(D_800E82C8[i].flags & 0x8000)) {
            continue;
        }
        if (!(D_800E82C8[i].flags3 & 4)) {
            continue;
        }
        func_80077F88(i);
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/68E0", func_80077288);
#endif

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

extern Pad0A0 *D_800C47F0;
extern u16 *D_800C4804;
extern u16 D_800C480A;
extern u16 D_800C49D2;
extern u16 *D_800C4AD4;
extern u16 *D_800C4B24;
extern u16 D_800C4B28;
extern u16 *D_800C4BAC;
extern u16 D_800C4BB0;
extern u16 D_800C4BD0;
extern u16 *D_800C4BDC;
extern Pad0A0 **D_800C4BE0;
extern u16 *D_800C4BE8;
extern u16 *D_800C4C0C;
extern u16 *D_800C4C4C;
extern u16 D_800E797C;
extern u16 D_800E79B0;
extern u16 D_800E79BC;
extern u16 *D_800E7A08;
extern u16 D_800E7A24;
extern u16 *D_800E7D6C;
extern u16 D_800E8100;
extern u16 *D_800E8108;
extern u16 D_800E8700;
extern u16 *D_800E9BC0;
extern u16 D_800E9BE4;

/* Points the shared state pointers at the live copies when arg0 is the current id
 * (D_800C4C10), otherwise at the default buffers */
void func_80077494(s32 arg0) {
    if (arg0 == *(u16 *)D_800C4C10) {
        D_800C4BE0 = &D_800C47F0;
        D_800E8108 = &D_800E79B0;
        D_800C4BDC = &D_800E8100;
        D_800C4804 = &D_800C4BD0;
        D_800C4C0C = &D_800E79BC;
        D_800C4BE8 = &D_800C49D2;
        D_800C4AD4 = &D_800E7A24;
        D_800E9BC0 = &D_800E797C;
        D_800E7A08 = &D_800C480A;
        D_800C4BAC = &D_800E9BE4;
        D_800C4B24 = &D_800C4B28;
        D_800E7D6C = &D_800C4BB0;
        D_800C4C4C = &D_800E8700;
    } else {
        D_800C4BE0 = D_800AF090;
        D_800E8108 = D_800AF0A6;
        D_800C4BDC = D_800AF0A6;
        D_800C4804 = D_800AF0A6;
        D_800C4C0C = D_800AF0A6;
        D_800C4BE8 = D_800AF0A6;
        D_800C4AD4 = D_800AF0A6;
        D_800E9BC0 = D_800AF0A6;
        D_800E7A08 = D_800AF0A6;
        D_800C4BAC = D_800AF0A6;
        D_800C4B24 = D_800AF0A6;
        D_800E7D6C = D_800AF0A6;
        D_800C4C4C = D_800AF0A6;
    }
}

INCLUDE_ASM("asm/nonmatchings/68E0", func_800775EC);

INCLUDE_ASM("asm/nonmatchings/68E0", func_80077BF8);

void func_80077F80(void) {
}

/* Closes scene i: first its child scenes (when flag 8 of byte 3 is set), then calls its close
 * hook (0x1C), frees its ten slot buffers and its work buffer (0x24) and clears the record */
#ifdef NON_MATCHING
/* 84/83: GCC keeps &scene[0] + 0x1C in s0 and derives the slot base from it; the original rebuilds the slot base address (a second symbol name gets to 21) */
void func_80077F88(s32 i) {
    s32 j;

    if (D_800E82C8[i].flags3 & 8) {
        if (i >= 0) {
            for (j = 0; j < 6; j++) {
                if (j != i && (D_800E82C8[j].flags & 0x8000) && D_800E82C8[j].parent == i) {
                    func_80077F88(j);
                }
            }
        }
    }
    if (*(void (**)(s32))&D_800E82C8[i].unk14[8] != NULL) {
        (*(void (**)(s32))&D_800E82C8[i].unk14[8])(i);
    }
    {
        void **p = D_800E82C8[i].slotsA;

        for (j = 0; j < 10; j++, p++) {
            if (*p != NULL) {
                HFree(*p);
            }
        }
    }
    HFree(*(void **)&D_800E82C8[i].unk14[0x10]);
    bzero(&D_800E82C8[i], 0xA8);
}
#else
INCLUDE_ASM("asm/nonmatchings/68E0", func_80077F88);
#endif

/* Saves n bytes of src into a new back-heap block: [kind, pad, n, n, data...] */
void func_800780D4(u8 kind, void *src, u16 n, u8 **out) {
    u8 *p;

    if (n == 0) {
        *out = NULL;
        return;
    }
    if (kind & 1) {
        return;
    }
    p = HMallocBack(n + 6);
    *out = p;
    p[0] = kind;
    *(u16 *)(p + 2) = n;
    *(u16 *)(p + 4) = n;
    _bcopy(src, p + 6, n);
}

/* Copies a packet's payload (u16 size at +2, data at +6) to dst and frees the packet. */
void func_80078164(u8 *p, void *dst) {
    if (p != NULL) {
        _bcopy(p + 6, dst, *(u16 *)(p + 2));
        HFree(p);
    }
}

/* Rebuilds the draw order of the active scenes (D_800C4C10, D_800C49D0 entries) sorted by depth
 * (0x0E, deepest first), then renumbers the nonzero depths count + 10 downwards in that order */
#ifdef NON_MATCHING
/* 84/84: the depth counter and the order pointer of the renumbering loop swap a0/a1 */
void func_8007819C(void) {
    s32 pad[1];
    s32 i;
    s32 j;
    s32 z;

    D_800C49D0 = 0;
    for (i = 0; i < 6; i++) {
        if (D_800E82C8[i].flags & 0x8000) {
            for (j = D_800C49D0 - 1; j >= 0; j--) {
                if (D_800E82C8[((u16 *)D_800C4C10)[j]].unk0E >= D_800E82C8[i].unk0E) {
                    break;
                }
                ((u16 *)D_800C4C10)[j + 1] = ((u16 *)D_800C4C10)[j];
            }
            ((u16 *)D_800C4C10)[j + 1] = i;
            D_800C49D0++;
        }
    }
    z = D_800C49D0 + 10;
    for (i = 0; i < D_800C49D0; i++) {
        if (D_800E82C8[((u16 *)D_800C4C10)[i]].unk0E != 0) {
            D_800E82C8[((u16 *)D_800C4C10)[i]].unk0E = z;
            z--;
        }
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/68E0", func_8007819C);
#endif

void func_800782EC(void) {
}

INCLUDE_RODATA("asm/nonmatchings/68E0", D_800ADF88);
