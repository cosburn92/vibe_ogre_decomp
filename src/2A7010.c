#include "common.h"

/* 2A7010 */

extern s32 D_80220F68;
extern s32 D_80220F6C;
extern s32 D_80220F70;
extern void *D_80239110_ovl_29A4C0[];

void func_8020DD60(void *fn, s32 a);
/* --- end decls --- */

/* Scheduling of the index shift differs. */
void func_802377E0_ovl_29A4C0(s32 i, s32 a, s32 b, s32 c)
{
  void **new_var;
  D_80220F68 = a;
  new_var = &D_80239110_ovl_29A4C0[i];
  D_80220F6C = b;
  D_80220F70 = c;
  func_8020DD60(*new_var, 0);
}
