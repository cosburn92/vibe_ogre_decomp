#include "common.h"
#include "nusys.h"

/* NuSystem nugfxinit.c */

extern void *D_800A9EE0[];  /* FrameBuf */
extern void *D_800C4B20;    /* nuGfxZBuffer */
extern void *D_800C4CE0;    /* nuGfxUcode */
extern u8 D_800A9EB0[];     /* nugfx_ucode */
extern u8 D_A9EF0[];        /* OS_K0_TO_PHYSICAL(rdpstateinit_dl) */

void func_8008B0B0(void);                       /* nuGfxThreadStart */
void func_80089AB0(void **framebuf, u32 num);   /* nuGfxSetCfb */
void func_800899D0(void *func);                 /* nuGfxSwapCfbFuncSet */
void func_8008B110(void *gfxTask);              /* nuGfxSwapCfb */
void func_80089660(void);                       /* nuGfxTaskMgrInit */
void func_80089804(void *gfxList_ptr, u32 gfxListSize, u32 ucode, u32 flag); /* nuGfxTaskStart */
void nuGfxTaskAllEndWait(void);

/* nuGfxInit */
void func_8008A1B0(void) {
    Gfx gfxList[0x101]; /* one entry more than nusys's 0x100: the frame is 8 bytes larger */
    Gfx *gfxList_ptr;

    func_8008B0B0();
    func_80089AB0(D_800A9EE0, 3);
    D_800C4B20 = (void *)0x80000400;
    func_800899D0(func_8008B110);
    D_800C4CE0 = D_800A9EB0;
    func_80089660();

    gfxList_ptr = gfxList;
    gfxList_ptr->w0 = 0xDE000000;
    gfxList_ptr->w1 = (u32)D_A9EF0;
    gfxList_ptr++;
    gfxList_ptr->w0 = 0xE9000000;
    gfxList_ptr->w1 = 0;
    gfxList_ptr++;
    gfxList_ptr->w0 = 0xDF000000;
    gfxList_ptr->w1 = 0;
    gfxList_ptr++;
    func_80089804(gfxList, (s32)(gfxList_ptr - gfxList) * sizeof(Gfx), 0, 0);
    nuGfxTaskAllEndWait();
}
