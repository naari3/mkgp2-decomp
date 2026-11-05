#include <triforce/amsrv_private.h>

s32 fn_80291314(u8 ch) {
    NetPacket* req = fn_8028CF1C(ch);
    NetPacket* rsp = fn_8028CE34(ch);
    u32* base = fn_8028D6B0();

    u32 idx = BSWAP32(req->result);

    rsp->result = BSWAP32(base[0]);
    rsp->arg[0] = BSWAP32(base[idx + 2]);
    REPLY(rsp, req);
    fn_8028D3E4(ch);
    return 1;
}

s32 fn_802913CC(u8 ch) {
    NetPacket* req = fn_8028CF1C(ch);
    NetPacket* rsp = fn_8028CE34(ch);
    u32* base = fn_8028D6B0();

    base[7] = BSWAP32(req->result);
    REPLY(rsp, req);
    fn_8028D3E4(ch);
    return 1;
}

s32 fn_8029145C(u8 ch) {
    NetPacket* req = fn_8028CF1C(ch);
    NetPacket* rsp = fn_8028CE34(ch);
    u32* base = fn_8028D6B0();
    u32 addr = base[1] + BSWAP32(req->result);

    if (addr & 3) {
        rsp->result = 0;
    } else {
        *(u32*)addr = BSWAP32(req->arg[0]);
        rsp->result = BSWAP32(base[0]);
    }
    REPLY(rsp, req);
    fn_8028D3E4(ch);
    return 1;
}

s32 fn_80291524(u8 ch) {
    NetPacket* req = fn_8028CF1C(ch);
    NetPacket* rsp = fn_8028CE34(ch);
    u32* base = fn_8028D6B0();
    u32 addr = base[1] + BSWAP32(req->result);

    if (addr & 3) {
        rsp->result = 0;
        rsp->arg[0] = 0;
    } else {
        rsp->result = BSWAP32(base[0]);
        rsp->arg[0] = BSWAP32(*(u32*)addr);
    }
    REPLY(rsp, req);
    fn_8028D3E4(ch);
    return 1;
}

s32 fn_802915F4(u8 ch) {
    NetPacket* req = fn_8028CF1C(ch);
    NetPacket* rsp = fn_8028CE34(ch);
    u32* base = fn_8028D6B0();

    base[1] = BSWAP32(req->result);
    rsp->result = BSWAP32(base[0]);
    REPLY(rsp, req);
    fn_8028D3E4(ch);
    return 1;
}

s32 fn_80291690(u8 ch) {
    NetPacket* req = fn_8028CF1C(ch);
    NetPacket* rsp = fn_8028CE34(ch);
    u32* base = fn_8028D6B0();

    *(u16*)((u8*)base + 0x18) = BSWAP16(req->flags);
    return 1;
}

s32 fn_802916E4(u8 ch) {
    NetPacket* req = fn_8028CF1C(ch);
    NetPacket* rsp = fn_8028CE34(ch);
    u32* base = fn_8028D6B0();

    *(u16*)((u8*)base + 0x18) = BSWAP16(req->flags);
    return 1;
}

s32 fn_80291738(u8 ch) {
    NetPacket* req = fn_8028CF1C(ch);
    NetPacket* rsp = fn_8028CE34(ch);

    rsp->id = req->id;
    rsp->sub = req->sub;
    rsp->flags = 0x80;
    fn_8028D3E4(ch);
    return 1;
}
