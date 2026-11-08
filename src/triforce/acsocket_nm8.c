#include "triforce/acsocket_private.h"

static inline void InitSocket(s32 i) {
    AcSock* k = SOCK(i);
    k->ready = 1;
    k->bufAddr = State.sockBase + i * State.sockStride;
}

static inline s32 InitSockets(u32* cfg) {
    s32 i;
    u32 batches;

    memset(&State, 0, sizeof(AcState));
    OSInitSemaphore(&State.sem, 1);
    State.sockBase = cfg[0];
    State.sockStride = cfg[1];
    State.unk08 = cfg[2];
    State.devBase = cfg[3];
    State.bufOff = cfg[4];
    State.bufSize = cfg[5];
    State.txOff = cfg[6];
    State.txSize = cfg[7];
    State.rxOff = cfg[8];
    State.rxSize = cfg[9];
    State.alignTx = 1;
    State.alignRx = 1;
    i = 0;
    for (batches = 16; batches != 0; --batches) {
        InitSocket(i++);
        InitSocket(i++);
        InitSocket(i++);
        InitSocket(i++);
    }
    return 0;
}

s32 fn_80293070(u32* cfg) {
    return InitSockets(cfg);
}
