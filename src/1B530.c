#include "common.h"
#include "nusys.h"

/* NuSystem nusicallbackadd.c, nusicallbackremove.c */

extern NUCallBackList *D_800A9EA0; /* nuSiCallBackList */

u32 osSetIntMask(u32 mask);

/* nuSiCallBackAdd */
void func_8008B130(NUCallBackList *list) {
    NUCallBackList **siCallBackListPtr;
    s32 cnt;
    u32 mask;

    siCallBackListPtr = &D_800A9EA0;
    while (*siCallBackListPtr) {
        if ((*siCallBackListPtr)->majorNo == list->majorNo) {
            return;
        }
        siCallBackListPtr = &(*siCallBackListPtr)->next;
    }
    for (cnt = 1; list->func[cnt] != NULL; cnt++) {
    }
    mask = osSetIntMask(1);
    *siCallBackListPtr = list;
    list->next = NULL;
    list->funcNum = cnt;
    osSetIntMask(mask);
}

/* nuSiCallBackRemove */
void func_8008B1D0(NUCallBackList *list) {
    NUCallBackList **siCallBackListPtr;
    NUCallBackList *siCallBackPtr;
    u32 mask;

    siCallBackListPtr = &D_800A9EA0;
    while (*siCallBackListPtr) {
        siCallBackPtr = (*siCallBackListPtr)->next;
        if (siCallBackPtr == list) {
            mask = osSetIntMask(1);
            (*siCallBackListPtr)->next = siCallBackPtr->next;
            siCallBackPtr->next = NULL;
            osSetIntMask(mask);
            break;
        }
        siCallBackListPtr = &(*siCallBackListPtr)->next;
    }
}
