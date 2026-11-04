#include "texp.h"

#include <string.h>

#include "class.h"
#include "debug.h"
#include "tev.h"
#include "texpdag.h"
#include "tobj.h"

#include "texp_inline.h"
#undef __FILE__
#define __FILE__ "texp.c"

void HSD_TExpFree(HSD_TExp* texp)
{
    switch (HSD_TExpGetType(texp)) {
    case HSD_TE_TEV:
        hsdFreeMemPiece(texp, sizeof(HSD_TETev));
        break;
    case HSD_TE_CNST:
        hsdFreeMemPiece(texp, sizeof(HSD_TECnst));
        break;
    default:
        break;
    }
}

HSD_TExp* HSD_TExpFreeList(HSD_TExp* texp_list, HSD_TExpType type, s32 all)
{
    HSD_TExp** handle;
    HSD_TExp* ptr;
    HSD_TExp* next;

    handle = &texp_list;

    if (all != 0) {
        while (*handle != NULL) {
            if (type == HSD_TE_ALL || type == (*handle)->type) {
                switch ((*handle)->type) {
                case HSD_TE_TEV:
                    next = (*handle)->tev.next;
                    HSD_TExpFree(*handle);
                    *handle = next;
                    continue;
                case HSD_TE_CNST:
                    next = (*handle)->tev.next;
                    HSD_TExpFree(*handle);
                    *handle = next;
                    continue;
                default:
                    HSD_ASSERT(0xDC, 0);
                }
            }
            handle = &(*handle)->tev.next;
        }
    } else {
        if (type == HSD_TE_ALL || type == HSD_TE_TEV) {
            for (ptr = texp_list; ptr != NULL; ptr = ptr->tev.next) {
                switch (ptr->type) {
                case HSD_TE_TEV:
                    if (ptr->tev.c_ref == 0 && ptr->tev.c_ref == 0) {
                        HSD_TExpUnref(ptr, 1);
                        HSD_TExpUnref(ptr, 5);
                    }
                    break;
                default:
                    break;
                }
            }
        }

        while (*handle != NULL) {
            if (type == HSD_TE_ALL || type == (*handle)->type) {
                switch ((*handle)->type) {
                case HSD_TE_TEV:
                    if ((*handle)->tev.c_ref != 0 || (*handle)->tev.a_ref != 0)
                    {
                        break;
                    }
                    next = (*handle)->tev.next;
                    HSD_TExpFree(*handle);
                    *handle = next;
                    continue;
                case HSD_TE_CNST:
                    if ((*handle)->cnst.ref != 0) {
                        break;
                    }
                    next = (*handle)->tev.next;
                    HSD_TExpFree(*handle);
                    *handle = next;
                    continue;
                default:
                    HSD_ASSERT(0x10C, 0);
                }
            }
            handle = &(*handle)->tev.next;
        }
    }

    return texp_list;
}
