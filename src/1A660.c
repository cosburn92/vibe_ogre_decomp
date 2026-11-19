#include "common.h"
#include "nusys.h"

/* NuSystem nucontmgr.c */

extern OSMesgQueue D_800E9B88;      /* nuSiMesgQ */
extern OSMesgQueue D_800C4A00;      /* nuContWaitMesgQ */
extern OSMesg D_800BE190;           /* nuContWaitMesgBuf */
extern OSMesgQueue nuContDataMutexQ;
extern OSMesg D_800BE194;           /* nuContDataMutexBuf */
extern NUCallBackList D_800A9FF8;   /* nuContCallBack */
extern u32 D_800C6D60;              /* nuContNum */
extern OSContStatus D_800C4B38[4];  /* nuContStatus */
extern u32 D_800C4B30;              /* nuContDataLockKey */
extern OSContPad D_800C4BF0[4];     /* nuContData */
extern void (*D_800A9FE0)(u32);     /* nuContReadFunc */

s32 osContStartReadData(OSMesgQueue *mq);
void osContGetReadData(OSContPad *pad);
s32 osContStartQuery(OSMesgQueue *mq);
void osContGetQuery(OSContStatus *status);

void func_8008A5D0(void);                   /* nuContDataUnLock */
void func_8008B130(NUCallBackList *list);   /* nuSiCallBackAdd */
void func_8008B1D0(NUCallBackList *list);   /* nuSiCallBackRemove */
void func_8008A640(void);                   /* nuContQueryRead */
void nuContDataClose(void);
void func_8008A37C(void);
s32 func_8008A3A4(OSContPad *pad, u32 lockflag);

/* nuContMgrInit */
u8 func_8008A260(void) {
    s32 cnt;
    u8 pattern;
    u8 bitmask;

    func_8008A5D0();
    osCreateMesgQueue(&D_800C4A00, &D_800BE190, 1);
    osCreateMesgQueue(&nuContDataMutexQ, &D_800BE194, 1);
    func_8008B130(&D_800A9FF8);
    func_8008A640();

    bitmask = 1;
    pattern = 0;
    D_800C6D60 = 0;
    for (cnt = 0; cnt < 4; cnt++) {
        if (D_800C4B38[cnt].errno) {
            continue;
        }
        if ((D_800C4B38[cnt].type & 0x1F07) == 5) { /* CONT_TYPE_NORMAL */
            pattern |= bitmask;
            D_800C6D60++;
        }
        bitmask <<= 1;
    }
    return pattern;
}

/* nuContMgrRemove */
void func_8008A334(void) {
    func_8008B1D0(&D_800A9FF8);
}

void nuContDataClose(void) {
    osSendMesg(&nuContDataMutexQ, NULL, OS_MESG_BLOCK);
}

/* nuContDataOpen */
void func_8008A37C(void) {
    osRecvMesg(&nuContDataMutexQ, NULL, OS_MESG_BLOCK);
}

/* contReadData */
s32 func_8008A3A4(OSContPad *pad, u32 lockflag) {
    s32 rtn;

    rtn = osContStartReadData(&D_800E9B88);
    if (rtn) {
        return rtn;
    }
    osRecvMesg(&D_800E9B88, NULL, OS_MESG_BLOCK);
    if (lockflag & D_800C4B30) {
        return rtn;
    }
    nuContDataClose();
    osContGetReadData(pad);
    func_8008A37C();
    return rtn;
}

/* contQuery */
s32 func_8008A42C(NUSiCommonMesg *mesg) {
    s32 rtn;

    rtn = osContStartQuery(&D_800E9B88);
    if (rtn) {
        return rtn;
    }
    osRecvMesg(&D_800E9B88, NULL, OS_MESG_BLOCK);
    osContGetQuery(D_800C4B38);
    return rtn;
}

/* contRetrace */
s32 func_8008A47C(NUSiCommonMesg *mesg) {
    if (D_800C4B30) {
        return 0;
    }
    osRecvMesg(&D_800C4A00, NULL, OS_MESG_NOBLOCK);
    func_8008A3A4(D_800C4BF0, 1);
    if (D_800A9FE0) {
        (*D_800A9FE0)(mesg->mesg);
    }
    osSendMesg(&D_800C4A00, NULL, OS_MESG_NOBLOCK);
    return 0;
}

/* contReadNW */
s32 func_8008A508(NUSiCommonMesg *mesg) {
    return func_8008A3A4(mesg->dataPtr, 0);
}

/* contRead */
s32 func_8008A528(NUSiCommonMesg *mesg) {
    s32 rtn;

    osRecvMesg(&D_800C4A00, NULL, OS_MESG_NOBLOCK);
    rtn = func_8008A3A4(D_800C4BF0, 0);
    if (rtn) {
        return rtn;
    }
    if (D_800A9FE0) {
        (*D_800A9FE0)(mesg->mesg);
    }
    return rtn;
}
