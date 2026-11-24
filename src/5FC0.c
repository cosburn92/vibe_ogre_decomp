#include "common.h"
#include "chunk.h"

/* Scene manager: the main scene-stack loop and the overlay loader */

typedef struct SceneEntry {
    /* 0x00 */ struct SceneEntry *prev;
    /* 0x04 */ u16 scene;
} SceneEntry; /* size 0x8 */

typedef struct {
    /* 0x00 */ void (*init)(void);
    /* 0x04 */ s32 unk4;
    /* 0x08 */ s32 unk8;
    /* 0x0C */ void (*exit)(void);
    /* 0x10 */ s32 ovlMask; /* overlays to load; bit 31/30 select the graphics heap size */
} SceneDesc;

typedef SceneDesc *(*SceneFunc)(void);

typedef struct {
    /* 0x00 */ u32 vramStart;
    /* 0x04 */ u32 vramEnd;
    /* 0x08 */ u32 romStart;
    /* 0x0C */ u32 romEnd;
    /* 0x10 */ u32 bssStart;
    /* 0x14 */ u32 bssEnd;
    /* 0x18 */ u32 textStart;
    /* 0x1C */ u32 textEnd;
    /* 0x20 */ u32 dataStart;
    /* 0x24 */ u32 dataEnd;
} Overlay; /* size 0x28 */

#define SCENE_NONE 0xFFFF
#define SCENE_WAIT 0xFFFD
#define SCENE_QUIT 0xFFFC
#define SCENE_POP 0xFFFE
#define SCENE_REPLACE 0x8000

extern Overlay D_800A83C0[];
extern u8 *D_800A86FC[]; /* overlay sets, each a list of overlay indices ending in 0xFF */
extern SceneDesc D_800A872C;
extern u8 D_800A81FC;
extern SceneEntry D_800AEFE0[];
extern u8 D_800AF020; /* scene stack depth */
extern SceneFunc D_800AF028[];
extern u8 D_800C4808;
extern SceneEntry *D_800C4BBC; /* top of the scene stack */
extern volatile u16 D_800C4C26; /* next scene request */
extern u8 D_800C4CE4;
extern u8 D_800CF970[];
extern u8 D_800D7970[];
extern u8 D_800E810C;
extern u16 D_800E810E;  /* current scene */
extern u16 D_800E8214;  /* boot scene */
extern SceneDesc *D_800E8294;
extern u8 D_8018F481;
extern u8 D_8018F5A3[];
extern u8 D_80243DB0[]; /* end of the overlay/heap region */

SceneDesc *func_80076188(void);
SceneDesc *D_801776C0(void);
SceneDesc *D_8017846C(void);
SceneDesc *D_801736E0(void);
SceneDesc *D_801779F8(void);
SceneDesc *D_8017B5B0(void);
SceneDesc *D_8017B5BC(void);
SceneDesc *D_8017B5E0(void);
SceneDesc *D_801784BC(void);
SceneDesc *D_80177D74(void);
SceneDesc *D_80177E4C(void);
SceneDesc *D_80173830(void);
SceneDesc *D_80177B78(void);
SceneDesc *D_80178460(void);
SceneDesc *D_80177728(void);
SceneDesc *D_80173920(void);
SceneDesc *D_80177ED8(void);
SceneDesc *D_80177F54(void);
SceneDesc *D_80178054(void);
SceneDesc *D_80178060(void);
SceneDesc *D_80178104(void);
SceneDesc *D_801776F4(void);
SceneDesc *D_801782B8(void);
SceneDesc *D_801862D0(void);
SceneDesc *D_8017BA34(void);

void bzero(void *p, s32 n);
void osInvalICache(void *p, s32 n);
void osInvalDCache(void *p, s32 n);
void osViSetSpecialFeatures(u32 func);
void nuGfxTaskAllEndWait(void);
s32 AddHeap(u32 start, u32 size);
void func_80070F14(void);
void func_80072398(void);
u8 func_80072944(void);
void func_80073164(u8 relative, s16 a, s16 b, s16 c, s16 d, s16 e, s16 f);
void func_80073398(void);
void func_80089990(void *func);
void func_80089A30(s32 a);
void func_80089BC0(void);
void func_80089C50(void);
void func_8008AF60(s32 size);
u8 func_80076150(s32 scene);
void func_800761E4(u32 mask);
void func_80076324(u32 mask);
s32 func_80076430(u32 mask);

void func_80075BC0(void) {
    SceneEntry *prev;
    u16 scene;

    D_800AF028[0] = func_80076188;
    D_800AF028[1] = D_801776C0;
    D_800AF028[2] = D_8017846C;
    D_800AF028[3] = D_801736E0;
    D_800AF028[4] = D_801779F8;
    D_800AF028[5] = D_8017B5B0;
    D_800AF028[6] = D_8017B5BC;
    D_800AF028[7] = D_8017B5E0;
    D_800AF028[8] = D_801784BC;
    D_800AF028[9] = D_80177D74;
    D_800AF028[10] = D_80177E4C;
    D_800AF028[11] = D_80173830;
    D_800AF028[12] = D_80177B78;
    D_800AF028[13] = D_80178460;
    D_800AF028[14] = D_80177728;
    D_800AF028[15] = D_80173920;
    D_800AF028[16] = D_80177ED8;
    D_800AF028[17] = D_80177F54;
    D_800AF028[18] = D_80178054;
    D_800AF028[19] = D_80178060;
    D_800AF028[20] = D_80178104;
    D_800AF028[21] = D_801776F4;
    D_800AF028[22] = D_801782B8;
    D_800AF028[23] = D_801862D0;
    D_800AF028[24] = D_8017BA34;

    prev = D_800AEFE0;
    D_800AF020 = 1;
    D_800C4BBC = prev;
    bzero(prev, sizeof(SceneEntry));
    D_800C4BBC->scene = D_800E8214;

    while (1) {
        if (D_800C4BBC->scene == D_800E8214) {
            D_800AF020 = 1;
            D_800C4BBC = D_800AEFE0;
            bzero(D_800AEFE0, sizeof(SceneEntry));
            D_800C4BBC->scene = D_800E8214;
        }
        nuGfxTaskAllEndWait();
        osViSetSpecialFeatures(0x5A);

        scene = D_800C4BBC->scene;
        if (scene >= 31) {
            scene = 0;
        }
        D_800E810E = scene;
        D_800E8294 = D_800AF028[scene]();
        D_800A81FC = func_80076150(D_800E810E);
        func_800761E4(D_800E8294->ovlMask);
        func_80076324(D_800E8294->ovlMask);

        if (D_800E8294->ovlMask < 0 ||
            (D_800E810E == 3 && D_8018F5A3[D_8018F481 * 9] >= 0x2A && D_8018F5A3[D_8018F481 * 9] < 0x2D)) {
            func_8008AF60(0x10000);
            AddHeap((u32)D_800D7970, 0x10000);
        } else if (D_800E8294->ovlMask & 0x40000000) {
            func_8008AF60(0x8000);
            AddHeap((u32)D_800CF970, 0x18000);
        } else {
            func_8008AF60(0x20000);
        }

        D_800C4808 = 0;
        D_800C4C26 = SCENE_NONE;
        if (D_800E8294->init != NULL) {
            D_800E8294->init();
        }
        if (func_80072944()) {
            return;
        }
        if (D_800C4C26 == SCENE_NONE || D_800C4C26 == SCENE_WAIT) {
            D_800E810C = 0;
            D_800C4CE4 = 1;
            func_80089990(func_80072398);
            func_80089C50();
            while (D_800C4C26 == SCENE_NONE || D_800C4C26 == SCENE_WAIT) {}
            func_80089BC0();
            func_80089990(NULL);
        }
        nuGfxTaskAllEndWait();
        func_80089BC0();
        func_80089A30(1);
        if ((u16)D_800C4C26 == SCENE_QUIT) {
            return;
        }
        if (D_800E8294->exit != NULL) {
            D_800E8294->exit();
        }
        func_80073398();
        func_80070F14();

        if ((u16)D_800C4C26 == SCENE_POP) {
            if (D_800C4BBC->prev != NULL) {
                D_800C4C26 = D_800C4BBC->scene;
                D_800C4BBC = D_800C4BBC->prev;
                D_800AF020--;
            } else {
                D_800C4BBC->scene = 0;
            }
        } else if (D_800C4C26 & SCENE_REPLACE) {
            D_800C4C26 &= ~SCENE_REPLACE;
            D_800C4BBC->scene = D_800C4C26;
        } else {
            prev = D_800C4BBC;
            D_800C4BBC = &D_800AEFE0[D_800AF020++];
            bzero(D_800C4BBC, sizeof(SceneEntry));
            D_800C4BBC->prev = prev;
            D_800C4BBC->scene = D_800C4C26;
        }
    }
}

u8 func_80076150(s32 scene) {
    switch (scene) {
        case 3:
        case 4:
        case 5:
        case 6:
        case 7:
        case 10:
        case 11:
        case 15:
        case 18:
        case 23:
            return 0;
        default:
            return 1;
    }
}

SceneDesc *func_80076188(void) {
    return &D_800A872C;
}

void func_80076194(void) {
    D_800C4C26 = SCENE_POP;
}

void func_800761A4(void) {
    func_80073164(0, 1, 1, 0x80, 1, 0x100, 0x2000);
}

/* Loads every overlay in the set selected by mask */
void func_800761E4(u32 mask) {
    u8 idx = func_80076430(mask);
    u8 i;
    u8 ovl;

    for (i = 0; D_800A86FC[idx][i] != 0xFF; i++) {
        ovl = D_800A86FC[idx][i];
        if (mask & (1 << ovl)) {
            osInvalICache((void *)D_800A83C0[ovl].textStart, D_800A83C0[ovl].textEnd - D_800A83C0[ovl].textStart);
            osInvalDCache((void *)D_800A83C0[ovl].dataStart, D_800A83C0[ovl].dataEnd - D_800A83C0[ovl].dataStart);
            RomRead((void *)D_800A83C0[ovl].romStart, (void *)D_800A83C0[ovl].vramStart,
                    D_800A83C0[ovl].romEnd - D_800A83C0[ovl].romStart);
            bzero((void *)D_800A83C0[ovl].bssStart, D_800A83C0[ovl].bssEnd - D_800A83C0[ovl].bssStart);
        }
    }
}

/* Gives the memory around the loaded overlays to the heap */
void func_80076324(u32 mask) {
    u8 idx = func_80076430(mask);
    u32 start = D_800A83C0[0].vramStart;
    u8 i;
    u8 ovl;

    for (i = 0; (ovl = D_800A86FC[idx][i]) != 0xFF; i++) {
        if (mask & (1 << ovl)) {
            if (start < D_800A83C0[ovl].vramStart) {
                AddHeap(start, D_800A83C0[ovl].vramStart - start);
            }
            start = D_800A83C0[ovl].vramEnd;
        }
    }
    if (start < (u32)D_80243DB0) {
        AddHeap(start, (u32)D_80243DB0 - start);
    }
}

/* Index of the first overlay set that contains every overlay in mask */
s32 func_80076430(u32 mask) {
    s32 i;
    s32 j;
    u32 bits;

    mask &= 0x3FFFFFFF;
    for (i = 0; D_800A86FC[i] != NULL; i++) {
        j = 0;
        bits = 0;
        for (; D_800A86FC[i][j] != 0xFF; j++) {
            bits |= 1 << D_800A86FC[i][j];
        }
        if (!(mask & ~bits)) {
            return i;
        }
    }
    return 0;
}
