#include <triforce/amjvs_internal.h>

s32 fn_8028A934(s32 node, u8 idx, s16 v) {
    u8* count = fn_80285778();
    JvsNode* nodes = fn_802857B8();
    JvsNode* n;
    JvsMgrNode* m;
    u32 used;
    s16* p;

    if (node < 1 || node > *count) {
        return 1;
    }
    n = &nodes[node];
    if (n->analogCh == 0 || idx < 1 || idx > (u32)(n->analogCh + n->extAnalog)) {
        return 1;
    }
    m = &Mgr.node[node];
    if ((m->flags & 0x10000) || m->used + 2 > 0x100) {
        return 4;
    }
    m->flags |= 0x10000;
    used = m->used;
    m->used = used + 2;
    p = (s16*)&m->buf[used];
    m->arg[16] = idx;
    m->data[16] = p;
    *p = v;
    return 0;
}
