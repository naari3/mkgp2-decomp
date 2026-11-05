#include <triforce/amsrv_private.h>

static NetLinkA LinkA;
static NetLinkB LinkB;

s32 fn_80290ED8(void) {
    NetLinkA* l = &LinkA;
    OSSemaphore* sem;

    if (l->ready == 0) {
        return -2;
    }
    sem = &l->sem;
    OSWaitSemaphore(sem);
    l->ready = 0;
    l->unk30 = 0;
    l->result = 0;
    OSSignalSemaphore(sem);
    l->busy = 1;
    l->result = fn_8028F45C();
    OSWaitSemaphore(sem);
    l->ready = 1;
    OSSignalSemaphore(sem);
    return l->result;
}

s32 fn_80290F70(u32* cfg) {
    memset(&LinkA, 0, 0x3C);
    OSInitSemaphore(&LinkA.sem, 1);
    LinkA.cfg[0] = cfg[0];
    LinkA.cfg[1] = cfg[1];
    LinkA.cfg[2] = cfg[2];
    LinkA.cfg[3] = cfg[3];
    LinkA.cfg[4] = cfg[4];
    LinkA.cfg[5] = cfg[5];
    LinkA.unk18 = 1;
    LinkA.unk1C = 1;
    LinkA.ready = 1;
    LinkA.cfg0 = cfg[0];
    return 0;
}

s32 fn_80291010(u32* cfg) {
    memset(&LinkB, 0, 0x30);
    OSInitSemaphore(&LinkB.sem, 1);
    LinkB.cfg0 = cfg[0];
    LinkB.cfg1 = cfg[1];
    LinkB.cfg2 = cfg[2];
    LinkB.cfg3 = cfg[3];
    LinkB.ready = 1;
    LinkB.cfg0b = cfg[0];
    return 0;
}

s32 fn_80291098(u8 ch) {
    NetPacket* req = fn_8028CF1C(ch);
    NetPacket* rsp = fn_8028CE34(ch);
    u32* base = fn_8028D6B0();

    base[9] = BSWAP32(req->result);
    base[10] = BSWAP32(req->arg[0]);
    REPLY(rsp, req);
    fn_8028D3E4(ch);
    return 1;
}
