#include "common.h"
#include "nusys.h"

/* NuSystem nugfxthread.c */

extern OSMesgQueue D_800C4C28;      /* nuGfxMesgQ */
extern OSMesg D_800BE1A0[];         /* nuGfxMesgBuf */
extern void (*D_800AA090)(u32);     /* nuGfxFunc */
extern void (*D_800AA094)(void);    /* nuGfxPreNMIFunc */
extern u32 D_800E79A4;              /* nuGfxTaskSpool */
extern OSThread D_800BE1C0;         /* GfxThread */
extern u64 D_800C2370[];            /* end of GfxStack */

void func_80089054(NUScClient *c, OSMesgQueue *mq, NUScMsg msgType); /* nuScAddClient */

/* nuGfxThread */
void func_8008AFE0(void *arg) {
    NUScClient gfxClient;
    NUScMsg *mesg_type;

    osCreateMesgQueue(&D_800C4C28, D_800BE1A0, 8);
    func_80089054(&gfxClient, &D_800C4C28, 3); /* NU_SC_RETRACE_MSG | NU_SC_PRENMI_MSG */
    while (1) {
        osRecvMesg(&D_800C4C28, (OSMesg *)&mesg_type, OS_MESG_BLOCK);
        switch (*mesg_type) {
            case 1: /* NU_SC_RETRACE_MSG */
                if (D_800AA090 != NULL) {
                    (*D_800AA090)(D_800E79A4);
                }
                break;
            case 2: /* NU_SC_PRENMI_MSG */
                if (D_800AA094 != NULL) {
                    (*D_800AA094)();
                }
                break;
            default:
                break;
        }
    }
}

/* nuGfxThreadStart */
void func_8008B0B0(void) {
    osCreateThread(&D_800BE1C0, 4, func_8008AFE0, NULL, D_800C2370, 0x32);
    osStartThread(&D_800BE1C0);
}
