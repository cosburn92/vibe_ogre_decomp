#include "common.h"

/* libultra contramread.c CRC helpers (crc.c) */

#define ADDRESS_CRC_MESSAGE_LENGTH 10
#define ADDRESS_CRC_LENGTH 5
#define ADDRESS_CRC_GENERATOR 0x15
#define ADDRESS_CRC_MASK ((1 << ADDRESS_CRC_LENGTH) - 1)

#define DATA_CRC_MESSAGE_BYTES 32
#define DATA_CRC_LENGTH 8
#define DATA_CRC_GENERATOR 0x85

u8 __osContAddressCrc(u16 addr) {
    u32 ret = 0;
    u32 bit;

    for (bit = (1 << ADDRESS_CRC_MESSAGE_LENGTH); bit != 0; bit >>= 1) {
        ret <<= 1;
        if (addr & bit) {
            if (ret & (1 << ADDRESS_CRC_LENGTH)) {
                ret ^= ADDRESS_CRC_GENERATOR - 1;
            } else {
                ret++;
            }
        } else if (ret & (1 << ADDRESS_CRC_LENGTH)) {
            ret ^= ADDRESS_CRC_GENERATOR;
        }
    }
    for (bit = ADDRESS_CRC_LENGTH; bit != 0; bit--) {
        ret <<= 1;
        if (ret & (1 << ADDRESS_CRC_LENGTH)) {
            ret ^= ADDRESS_CRC_GENERATOR;
        }
    }
    return ret & ADDRESS_CRC_MASK;
}

u8 __osContDataCrc(u8 *data) {
    u32 ret = 0;
    u32 bit;
    u32 byte;

    for (byte = DATA_CRC_MESSAGE_BYTES; byte != 0; byte--, data++) {
        for (bit = (1 << (DATA_CRC_LENGTH - 1)); bit != 0; bit >>= 1) {
            ret <<= 1;
            if (*data & bit) {
                if (ret & (1 << DATA_CRC_LENGTH)) {
                    ret ^= DATA_CRC_GENERATOR - 1;
                } else {
                    ret++;
                }
            } else if (ret & (1 << DATA_CRC_LENGTH)) {
                ret ^= DATA_CRC_GENERATOR;
            }
        }
    }
    do {
        ret <<= 1;
        if (ret & (1 << DATA_CRC_LENGTH)) {
            ret ^= DATA_CRC_GENERATOR;
        }
        byte++;
    } while (byte < DATA_CRC_LENGTH);
    return ret;
}
