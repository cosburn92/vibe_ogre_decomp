#include "common.h"
#include "libultra.h"

/* libultra siacs.c */

extern OSMesgQueue D_800E9BC8; /* __osSiAccessQueue */
extern u32 D_800AA780;         /* __osSiAccessQueueEnabled */
extern OSMesg D_800C35A0[1];   /* siAccessBuf */

inline void __osSiCreateAccessQueue(void) {
    D_800AA780 = 1;
    osCreateMesgQueue(&D_800E9BC8, D_800C35A0, 1);
    osSendMesg(&D_800E9BC8, NULL, OS_MESG_NOBLOCK);
}

void __osSiGetAccess(void) {
    OSMesg dummyMesg;

    if (!D_800AA780) {
        __osSiCreateAccessQueue();
    }
    osRecvMesg(&D_800E9BC8, &dummyMesg, OS_MESG_BLOCK);
}

void __osSiRelAccess(void) {
    osSendMesg(&D_800E9BC8, NULL, OS_MESG_NOBLOCK);
}
