#include "common.h"

/* 112C00 */

extern u8 *D_801AB850;
/* --- end decls --- */

INCLUDE_ASM("asm/nonmatchings/112C00", func_801BE4C0_ovl_101CE0);

#ifndef FIELD
#define FIELD(p, T, off) (*(T *)((u8 *)(p) + (off)))
#endif
extern s32 D_801F0DE0_ovl_101CE0;
extern s32 D_801F3610_ovl_101CE0;
extern f32 D_801F0DB8_ovl_101CE0; /* pan limits: min x, min z, max x, max z */
extern f32 D_801F0DBC_ovl_101CE0;
extern f32 D_801F0DC0_ovl_101CE0;
extern f32 D_801F0DC4_ovl_101CE0;
extern f32 *D_8018F58C;           /* field camera */
extern u8 D_800E7A90[];
s32 func_801DD244_ovl_101CE0(void);
s32 func_801AAE10(void *cam, f32 x, f32 y, f32 *out);
s32 func_801AA8A4(s32 map, void *cam, f32 x, f32 y, f32 *out);

/* Pans the field camera with the stick (speed scales it), keeping the ground point under the
 * cursor inside the map limits; a clamped axis drops its stick input */
void func_801BECD0_ovl_101CE0(f32 speed) {
    f32 p[3];
    f32 dx;
    f32 dz;
    f32 x;
    f32 z;
    u8 h = func_801DD244_ovl_101CE0() != 0;

    if (D_801F0DE0_ovl_101CE0 != 2 && D_801F3610_ovl_101CE0 != 0) {
        dx = (f32)(s8)D_801AB850[6] / 128.0f * speed;
        dz = (f32)-(s8)D_801AB850[7] / 128.0f * speed;
        if (!h) {
            func_801AAE10(D_8018F58C, FIELD(D_801AB850, f32, 8), FIELD(D_801AB850, f32, 0xC), p);
        } else {
            func_801AA8A4(D_800E7A90[0x29], D_8018F58C, FIELD(D_801AB850, f32, 8), FIELD(D_801AB850, f32, 0xC), p);
        }
        x = p[0] + dx;
        z = p[2] + dz;
        if (D_801F0DB8_ovl_101CE0 <= x && x <= D_801F0DC0_ovl_101CE0) {
            D_8018F58C[8] += dx;
            D_8018F58C[5] += dx;
        } else {
            if (x < D_801F0DB8_ovl_101CE0) {
                x = D_801F0DB8_ovl_101CE0;
            } else if (D_801F0DC0_ovl_101CE0 < x) {
                x = D_801F0DC0_ovl_101CE0;
            }
            D_8018F58C[8] += x - p[0];
            D_8018F58C[5] += x - p[0];
            D_801AB850[6] = 0;
        }
        if (D_801F0DBC_ovl_101CE0 <= z && z <= D_801F0DC4_ovl_101CE0) {
            D_8018F58C[10] += dz;
            D_8018F58C[7] += dz;
        } else {
            if (z < D_801F0DBC_ovl_101CE0) {
                z = D_801F0DBC_ovl_101CE0;
            } else if (D_801F0DC4_ovl_101CE0 < z) {
                z = D_801F0DC4_ovl_101CE0;
            }
            D_8018F58C[10] += z - p[2];
            D_8018F58C[7] += z - p[2];
            D_801AB850[7] = 0;
        }
    }
}

extern s8 D_801F0E13_ovl_101CE0;
extern u16 *D_801F0CA0_ovl_101CE0; /* button map */
extern u16 D_800E8100;              /* buttons pressed */
extern u8 D_801F0D90_ovl_101CE0;
extern f32 D_801F0D94_ovl_101CE0;
extern f32 D_801E91C8_ovl_101CE0; /* zoom angle min */
extern f32 D_801E91CC_ovl_101CE0; /* zoom angle max */
extern f32 D_8018F578;
extern f32 D_8018F580;
extern f32 D_8018F584;
extern f32 D_8018F588;
f32 sinf(f32 x);
f32 cosf(f32 x);

/* Steps the field camera zoom: the zoom buttons pick one of three levels, the angle (s + 0x10)
 * accelerates toward it (0.18 per frame, at most 2.5) and the camera height, distance and fov
 * follow it */
#ifdef NON_MATCHING
/* 231/227 instructions: the zoom-level switch is a tree (==1, <2, ==2) in the original, and the stores of the speed and D_801F3610 are scheduled differently */
void func_801BEF54_ovl_101CE0(void) {
    s32 m = D_801F0DE0_ovl_101CE0;
    f32 target;
    f32 a;
    f32 r;
    f32 *cam;

    if ((m != 0x2A && m != 0) && (m != 1 && m != 0x1F)) {
        return;
    }
    if (m == 1 && D_801F0E13_ovl_101CE0 == m) {
        return;
    }
    if (m != 0x1F) {
        if (D_801F0CA0_ovl_101CE0[0xC] & D_800E8100) {
            if (D_801AB850[4] < 2) {
                D_801AB850[4]++;
            }
        }
        if (D_801F0CA0_ovl_101CE0[0xD] & D_800E8100) {
            if (D_801AB850[4] != 0) {
                D_801AB850[4]--;
            }
        }
    }
    D_801F0D90_ovl_101CE0 = D_801AB850[4];
    D_801F0D94_ovl_101CE0 = FIELD(D_801AB850, f32, 0x10);
    switch (D_801AB850[4]) {
        case 1:
            target = (D_801E91C8_ovl_101CE0 + D_801E91CC_ovl_101CE0) * 0.6f;
            break;
        case 2:
            target = D_801E91CC_ovl_101CE0;
            break;
        default:
            target = D_801E91C8_ovl_101CE0;
            break;
    }
    if (FIELD(D_801AB850, f32, 0x10) < target) {
        D_801F3610_ovl_101CE0 = 1;
        FIELD(D_801AB850, f32, 0x14) += 0.18f;
        if (FIELD(D_801AB850, f32, 0x14) > 2.5f) {
            FIELD(D_801AB850, f32, 0x14) = 2.5f;
        }
        FIELD(D_801AB850, f32, 0x10) += FIELD(D_801AB850, f32, 0x14);
        if (target < FIELD(D_801AB850, f32, 0x10)) {
            FIELD(D_801AB850, f32, 0x10) = target;
            FIELD(D_801AB850, f32, 0x14) = 0;
        }
    } else if (target < FIELD(D_801AB850, f32, 0x10)) {
        D_801F3610_ovl_101CE0 = 1;
        FIELD(D_801AB850, f32, 0x14) -= 0.18f;
        if (FIELD(D_801AB850, f32, 0x14) < -2.5f) {
            FIELD(D_801AB850, f32, 0x14) = -2.5f;
        }
        FIELD(D_801AB850, f32, 0x10) += FIELD(D_801AB850, f32, 0x14);
        if (FIELD(D_801AB850, f32, 0x10) < target) {
            FIELD(D_801AB850, f32, 0x10) = target;
            FIELD(D_801AB850, f32, 0x14) = 0;
        }
    }
    if (FIELD(D_801AB850, f32, 0x10) < D_801E91C8_ovl_101CE0) {
        FIELD(D_801AB850, f32, 0x10) = D_801E91C8_ovl_101CE0;
        FIELD(D_801AB850, f32, 0x14) = 0.0f;
    }
    if (D_801E91CC_ovl_101CE0 < FIELD(D_801AB850, f32, 0x10)) {
        FIELD(D_801AB850, f32, 0x10) = D_801E91CC_ovl_101CE0;
        FIELD(D_801AB850, f32, 0x14) = 0.0f;
    }
    D_801F0D94_ovl_101CE0 = FIELD(D_801AB850, f32, 0x10);
    cam = D_8018F58C;
    cam[0] = D_8018F584 + (D_8018F588 - D_8018F584) * (FIELD(D_801AB850, f32, 0x10) - D_801E91C8_ovl_101CE0) /
                              (D_801E91CC_ovl_101CE0 - D_801E91C8_ovl_101CE0);
    a = FIELD(D_801AB850, f32, 0x10) / 360.0f * 6.2831855f;
    r = D_8018F578 * D_8018F580;
    cam[7] = cam[10] + D_8018F578 * cosf(a);
    cam = D_8018F58C;
    cam[6] = cam[9] + r * sinf(a);
}
#else
INCLUDE_ASM("asm/nonmatchings/112C00", func_801BEF54_ovl_101CE0);
#endif

/* Steps the 0..4 open counter at +0x1C (clears +0x20 when it reaches 4) */
void func_801BF2F0_ovl_101CE0(void) {
    u8 *s = D_801AB850;

    if (s[0x18] & 1) {
        if (*(s32 *)(s + 0x1C) < 4) {
            if (++*(s32 *)(s + 0x1C) == 4) {
                s[0x20] = 0;
            }
        }
    } else if (*(s32 *)(s + 0x1C) > 0) {
        (*(s32 *)(s + 0x1C))--;
    }
}
