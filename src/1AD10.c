#include "common.h"

/* NuSystem nucontpakjiston64.c / nucontpakn64tojis.c: note-name conversion between JIS (half-width
   kana) and the controller pak's N64 font codes */

extern u8 D_800AA050[][2]; /* code_tbl: {jis, n64} pairs, ends with n64 == 0 */

/* nuContPakJisToN64 */
void func_8008A910(u8 *jis, u8 *n64, u32 len) {
    u32 cnt;
    u32 cnt2;

    for (cnt = 0; cnt < len; cnt++) {
        if (*jis == 0) {
            break;
        }
        if ((*jis >= 'A') && (*jis <= 'Z')) {
            *n64 = *jis - 0x27;
        } else if (((u8)(*jis - 'a')) < 26) {
            *n64 = *jis - 0x47;
        } else if ((*jis >= '0') && (*jis <= '9')) {
            *n64 = *jis - 0x20;
        } else if ((*jis >= 0xB1) && (*jis <= 0xDC)) {
            if (*(jis + 1) == 0xDE) {
                if (*jis < 0xCA) {
                    *n64 = *jis - 0x3A;
                } else {
                    *n64 = *jis - 0x3F;
                }
                jis++;
            } else if (*(jis + 1) == 0xDF) {
                *n64 = *jis - 0x3A;
                jis++;
            } else {
                *n64 = *jis - 0x61;
            }
        } else {
            for (cnt2 = 0; D_800AA050[cnt2][1]; cnt2++) {
                if (D_800AA050[cnt2][0] == *jis) {
                    *n64 = D_800AA050[cnt2][1];
                    break;
                }
            }
            if (!D_800AA050[cnt2][1]) {
                *n64 = 0xF;
            }
        }
        n64++;
        jis++;
    }
}

/* nuContPakN64ToJis */
void func_8008AA5C(u8 *n64, u8 *jis, u32 len) {
    u32 cnt;
    u32 cnt2;

    for (cnt = 0; cnt < len; cnt++) {
        if (*n64 == 0) {
            *jis = *n64;
        } else if ((*n64 >= 0x1A) && (*n64 <= 0x33)) {
            *jis = *n64 + 0x27;
        } else if ((*n64 >= 0x10) && (*n64 <= 0x19)) {
            *jis = *n64 + 0x20;
        } else if ((*n64 >= 0x50) && (*n64 <= 0x7B)) {
            *jis = *n64 + 0x61;
        } else if ((*n64 >= 0x7C) && (*n64 <= 0x8A)) {
            *jis = *n64 + 0x3A;
            *(jis + 1) = 0xDE;
            jis++;
        } else if ((*n64 >= 0x8B) && (*n64 <= 0x8F)) {
            *jis = *n64 + 0x3F;
            *(jis + 1) = 0xDE;
        } else if ((*n64 >= 0x90) && (*n64 <= 0x94)) {
            *jis = *n64 + 0x3A;
            *(jis + 1) = 0xDF;
        } else {
            for (cnt2 = 0; D_800AA050[cnt2][1]; cnt2++) {
                if (D_800AA050[cnt2][1] == *n64) {
                    *jis = D_800AA050[cnt2][0];
                    break;
                }
            }
            if (!D_800AA050[cnt2][1]) {
                *jis = 0xF;
            }
        }
        jis++;
        n64++;
    }
}
