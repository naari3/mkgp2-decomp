#include <triforce/amjvs_internal.h>

s32 fn_8028B3D0(u8 node, u8 idx) {
    JvsCmd* c = fn_802857C8();
    s32 cur = c->cur[node];
    u32 resp;
    JvsHandler fn;

    resp = c->req[cur][node].resp[idx];
    idx = c->req[cur][node].cmd[idx];
    if ((s32)idx < 0x60 || (s32)idx > 0x7F) {
        return 0;
    }
    fn = Mgr.handler[(u8)idx - 0x60].fn;
    if (fn == NULL) {
        return 0;
    }
    return fn(node, idx, resp);
}
