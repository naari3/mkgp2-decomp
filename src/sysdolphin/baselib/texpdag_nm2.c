#include "texpdag.h"

#include <placeholder.h>
#include <string.h>

#include "debug.h"
#include "texp.h"
#include "tobj.h"

void CalcRange(HSD_TETev* tev);

int HSD_TExpSimplify(HSD_TExp* texp_)
{
    /* Redundant cast and copy (as in melee's MUST_MATCH): gives texp r31. */
    HSD_TExp* texp = (HSD_TExp*) texp_;
    int res = false;

    if (HSD_TExpGetType(texp) != HSD_TE_TEV) {
        return false;
    }
    if (SimplifySrc(texp) != 0) {
        res = true;
    }
    if (SimplifyThis(texp) != 0) {
        res = true;
    }
    if (SimplifyByMerge(texp) != 0) {
        res = true;
    }
    CalcRange(&texp->tev);
    return res;
}

