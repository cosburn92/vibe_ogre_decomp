#include "common.h"

/* Sound-effect request queue: requests are collected during the frame, then turned into a
 * command list that starts effects (within a voice budget) or changes their parameter. */

typedef struct {
    /* 0x00 */ u8 state; /* 0 free, 1 start, 2 change parameter */
    /* 0x01 */ u8 id;
    /* 0x02 */ u16 sound;
    /* 0x04 */ u16 priority;
    /* 0x06 */ u8 flags; /* 1: start even when over budget, 2: never merge */
    /* 0x07 */ u8 pad;
} SoundRequest;

typedef struct {
    /* 0x00 */ u8 state;
    /* 0x01 */ u8 id;
    /* 0x02 */ u8 cost;
    /* 0x03 */ u8 pad;
    /* 0x04 */ s32 handle;
} SoundVoice;

typedef struct {
    /* 0x00 */ s32 *handle;
    /* 0x04 */ u16 sound;
    /* 0x06 */ u8 type;
    /* 0x07 */ u8 pad;
} SoundCommand;

typedef struct {
    u8 data[0x50];
} SoundChannel;

extern SoundChannel D_800EB1F0_ovl_03F1B0;
extern SoundChannel D_800EB240_ovl_03F1B0;
extern SoundChannel D_800EB290_ovl_03F1B0;
extern u8 D_800EB700_ovl_03F1B0[]; /* voice cost per sound, two 4-bit entries per byte */
extern SoundRequest D_800EB8F0_ovl_03F1B0[16];
extern SoundVoice D_800EB970_ovl_03F1B0[16];
extern SoundCommand D_800EB9F0_ovl_03F1B0[];
extern s32 D_800EBAF0_ovl_03F1B0; /* command count; bit 31 = list ready */
extern u8 D_80104710_ovl_03F1B0[];

s32 func_80081770(s32 number);
s32 func_80081A54(s32 handle, s32 speed);
s32 func_80081B08(s32 handle);
void *func_80081DF0(void *bank);

void func_800EA9BC_ovl_03F1B0(u8 type, u8 id, u16 sound, u16 priority, u8 flags);
void func_800EAB40_ovl_03F1B0(u8 type, u8 id, u16 sound, u16 priority, u8 flags);
s32 func_800EB028_ovl_03F1B0(u8 state, u16 maxPriority);

void func_800EA8E0_ovl_03F1B0(void) {
    s32 i;

    for (i = 15; i >= 0; i--) {
        D_800EB8F0_ovl_03F1B0[i].state = 0;
    }
    for (i = 15; i >= 0; i--) {
        D_800EB970_ovl_03F1B0[i].state = 0;
    }
    D_800EBAF0_ovl_03F1B0 = 0;
}

s32 func_800EA924_ovl_03F1B0(SoundChannel *ch, s32 id, s32 sound, s32 priority) {
    if (ch == &D_800EB1F0_ovl_03F1B0) {
        func_800EA9BC_ovl_03F1B0(id, 4, sound, priority, 0);
    } else if (ch == &D_800EB240_ovl_03F1B0) {
        func_800EA9BC_ovl_03F1B0(id, 5, sound, priority, 0);
    } else if (ch == &D_800EB290_ovl_03F1B0) {
        func_800EA9BC_ovl_03F1B0(id, 6, sound, priority, 2);
    } else if (ch == NULL) {
        func_800EA9BC_ovl_03F1B0(id, 7, sound, priority, 1);
    } else {
        return 0;
    }
    return 1;
}

#ifdef NON_MATCHING
/* Loop shape differs: the original iterates a pointer to the priority field and hoists the masked arguments. */
void func_800EA9BC_ovl_03F1B0(u8 type, u8 id, u16 sound, u16 priority, u8 flags) {
    s32 i;

    switch (type) {
        case 1:
            if (flags & 2) {
                break;
            }
            for (i = 0; i < 16; i++) {
                if (D_800EB8F0_ovl_03F1B0[i].state == 1 && sound == D_800EB8F0_ovl_03F1B0[i].sound) {
                    goto found;
                }
            }
            break;
        case 2:
            if (sound == 0) {
                for (i = 0; i < 16; i++) {
                    if (D_800EB8F0_ovl_03F1B0[i].state == 1 && D_800EB8F0_ovl_03F1B0[i].id == id) {
                        D_800EB8F0_ovl_03F1B0[i].state = 0;
                    }
                }
            }
            for (i = 0; i < 16; i++) {
                if (D_800EB8F0_ovl_03F1B0[i].state == 2 && id == D_800EB8F0_ovl_03F1B0[i].id) {
                    D_800EB8F0_ovl_03F1B0[i].sound = sound;
                found:
                    if (D_800EB8F0_ovl_03F1B0[i].priority < priority) {
                        D_800EB8F0_ovl_03F1B0[i].priority = priority;
                    }
                    return;
                }
            }
            break;
    }
    func_800EAB40_ovl_03F1B0(type, id, sound, priority, flags);
}
#else
INCLUDE_ASM("asm/nonmatchings/3FE70", func_800EA9BC_ovl_03F1B0);
#endif

/* Adds a request, replacing the lowest-priority one when the queue is full */
void func_800EAB40_ovl_03F1B0(u8 type, u8 id, u16 sound, u16 priority, u8 flags) {
    s32 i;
    s32 min = 0;

    for (i = 0; i < 16; i++) {
        if (D_800EB8F0_ovl_03F1B0[i].state == 0) {
            D_800EB8F0_ovl_03F1B0[i].state = type;
            D_800EB8F0_ovl_03F1B0[i].id = id;
            D_800EB8F0_ovl_03F1B0[i].sound = sound;
            D_800EB8F0_ovl_03F1B0[i].priority = priority;
            D_800EB8F0_ovl_03F1B0[i].flags = flags;
            return;
        }
        if (D_800EB8F0_ovl_03F1B0[i].priority < D_800EB8F0_ovl_03F1B0[min].priority) {
            min = i;
        }
    }
    if (D_800EB8F0_ovl_03F1B0[min].priority < priority) {
        D_800EB8F0_ovl_03F1B0[min].state = type;
        D_800EB8F0_ovl_03F1B0[min].id = id;
        D_800EB8F0_ovl_03F1B0[min].sound = sound;
        D_800EB8F0_ovl_03F1B0[min].priority = priority;
        D_800EB8F0_ovl_03F1B0[min].flags = flags;
    }
}

/* Builds this frame's command list from the queued requests */
#ifdef NON_MATCHING
/* Store order/scheduling of the command-list writes and the first loop differ. */
void func_800EAC24_ovl_03F1B0(void) {
    s32 budget = 8;
    s32 i;
    s32 j;
    s32 cost;
    u16 priority;

    D_800EBAF0_ovl_03F1B0 = 0;
    for (i = 0; i < 16; i++) {
        if (D_800EB970_ovl_03F1B0[i].state != 0) {
            if (!func_80081B08(D_800EB970_ovl_03F1B0[i].handle)) {
                D_800EB970_ovl_03F1B0[i].state = 0;
            } else {
                D_800EB970_ovl_03F1B0[i].state = 2;
                budget -= D_800EB970_ovl_03F1B0[i].cost;
            }
        }
    }

    priority = 0xFFFF;
    while ((j = func_800EB028_ovl_03F1B0(2, priority)) >= 0) {
        priority = D_800EB8F0_ovl_03F1B0[j].priority;
        for (i = 0; i < 16; i++) {
            if (D_800EB970_ovl_03F1B0[i].state != 0 && D_800EB970_ovl_03F1B0[i].id == D_800EB8F0_ovl_03F1B0[j].id) {
                D_800EB9F0_ovl_03F1B0[D_800EBAF0_ovl_03F1B0].handle = &D_800EB970_ovl_03F1B0[i].handle;
                D_800EB9F0_ovl_03F1B0[D_800EBAF0_ovl_03F1B0].type = 2;
                D_800EB9F0_ovl_03F1B0[D_800EBAF0_ovl_03F1B0].sound = D_800EB8F0_ovl_03F1B0[j].sound;
                D_800EBAF0_ovl_03F1B0++;
            }
        }
        D_800EB8F0_ovl_03F1B0[j].state = 0;
    }

    priority = 0xFFFF;
    while ((j = func_800EB028_ovl_03F1B0(1, priority)) >= 0) {
        priority = D_800EB8F0_ovl_03F1B0[j].priority;
        cost = (D_800EB700_ovl_03F1B0[D_800EB8F0_ovl_03F1B0[j].sound >> 1] >>
                ((~D_800EB8F0_ovl_03F1B0[j].sound & 1) * 4)) & 0xF;
        if (budget < cost && !(D_800EB8F0_ovl_03F1B0[j].flags & 1)) {
            break;
        }
        for (i = 0; i < 16; i++) {
            if (D_800EB970_ovl_03F1B0[i].state == 0) {
                D_800EB970_ovl_03F1B0[i].state = 1;
                D_800EB970_ovl_03F1B0[i].cost = cost;
                D_800EB970_ovl_03F1B0[i].id = D_800EB8F0_ovl_03F1B0[j].id;
                D_800EB9F0_ovl_03F1B0[D_800EBAF0_ovl_03F1B0].handle = &D_800EB970_ovl_03F1B0[i].handle;
                D_800EB9F0_ovl_03F1B0[D_800EBAF0_ovl_03F1B0].type = 1;
                D_800EB9F0_ovl_03F1B0[D_800EBAF0_ovl_03F1B0].sound = D_800EB8F0_ovl_03F1B0[j].sound;
                D_800EBAF0_ovl_03F1B0++;
                D_800EB8F0_ovl_03F1B0[j].state = 0;
                budget -= cost;
                break;
            }
        }
        if (i >= 16) {
            break;
        }
    }
    D_800EBAF0_ovl_03F1B0 |= 0x80000000;
}
#else
INCLUDE_ASM("asm/nonmatchings/3FE70", func_800EAC24_ovl_03F1B0);
#endif

/* Runs the command list (audio side) */
void func_800EAF1C_ovl_03F1B0(void) {
    u32 i;

    if (D_800EBAF0_ovl_03F1B0 < 0) {
        D_800EBAF0_ovl_03F1B0 &= 0x7FFFFFFF;
        for (i = 0; i < D_800EBAF0_ovl_03F1B0; i++) {
            switch (D_800EB9F0_ovl_03F1B0[i].type) {
                case 1:
                    func_80081DF0(D_80104710_ovl_03F1B0);
                    *D_800EB9F0_ovl_03F1B0[i].handle = func_80081770(D_800EB9F0_ovl_03F1B0[i].sound);
                    break;
                case 2:
                    func_80081A54(*D_800EB9F0_ovl_03F1B0[i].handle,
                                  D_800EB9F0_ovl_03F1B0[i].sound < 2 ? 2 : D_800EB9F0_ovl_03F1B0[i].sound);
                    break;
            }
        }
    }
}

/* Highest-priority request in the given state (priority <= maxPriority), or -1 */
#ifdef NON_MATCHING
/* Only the counter and offset registers (a2/a3) are swapped. */
s32 func_800EB028_ovl_03F1B0(u8 state, u16 maxPriority) {
    s32 best = -1;
    s32 found = 0;
    s32 i;

    for (i = 0; i < 16; i++) {
        if (D_800EB8F0_ovl_03F1B0[i].state == state && D_800EB8F0_ovl_03F1B0[i].priority <= maxPriority) {
            if (!found || D_800EB8F0_ovl_03F1B0[best].priority < D_800EB8F0_ovl_03F1B0[i].priority) {
                best = i;
            }
        }
    }
    return best;
}
#else
INCLUDE_ASM("asm/nonmatchings/3FE70", func_800EB028_ovl_03F1B0);
#endif
