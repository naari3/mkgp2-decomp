#include <triforce/amsrv_private.h>

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
    REPLY(rsp, req);
    fn_8028D3E4(ch);
    return 1;
}

/* Matches with opt_common_subs off; the reply header is spelled out so the
 * flag word still goes through one byte-reversed store. */
#pragma opt_common_subs off
s32 fn_8029121C(u8 ch) {
    NetPacket* req = fn_8028CF1C(ch);
    NetPacket* rsp = fn_8028CE34(ch);
    u32* base = fn_8028D6B0();
    u32 addr = base[1] + BSWAP32(req->result);
    u32* p = (u32*)(addr & ~3);

    rsp->result = BSWAP32(p[0]);
    rsp->arg[0] = BSWAP32(p[1]);
    rsp->arg[1] = BSWAP32(p[2]);
    rsp->arg[2] = BSWAP32(p[3]);
    rsp->arg[3] = BSWAP32(p[4]);
    rsp->arg[4] = BSWAP32(p[5]);
    rsp->arg[5] = BSWAP32(p[6]);
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
