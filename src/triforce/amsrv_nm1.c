#include <triforce/amsrv_private.h>

/* opt_common_subs off and the spelled-out reply header take this from 62 to
 * 16 diff lines; the result/arg[0] loads still swap r5/r6. */
#pragma opt_common_subs off
s32 fn_80291134(u8 ch) {
    NetPacket* req = fn_8028CF1C(ch);
    NetPacket* rsp = fn_8028CE34(ch);
    u32* base = fn_8028D6B0();
    u32 addr = base[1] + BSWAP32(req->result);
    u32* p = (u32*)(addr & ~3);

    p[0] = BSWAP32(req->arg[0]);
    p[1] = BSWAP32(req->arg[1]);
    p[2] = BSWAP32(req->arg[2]);
    p[3] = BSWAP32(req->arg[3]);
    p[4] = BSWAP32(req->arg[4]);
    p[5] = BSWAP32(req->arg[5]);
    {
        u32 fl;
        rsp->id = req->id;
        rsp->sub = req->sub;
        fl = BSWAP16(req->flags) | 0x8000;
        rsp->flags = BSWAP16(fl);
    }
    fn_8028D3E4(ch);
    return 1;
}

#pragma opt_common_subs reset
