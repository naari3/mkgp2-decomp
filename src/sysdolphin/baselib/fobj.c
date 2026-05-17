#include "sysdolphin/baselib/fobj.h"

static inline unsigned int HSD_FObjSetState(HSD_FObj* fobj, unsigned int state)
{
    if (fobj) {
        fobj->flags = (state & 0xF) | (fobj->flags & 0xF0);
    }
    return state;
}

static inline void HSD_FObjReqAnim(HSD_FObj* fobj, float startframe)
{
    if (fobj == 0) {
        return;
    }
    fobj->ad = fobj->ad_head;
    fobj->time = (float)fobj->startframe + startframe;
    fobj->op = 0;
    fobj->op_intrp = 0;
    fobj->flags &= ~0x40;
    fobj->nb_pack = 0;
    fobj->fterm = 0;
    fobj->p0 = 0.0f;
    fobj->p1 = 0.0f;
    fobj->d0 = 0.0f;
    fobj->d1 = 0.0f;
    HSD_FObjSetState(fobj, 1);
}

void HSD_FObjReqAnimAll(HSD_FObj* fobj, float startframe)
{
    HSD_FObj* fp;
    if (fobj == 0) {
        return;
    }
    for (fp = fobj; fp != 0; fp = fp->next) {
        HSD_FObjReqAnim(fp, startframe);
    }
}
