/* Second names for data addresses that the original code reaches through two different symbols
 * (end of one block = start of the next), so the compiler does not merge the address loads. */
jpegTextStart = D_8009ED80; /* rspboot text end = JPEG microcode text start */
D_8022A921_head_ovl_281860 = D_8022A921_ovl_281860;
D_80220EE0_b_ovl_25EE90 = D_80220EE0_ovl_25EE90; /* base matrix, second name used by the spell-bolt handlers */
D_8022A720_rects_ovl_1BA050 = D_8022A720_ovl_1BA050; /* rectangle list (count + 8-byte rects) viewed as one struct by func_802296B0 */
D_801ABDD8_ovl_0EBBB0 = D_801ABE08_ovl_0EBBB0 - 0x30; /* sun colour table [angle][2][4][3], first half overlaps the D_801ABD58 label */
D_800A8740_root = D_800A8740; /* asset cache root stored as an array element by LoadAsset */
