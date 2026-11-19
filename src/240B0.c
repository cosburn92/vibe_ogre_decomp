#include "common.h"

INCLUDE_ASM("asm/nonmatchings/240B0", osCreateScheduler);

INCLUDE_ASM("asm/nonmatchings/240B0", osScAddClient);

INCLUDE_ASM("asm/nonmatchings/240B0", osScRemoveClient);

INCLUDE_ASM("asm/nonmatchings/240B0", osScGetCmdQ);

INCLUDE_ASM("asm/nonmatchings/240B0", __scMain);

INCLUDE_ASM("asm/nonmatchings/240B0", __scHandleRetrace);

INCLUDE_ASM("asm/nonmatchings/240B0", __scHandleRSP);

INCLUDE_ASM("asm/nonmatchings/240B0", __scHandleRDP);

INCLUDE_ASM("asm/nonmatchings/240B0", __scTaskReady);

INCLUDE_ASM("asm/nonmatchings/240B0", __scTaskComplete);

INCLUDE_ASM("asm/nonmatchings/240B0", __scAppendList);

INCLUDE_ASM("asm/nonmatchings/240B0", __scExec);

INCLUDE_ASM("asm/nonmatchings/240B0", __scYield);

INCLUDE_ASM("asm/nonmatchings/240B0", __scSchedule);
