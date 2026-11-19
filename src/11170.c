#include "common.h"
#include "nusys.h"

/* Glue between libmus and the NuSystem scheduler (the libmus sample "nu_mus" scheduler interface) */

#define OS_MESG_BLOCK 1
#define M_AUDTASK 2
#define NU_SC_PRENMI_MSG 2

typedef struct {
    void (*init)(void);
    void (*waitFrame)(void);
    void (*doTask)(u32 *task);
} MusSched;

typedef void (*MusFrameCallback)(s32 type, s32 frame);

extern u8 D_800A9890;                /* audio task enabled */
extern u8 D_800A9891;                /* frame counter */
extern MusFrameCallback D_800A9894;  /* per-frame callback */
extern MusSched D_800A9898;
extern OSMesg D_800B17D0[4];
extern OSMesg D_800B17E0[1];
extern OSMesgQueue D_800C49E8;       /* task done queue */
extern NUScTask audioTask;
extern OSMesgQueue D_800E7970;       /* NuSystem client */
extern OSMesgQueue D_800E79C8;       /* retrace queue */
extern OSMesgQueue D_800E8B14;       /* nuScAudioMesgQ */
extern u64 D_8009ECB0[];             /* rspbootTextStart */
extern u64 D_8009ED80[];             /* rspbootTextEnd */

f32 func_8009C750(f32 x, f32 *ip); /* modff */
void func_8008203C(MusSched *sched); /* MusSetScheduler */
void func_8008123C(void *config);    /* MusInitialize */
void func_80089054(void *c, OSMesgQueue *mq, NUScMsg msgType); /* nuScAddClient */
s32 osSendMesg(OSMesgQueue *mq, OSMesg msg, s32 flag);

/* Round to nearest (halves round down) */
s32 func_80080D70(f32 x) {
    f32 ip;
    s32 i = x;

    if (func_8009C750(x, &ip) > 0.5) {
        i++;
    }
    return i;
}

void func_80080DC0(void *config) {
    D_800A9890 = 1;
    audioTask.msgQ = &D_800C49E8;
    audioTask.list.t.type = M_AUDTASK;
    audioTask.msg = 0;
    audioTask.list.t.ucode_boot = D_8009ECB0;
    audioTask.list.t.ucode_boot_size = (u8 *)D_8009ED80 - (u8 *)D_8009ECB0;
    audioTask.list.t.ucode_data_size = 0x800;
    audioTask.list.t.dram_stack = NULL;
    audioTask.list.t.dram_stack_size = 0;
    audioTask.list.t.output_buff = NULL;
    audioTask.list.t.output_buff_size = NULL;
    audioTask.list.t.yield_data_ptr = NULL;
    audioTask.list.t.yield_data_size = 0;
    func_8008203C(&D_800A9898);
    func_8008123C(config);
}

void func_80080E84(void) {
    osCreateMesgQueue(&D_800E79C8, D_800B17D0, 4);
    osCreateMesgQueue(&D_800C49E8, D_800B17E0, 1);
    func_80089054(&D_800E7970, &D_800E79C8, 3);
}

void func_80080EE8(void) {
    NUScMsg *msg;

    while (1) {
        osRecvMesg(&D_800E79C8, (OSMesg *)&msg, OS_MESG_BLOCK);
        switch (*msg) {
            case 1:
                return;
            case NU_SC_PRENMI_MSG:
                if (D_800A9894 != NULL) {
                    D_800A9894(2, D_800A9891);
                }
                D_800A9891++;
                break;
        }
    }
}

void func_80080F78(u32 *task) {
    if (D_800A9890 == 1) {
        audioTask.list.t.data_ptr = (u64 *)task[0];
        audioTask.list.t.data_size = task[1];
        audioTask.list.t.ucode = (u64 *)task[2];
        audioTask.list.t.ucode_data = (u64 *)task[3];
        osSendMesg(&D_800E8B14, &audioTask, OS_MESG_BLOCK);
        osRecvMesg(&D_800C49E8, NULL, OS_MESG_BLOCK);
    }
    if (D_800A9894 != NULL && D_800A9891 != 0) {
        D_800A9894(1, D_800A9891);
        D_800A9891++;
    }
}
