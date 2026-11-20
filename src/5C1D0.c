#include "common.h"

/* 5C1D0 */

extern u8 D_80196AEC_ovl_040E80;
extern u8 D_8018FE44_ovl_040E80[];
extern u8 D_8018FE30_ovl_040E80[];
/* --- end decls --- */

/* Branch layout differs. */
u8 *func_801862D0_ovl_040E80(void)
{
  u8 v = D_80196AEC_ovl_040E80;
  if (v & 8)
  {
    return D_8018FE44_ovl_040E80;
  }
  if (D_8018FE44_ovl_040E80)
  {
    D_80196AEC_ovl_040E80 = v & 0xDF;
    return D_8018FE30_ovl_040E80;
  }
  else
  {
    D_80196AEC_ovl_040E80 = v & 0xDF;
    return D_8018FE30_ovl_040E80;
  }
}
