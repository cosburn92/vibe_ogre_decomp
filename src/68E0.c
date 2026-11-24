#include "common.h"
#include "heap.h"
#include "scene.h"
extern u16 D_800C49D0;
/* A window object list (040E80 overlay) and the window it holds */
typedef struct {
    /* 0x00 */ u8 unk00[0x26];
    /* 0x26 */ u16 flags;
    /* 0x28 */ u8 unk28[4];
    /* 0x2C */ s32 x;
    /* 0x30 */ s32 y;
    /* 0x34 */ s32 x2;
    /* 0x38 */ s32 y2;
} SceneWin;
typedef struct {
    /* 0x00 */ void *unk00;
    /* 0x04 */ SceneWin *win;
} SceneWinList;
/* Scene.flags seen as bitfields: the original tests two of its bits together with one word load */
typedef struct {
    u32 unk_hi : 3; /* 0x8000 in use, 0x4000, 0x2000 started */
    u32 f1000 : 1;
    u32 f0800 : 1;
    u32 unk_lo : 27;
} SceneBits;
extern SceneWinList *D_800AF0B0;
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





#define SCENE_PARENT(i) (D_800E82C8[i].parent)
extern s32 D_800C4C20;
extern volatile u16 D_800C4C26;
extern u8 D_800E7A32;
void func_80077F88(s32 i);
typedef struct {
    u32 w0;
    u32 w1;
} Gfx;
extern Gfx *D_800E9BA0;
extern Scene D_800E7A30; /* the scene being run, copied out of its slot */
extern u8 D_800E91D0[];
extern u32 D_801869C8[];
void func_80173D84(void *list);
void func_80173DBC(u8 kind, s16 x, s16 y, s16 x2, s16 y2);
void func_800780D4(u8 kind, void *src, u16 n, u8 **out);
void func_80078164(u8 *p, void *dst);
void func_800782EC(s32 color, s32 shade, s32 x, s32 y, s32 x2, s32 y2);
void func_80077288(void);
void func_80077494(s32 arg0);
s32 func_8009C7CC(void);
void func_80173D14(void *list);
void func_80173D4C(void *list);
u8 *func_8017C29C(u8 *p, s16 x, s16 y, s16 z, s16 w);
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

/* Scene update. First pass, round robin from slot 0 until a full lap starts nothing new: scenes
 * not yet started (flag 0x2000 clear) run their init callback with a fresh window list in unk98;
 * a list that got a window keeps its own copy (flags3 bit 2), the shared one is replaced.
 * Second pass: started scenes run their update callback; a windowed scene keeps its rect on the
 * window (inset by 6) and is closed (flags2 bit 2) once the window is gone. */
void func_800765D8(void) {
    s32 i;
    s32 last;

    last = 0;
    i = 0;
    do {
        D_800C4C20 = i;
        if (!(D_800E82C8[i].flags & 0x2000) && (D_800E82C8[i].flags & 0x8000) && D_800E82C8[i].owner != NULL) {
            _bcopy(&D_800E82C8[i], &D_800E7A30, 0xA8);
            if (i == ((u16 *)D_800C4C10)[0]) {
                D_800E7A30.flags2 |= 4;
            }
            D_800E7A30.unk04[0] = 6;
            D_800E7A30.unk98 = D_800AF0B0;
            ((void (*)(s32))D_800E7A30.owner)(i);
            if (((SceneWinList *)D_800E7A30.unk98)->win != NULL) {
                D_800E7A30.unk98 = func_80173B60(D_800E7A30.unk98);
                ((SceneWinList *)D_800E7A30.unk98)->win = D_800AF0B0->win;
                D_800AF0B0->win = NULL;
                D_800E7A30.flags3 |= 2;
            } else {
                D_800E7A30.unk98 = NULL;
            }
            D_800E7A30.flags |= 0x2000;
            if (i == ((u16 *)D_800C4C10)[0]) {
                D_800E7A30.flags2 &= ~4;
            }
            func_800780D4(D_800E7A30.flags, D_800E91D0, D_800E7A30.size, &D_800E7A30.data);
            _bcopy(&D_800E7A30, &D_800E82C8[i], 0xA8);
            if (D_800E82C8[i].flags2 & 2) {
                func_80077F88(i);
            }
            last = i;
        }
        i++;
        i %= 6;
    } while (i != last);
    func_8007819C();

    for (i = 0; i < 6; i++) {
        D_800C4C20 = i;
        if (!(D_800E82C8[i].flags & 0x2000) || !(D_800E82C8[i].flags & 0x8000) || D_800E82C8[i].update == NULL) {
            continue;
        }
        _bcopy(&D_800E82C8[i], &D_800E7A30, 0xA8);
        if (i == ((u16 *)D_800C4C10)[0]) {
            D_800E7A30.flags2 |= 4;
        }
        func_80078164(D_800E7A30.data, D_800E91D0);
        func_80077494(i);
        D_800E7A30.update(i);
        if (D_800E7A30.flags3 & 2) {
            if (!((SceneBits *)&D_800E7A30)->f1000 && !((SceneBits *)&D_800E7A30)->f0800) {
                func_8017C29C((u8 *)((SceneWinList *)D_800E7A30.unk98)->win, D_800E7A30.x - 6, D_800E7A30.y - 6,
                              D_800E7A30.x2 + 6, D_800E7A30.y2 + 6);
            }
            func_80173D14(D_800E7A30.unk98);
            func_80173D4C(D_800E7A30.unk98);
            if (((SceneWinList *)D_800E7A30.unk98)->win == NULL) {
                D_800E7A30.flags2 |= 2;
            } else if (((SceneWinList *)D_800E7A30.unk98)->win->flags == 0) {
                if (D_800E7A30.flags & 0x800) {
                    D_800E7A30.flags &= ~0x800;
                }
            } else {
                D_800E7A30.x = ((SceneWinList *)D_800E7A30.unk98)->win->x + 6;
                D_800E7A30.x2 = ((SceneWinList *)D_800E7A30.unk98)->win->x2 - 6;
                if (D_800E7A30.x2 < D_800E7A30.x) {
                    D_800E7A30.x = D_800E7A30.x2;
                }
                D_800E7A30.y = ((SceneWinList *)D_800E7A30.unk98)->win->y + 6;
                D_800E7A30.y2 = ((SceneWinList *)D_800E7A30.unk98)->win->y2 - 6;
                if (D_800E7A30.y2 < D_800E7A30.y) {
                    D_800E7A30.y = D_800E7A30.y2;
                }
            }
        }
        if (i == ((u16 *)D_800C4C10)[0]) {
            D_800E7A30.flags2 &= ~4;
        }
        func_800780D4(D_800E7A30.flags, D_800E91D0, D_800E7A30.size, &D_800E7A30.data);
        _bcopy(&D_800E7A30, &D_800E82C8[i], 0xA8);
        if (D_800E82C8[i].flags2 & 2) {
            func_80077F88(i);
        }
        func_8009C7CC();
        if (--D_800C49D0 == 0) {
            break;
        }
    }
    func_8007819C();
    D_800C4C20 = -1;
    func_80077288();
}

/* Draws the active scenes back to front: each one is copied into D_800E7A30 with its saved
 * D_800E91D0 state, gets an optional backdrop, runs its draw callback, then is saved back.
 * The front scene (index 0) is marked with flags2 bit 4 and gets the bright frame. */
void func_80076AE8(void) {
    s32 i;
    s32 s;

    for (i = D_800C49D0 - 1; i >= 0; i--) {
        s = ((u16 *)D_800C4C10)[i];
        D_800C4C20 = s;
        if (!(D_800E82C8[s].flags & 0x2000) && D_800E82C8[s].draw == NULL) {
            continue;
        }
        _bcopy(&D_800E82C8[s], &D_800E7A30, 0xA8);
        if (i == 0) {
            D_800E7A30.flags2 |= 4;
        }
        func_80078164(D_800E7A30.data, D_800E91D0);
        if (D_800E7A30.flags3 & 2) {
            Gfx *g = D_800E9BA0;

            g->w0 = 0xDE000000;
            g->w1 = (u32)D_801869C8;
            D_800E9BA0 = g + 1;
            func_80173D84(D_800E7A30.unk98);
        } else if (!(D_800E7A30.flags2 & 1) && D_800E7A30.unkA0 != 0) {
            Gfx *g = D_800E9BA0;

            g->w0 = 0xDE000000;
            g->w1 = (u32)D_801869C8;
            D_800E9BA0 = g + 1;
            func_80173DBC(D_800E7A30.unkA0, D_800E7A30.x, D_800E7A30.y, D_800E7A30.x2, D_800E7A30.y2);
        }
        {
            Gfx *g = D_800E9BA0;

            g->w0 = 0xDE000000;
            g->w1 = (u32)D_801869C8;
            D_800E9BA0 = g + 1;
        }
        D_800E7A30.draw(s);
        {
            Gfx *g = D_800E9BA0;

            g->w0 = 0xE7000000;
            g->w1 = 0;
            D_800E9BA0 = g + 1;
        }
        if (!(D_800E7A30.flags2 & 1) && D_800E7A30.unkA0 == 0) {
            if (i == 0) {
                func_800782EC(0xFFFF, 0x18C1, D_800E7A30.x, D_800E7A30.y, D_800E7A30.x2, D_800E7A30.y2);
            } else {
                func_800782EC(0x4211, 0x843, D_800E7A30.x, D_800E7A30.y, D_800E7A30.x2, D_800E7A30.y2);
            }
        }
        if (i == 0) {
            D_800E7A30.flags2 &= ~4;
        }
        func_800780D4(D_800E7A30.flags, D_800E91D0, D_800E7A30.size, &D_800E7A30.data);
        _bcopy(&D_800E7A30, &D_800E82C8[s], 0xA8);
    }
    D_800C4C20 = -1;
}

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

/* Opening animation: scenes with flags 0xE800 set grow from (x, y) to their full size (unk28 x
 * unk2A) over unk04[0] frames in 8.8 fixed point. flags2 bits 0xC0 pick the horizontal direction
 * (0 or 0x40 grows x2 right, 0x80 grows x left) and bits 0x30 the vertical one (0 or 0x20 grows y2
 * down, 0x10 grows y up); a window pushed past the 320x240 screen slides back. unk2C carries the
 * fractions (read x from the low byte, y from the high byte, but written back the other way round).
 * Once both axes reach full size, flags 0x800 and 0x400 are cleared. */
#ifdef NON_MATCHING
/* same size; loads are scheduled differently (retail reloads unk28/x after the x2 store and keeps mode in a3) and the scene offset lands in a1 instead of a2 */
void func_800775EC(void) {
    s32 fx;
    s32 fy;
    s32 i;
    s32 s;
    u8 mode;
    s32 step;
    s32 grow;
    u8 done;

    fx = 0;
    fy = 0;
    for (i = 0; i < D_800C49D0; i++) {
        s = ((u16 *)D_800C4C10)[i];
        if ((D_800E82C8[s].flags & 0xE800) != 0xE800) {
            continue;
        }
        if (D_800E82C8[s].flags3 & 2) {
            continue;
        }
        done = 0;
        if (!(D_800E82C8[s].flags & 0x400)) {
            D_800E82C8[s].unk2C = 0;
            D_800E82C8[s].flags |= 0x400;
        }

        step = D_800E82C8[s].unk28 << 8;
        mode = D_800E82C8[s].flags2 & 0xC0;
        grow = mode == 0 || mode == 0x40;
        step /= D_800E82C8[s].unk04[0];
        if (grow) {
            fx = ((D_800E82C8[s].x2 << 8) | (D_800E82C8[s].unk2C & 0xFF)) + step;
            D_800E82C8[s].x2 = fx >> 8;
            if (D_800E82C8[s].x2 >= D_800E82C8[s].x + D_800E82C8[s].unk28 - 1) {
                D_800E82C8[s].x2 = D_800E82C8[s].x + D_800E82C8[s].unk28 - 1;
                done |= 1;
            }
            if (D_800E82C8[s].x2 >= 320) {
                D_800E82C8[s].x = D_800E82C8[s].x + 319 - D_800E82C8[s].x2;
                D_800E82C8[s].x2 = 319;
                if (D_800E82C8[s].x < 0) {
                    D_800E82C8[s].x = 0;
                    done |= 1;
                }
            }
        } else if (mode == 0x40 || mode == 0x80) {
            fx = ((D_800E82C8[s].x << 8) | (D_800E82C8[s].unk2C & 0xFF)) - step;
            D_800E82C8[s].x = fx >> 8;
            if (D_800E82C8[s].x <= D_800E82C8[s].x2 - D_800E82C8[s].unk28 + 1) {
                D_800E82C8[s].x = D_800E82C8[s].x2 - D_800E82C8[s].unk28 + 1;
                done |= 1;
            }
            if (D_800E82C8[s].x < 0) {
                D_800E82C8[s].x2 = D_800E82C8[s].x2 - D_800E82C8[s].x;
                D_800E82C8[s].x = 0;
                if (D_800E82C8[s].x2 >= 320) {
                    D_800E82C8[s].x2 = 319;
                    done |= 1;
                }
            }
        }

        step = D_800E82C8[s].unk2A << 8;
        mode = D_800E82C8[s].flags2 & 0x30;
        grow = mode == 0 || mode == 0x20;
        step /= D_800E82C8[s].unk04[0];
        if (grow) {
            fy = ((D_800E82C8[s].y2 << 8) | (D_800E82C8[s].unk2C >> 8)) + step;
            D_800E82C8[s].y2 = fy >> 8;
            if (D_800E82C8[s].y2 >= D_800E82C8[s].y + D_800E82C8[s].unk2A - 1) {
                D_800E82C8[s].y2 = D_800E82C8[s].y + D_800E82C8[s].unk2A - 1;
                done |= 2;
            }
            if (D_800E82C8[s].y2 >= 240) {
                D_800E82C8[s].y = D_800E82C8[s].y + 239 - D_800E82C8[s].y2;
                D_800E82C8[s].y2 = 239;
                if (D_800E82C8[s].y < 0) {
                    D_800E82C8[s].y = 0;
                    done |= 2;
                }
            }
        } else if (mode == 0x20 || mode == 0x10) {
            fy = ((D_800E82C8[s].y << 8) | (D_800E82C8[s].unk2C >> 8)) - step;
            D_800E82C8[s].y = fy >> 8;
            if (D_800E82C8[s].y <= D_800E82C8[s].y2 - D_800E82C8[s].unk2A + 1) {
                D_800E82C8[s].y = D_800E82C8[s].y2 - D_800E82C8[s].unk2A + 1;
                done |= 2;
            }
            if (D_800E82C8[s].y < 0) {
                D_800E82C8[s].y2 = D_800E82C8[s].y2 - D_800E82C8[s].y;
                D_800E82C8[s].y = 0;
                if (D_800E82C8[s].y2 >= 240) {
                    D_800E82C8[s].y2 = 239;
                    done |= 2;
                }
            }
        }

        D_800E82C8[s].unk2C = (fy & 0xFF) | ((fx & 0xFF) << 8);
        if (done == 3) {
            D_800E82C8[s].flags &= ~0xC00;
        }
    }
}
#else
INCLUDE_ASM("asm/nonmatchings/68E0", func_800775EC);
#endif

/* Closing animation: scenes with all of flags 0xF000 set shrink their far corner (x2, y2) towards
 * (x, y) over unk04[0] frames in 8.8 fixed point, and are freed once they reach the minimum size.
 * The step's whole parts go in unk28/unk2A and both fractions in unk2C; unk2E holds the corner's
 * fractions (x in the low byte, y in the high byte). */
void func_80077BF8(void) {
    s32 i;
    s32 s;
    s32 dx;
    s32 dy;

    for (i = 0; i < D_800C49D0; i++) {
        s = ((u16 *)D_800C4C10)[i];
        if ((D_800E82C8[s].flags & 0xF000) != 0xF000) {
            continue;
        }
        if (D_800E82C8[s].flags3 & 2) {
            continue;
        }
        if (D_800E82C8[s].x2 == D_800E82C8[s].x + D_800E79A0 - 1
            && D_800E82C8[s].y2 == D_800E82C8[s].y + D_800E79A0 - 1) {
            func_80077F88(s);
            continue;
        }
        if (!(D_800E82C8[s].flags & 0x400)) {
            dx = ((D_800E82C8[s].x2 - D_800E82C8[s].x + 1) << 8) / D_800E82C8[s].unk04[0];
            dy = ((D_800E82C8[s].y2 - D_800E82C8[s].y + 1) << 8) / D_800E82C8[s].unk04[0];
            D_800E82C8[s].unk2E = 0;
            D_800E82C8[s].flags |= 0x400;
            D_800E82C8[s].unk28 = dx >> 8;
            D_800E82C8[s].unk2A = dy >> 8;
            D_800E82C8[s].unk2C = ((u8)dy << 8) | (u8)dx;
        }
        dx = (D_800E82C8[s].unk28 << 8) | (D_800E82C8[s].unk2C & 0xFF);
        dy = (D_800E82C8[s].unk2A << 8) | (D_800E82C8[s].unk2C >> 8);
        {
            s32 nx = ((D_800E82C8[s].x2 << 8) | (D_800E82C8[s].unk2E & 0xFF)) - dx;
            s32 ny = ((D_800E82C8[s].y2 << 8) | (D_800E82C8[s].unk2E >> 8)) - dy;

            D_800E82C8[s].x2 = nx >> 8;
            D_800E82C8[s].y2 = ny >> 8;
            D_800E82C8[s].unk2E = (nx & 0xFF) | ((ny & 0xFF) << 8);
        }
        if (D_800E82C8[s].x2 < D_800E82C8[s].x + D_800E79A0 - 1) {
            D_800E82C8[s].x2 = D_800E82C8[s].x + D_800E79A0 - 1;
        }
        if (D_800E82C8[s].y2 < D_800E82C8[s].y + D_800E79A0 - 1) {
            D_800E82C8[s].y2 = D_800E82C8[s].y + D_800E79A0 - 1;
        }
    }
}

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
    if (D_800E82C8[i].exit != NULL) {
        D_800E82C8[i].exit(i);
    }
    {
        void **p = D_800E82C8[i].slotsA;

        for (j = 0; j < 10; j++, p++) {
            if (*p != NULL) {
                HFree(*p);
            }
        }
    }
    HFree(D_800E82C8[i].data);
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

void func_800782EC(s32 color, s32 shade, s32 x, s32 y, s32 x2, s32 y2) {
}

INCLUDE_RODATA("asm/nonmatchings/68E0", D_800ADF88);
