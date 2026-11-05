#include <triforce/amjvs_internal.h>

void fn_8028B180(BOOL filter) {
    JvsMgr* m;
    OSSemaphore* sem = &Mgr.sem;
    JvsStats* st;
    JvsEvent ev;
    u32 i;
    s32 n;

    OSWaitSemaphore(sem);
    for (i = 0; i < 16; i++) {
        Mgr.node[i].err.count = 0;
    }
    m = &Mgr;
    if (fn_80283E3C() != 0) {
        for (n = fn_80283E3C(); n > 0; n--) {
            ev = fn_80283E54();
            if (!filter || !((ev.node == 0 && ev.cmd == 0xF0 && (ev.err & 8)) ||
                             (ev.node == 0 && ev.cmd == 0xF1 && (ev.err & 8)) || (ev.cmd == 0x15 && (ev.err & 0x40))))
            {
                st = &Mgr.node[ev.node].err;
                st->total++;
                st->count++;
            }
        }
    }
    for (i = 0; i < 16; i++, m = (JvsMgr*)((u8*)m + sizeof(JvsMgrNode))) {
        st = &m->node[0].err;
        if (m->node[0].err.count > 0) {
            st->runs++;
            st->streak++;
        } else {
            st->streak = 0;
        }
    }
    OSSignalSemaphore(sem);
}
