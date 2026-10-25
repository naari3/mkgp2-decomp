/* Triforce AM baseboard access over EXI. */
#include <dolphin.h>
#include <dolphin/exi.h>

static OSSemaphore Sem;
static s32 DmaChan;

static void WriteDmaCallback(s32 chan, OSContext* context);
static void ReadDmaCallback(s32 chan, OSContext* context);

static u32 AddCheck(u32 cmd) {
    u32 v = cmd;
    u32 bit;
    u32 poly;

    for (poly = 0x8D800000, bit = 0x80000000; bit >= 0x100; bit >>= 1, poly >>= 1) {
        if (v & bit) {
            v ^= poly;
        }
    }
    return (cmd & 0xFFFFFF00) | (v & 0xFF);
}

BOOL fn_80286B80(s32 chan) {
    if (EXIDetach(chan) != TRUE) {
        OSReport("exi_disconnect > EXIDetach function is error!\n");
        return FALSE;
    }
    OSReport("exi_disconnect > completed.\n");
    return TRUE;
}

BOOL fn_80286BD4(s32 chan, u32 dev) {
    u32 id;

    if (!EXIGetID(chan, dev, &id)) {
        OSReport("exi_connect2 > EXIGetID function is error!\n");
        return FALSE;
    }
    if (id != 0x06041000) {
        OSReport("exi_connect2 > ID is different from GC-AM BASE PCB ID!\n");
        return FALSE;
    }
    OSInitSemaphore(&Sem, 1);
    return TRUE;
}

BOOL fn_80286C54(s32 chan, u32 dev, u16 addr, u8 data) {
    BOOL err = FALSE;
    u32 status;
    u32 cmd1;
    u32 cmd2;

    OSWaitSemaphore(&Sem);
    if (EXILock(chan, dev, NULL)) {
        if (EXISelect(chan, dev, EXI_FREQ_16M)) {
            cmd1 = AddCheck(0x01000000 | (addr << 8));
            err |= !EXIImm(chan, &cmd1, 4, EXI_WRITE, NULL);
            err |= !EXISync(chan);
            err |= !EXIImm(chan, &status, 1, EXI_READ, NULL);
            err |= !EXISync(chan);
            err |= !EXIDeselect(chan);
        }
        EXIUnlock(chan);
    }
    if (((status >> 24) & 0xF) != 1) {
        err = TRUE;
    }
    if (!err && EXILock(chan, dev, NULL)) {
        if (EXISelect(chan, dev, EXI_FREQ_16M)) {
            cmd2 = AddCheck(0x02000000 | (data << 16));
            err |= !EXIImm(chan, &cmd2, 4, EXI_WRITE, NULL);
            err |= !EXISync(chan);
            err |= !EXIImm(chan, &status, 1, EXI_READ, NULL);
            err |= !EXISync(chan);
            err |= !EXIDeselect(chan);
        }
        EXIUnlock(chan);
    }
    if (((status >> 24) & 0xF) != 1) {
        err = TRUE;
    }
    OSSignalSemaphore(&Sem);
    return !err;
}

BOOL fn_80286E78(s32 chan, u32 dev, u16 addr, u8* data) {
    BOOL err = FALSE;
    u32 status;
    u32 cmd1;
    u32 cmd2;

    OSWaitSemaphore(&Sem);
    if (EXILock(chan, dev, NULL)) {
        if (EXISelect(chan, dev, EXI_FREQ_16M)) {
            cmd1 = AddCheck(0x01000000 | (addr << 8));
            err |= !EXIImm(chan, &cmd1, 4, EXI_WRITE, NULL);
            err |= !EXISync(chan);
            err |= !EXIImm(chan, &status, 1, EXI_READ, NULL);
            err |= !EXISync(chan);
            err |= !EXIDeselect(chan);
        }
        EXIUnlock(chan);
    }
    if (((status >> 24) & 0xF) != 1) {
        err = TRUE;
    }
    if (!err && EXILock(chan, dev, NULL)) {
        if (EXISelect(chan, dev, EXI_FREQ_16M)) {
            cmd2 = AddCheck(0x03000000);
            err |= !EXIImm(chan, &cmd2, 4, EXI_WRITE, NULL);
            err |= !EXISync(chan);
            err |= !EXIImm(chan, &status, 2, EXI_READ, NULL);
            err |= !EXISync(chan);
            err |= !EXIDeselect(chan);
        }
        EXIUnlock(chan);
    }
    *data = status >> 16;
    if (((status >> 24) & 0xF) != 1) {
        err = TRUE;
    }
    OSSignalSemaphore(&Sem);
    return !err;
}

BOOL fn_802870A4(s32 chan, u32 dev, u16 addr, void* buf, u32 len, BOOL sync) {
    BOOL err = FALSE;
    u32 status;
    u32 cmd1;
    u32 cmd2;

    OSWaitSemaphore(&Sem);
    if (EXILock(chan, dev, NULL)) {
        if (EXISelect(chan, dev, EXI_FREQ_16M)) {
            cmd1 = AddCheck(0x01000000 | (addr << 8));
            err |= !EXIImm(chan, &cmd1, 4, EXI_WRITE, NULL);
            err |= !EXISync(chan);
            err |= !EXIImm(chan, &status, 1, EXI_READ, NULL);
            err |= !EXISync(chan);
            err |= !EXIDeselect(chan);
        }
        EXIUnlock(chan);
    }
    if (((status >> 24) & 0xF) != 1) {
        err = TRUE;
    }
    if (!err && EXILock(chan, dev, NULL)) {
        if (EXISelect(chan, dev, EXI_FREQ_16M)) {
            cmd2 = AddCheck(0x05000000);
            err |= !EXIImm(chan, &cmd2, 4, EXI_WRITE, NULL);
            err |= !EXISync(chan);
            err |= !EXIImm(chan, &status, 1, EXI_READ, NULL);
            err |= !EXISync(chan);
            if (((status >> 24) & 0xF) != 1) {
                err = TRUE;
            } else {
                DCStoreRange(buf, len);
                if (sync) {
                    err |= !EXIDma(chan, buf, len, EXI_WRITE, NULL);
                    err |= !EXISync(chan);
                    err |= !EXIImm(chan, &status, 1, EXI_READ, NULL);
                    err |= !EXISync(chan);
                } else {
                    DmaChan = chan;
                    err |= !EXIDma(chan, buf, len, EXI_WRITE, WriteDmaCallback);
                    return !err;
                }
            }
            err |= !EXIDeselect(chan);
        } else {
            err = TRUE;
        }
        EXIUnlock(chan);
    } else {
        err = TRUE;
    }
    OSSignalSemaphore(&Sem);
    return !err;
}

BOOL fn_802873A0(s32 chan, u32 dev, u16 addr, void* buf, u32 len, BOOL sync) {
    BOOL err = FALSE;
    u32 status;
    u32 cmd1;
    u32 cmd2;

    OSWaitSemaphore(&Sem);
    if (EXILock(chan, dev, NULL)) {
        if (EXISelect(chan, dev, EXI_FREQ_16M)) {
            cmd1 = AddCheck(0x01000000 | (addr << 8));
            err |= !EXIImm(chan, &cmd1, 4, EXI_WRITE, NULL);
            err |= !EXISync(chan);
            err |= !EXIImm(chan, &status, 1, EXI_READ, NULL);
            err |= !EXISync(chan);
            err |= !EXIDeselect(chan);
        }
        EXIUnlock(chan);
    }
    if (((status >> 24) & 0xF) != 1) {
        err = TRUE;
    }
    if (!err && EXILock(chan, dev, NULL)) {
        if (EXISelect(chan, dev, EXI_FREQ_16M)) {
            cmd2 = AddCheck(0x03000000);
            err |= !EXIImm(chan, &cmd2, 4, EXI_WRITE, NULL);
            err |= !EXISync(chan);
            err |= !EXIImm(chan, &status, 1, EXI_READ, NULL);
            err |= !EXISync(chan);
            if (((status >> 24) & 0xF) != 1) {
                err = TRUE;
            } else {
                DCInvalidateRange(buf, len);
                if (sync) {
                    err |= !EXIDma(chan, buf, len, EXI_READ, NULL);
                    err |= !EXISync(chan);
                } else {
                    DmaChan = chan;
                    err |= !EXIDma(chan, buf, len, EXI_READ, ReadDmaCallback);
                    return !err;
                }
            }
            err |= !EXIDeselect(chan);
        } else {
            err = TRUE;
        }
        EXIUnlock(chan);
    } else {
        err = TRUE;
    }
    OSSignalSemaphore(&Sem);
    return !err;
}

static void WriteDmaCallback(s32 chan, OSContext* context) {
    u32 status;

    EXIImm(DmaChan, &status, 1, EXI_READ, NULL);
    EXISync(DmaChan);
    EXIDeselect(DmaChan);
    EXIUnlock(DmaChan);
    OSSignalSemaphore(&Sem);
}

static void ReadDmaCallback(s32 chan, OSContext* context) {
    EXIDeselect(DmaChan);
    EXIUnlock(DmaChan);
    OSSignalSemaphore(&Sem);
}

void fn_802876F4(s32 chan) {
    while (EXIGetState(chan) & ~8) {
    }
}

BOOL fn_8028772C(s32 chan, u32 dev, u16* data) {
    BOOL err = FALSE;
    u32 cmd = AddCheck(0x82000000);
    u8 status;

    OSWaitSemaphore(&Sem);
    if (EXILock(chan, dev, NULL)) {
        if (EXISelect(chan, dev, EXI_FREQ_16M)) {
            err |= !EXIImm(chan, &cmd, 4, EXI_WRITE, NULL);
            err |= !EXISync(chan);
            err |= !EXIImm(chan, &status, 1, EXI_READ, NULL);
            err |= !EXISync(chan);
            if (status != 4) {
                err = TRUE;
            } else {
                err |= !EXIImmEx(chan, data, 2, EXI_READ);
                err |= !EXISync(chan);
            }
            err |= !EXIDeselect(chan);
        } else {
            err = TRUE;
        }
        err |= !EXIUnlock(chan);
    } else {
        err = TRUE;
    }
    OSSignalSemaphore(&Sem);
    return !err;
}

BOOL fn_802878B4(s32 chan, u32 dev, u16 data) {
    BOOL err = FALSE;
    u32 cmd = AddCheck(0x83000000 | (data << 8));
    u8 status;

    OSWaitSemaphore(&Sem);
    if (EXILock(chan, dev, NULL)) {
        if (EXISelect(chan, dev, EXI_FREQ_16M)) {
            err |= !EXIImm(chan, &cmd, 4, EXI_WRITE, NULL);
            err |= !EXISync(chan);
            err |= !EXIImm(chan, &status, 1, EXI_READ, NULL);
            err |= !EXISync(chan);
            if (status != 4) {
                err = TRUE;
            }
            err |= !EXIDeselect(chan);
        } else {
            err = TRUE;
        }
        err |= !EXIUnlock(chan);
    } else {
        err = TRUE;
    }
    OSSignalSemaphore(&Sem);
    return !err;
}

BOOL fn_802879FC(s32 chan, u32 dev, u16 data) {
    BOOL err = FALSE;
    u32 cmd = AddCheck(0x87000000 | (data << 8));
    u8 status;

    OSWaitSemaphore(&Sem);
    if (EXILock(chan, dev, NULL)) {
        if (EXISelect(chan, dev, EXI_FREQ_16M)) {
            err |= !EXIImm(chan, &cmd, 4, EXI_WRITE, NULL);
            err |= !EXISync(chan);
            err |= !EXIImm(chan, &status, 1, EXI_READ, NULL);
            err |= !EXISync(chan);
            if (status != 4) {
                err = TRUE;
            }
            err |= !EXIDeselect(chan);
        } else {
            err = TRUE;
        }
        err |= !EXIUnlock(chan);
    } else {
        err = TRUE;
    }
    OSSignalSemaphore(&Sem);
    return !err;
}

BOOL fn_80287B44(s32 chan, u32 dev, u16* data) {
    BOOL err = FALSE;
    u32 cmd = AddCheck(0x86000000);
    u8 status;

    OSWaitSemaphore(&Sem);
    if (EXILock(chan, dev, NULL)) {
        if (EXISelect(chan, dev, EXI_FREQ_16M)) {
            err |= !EXIImm(chan, &cmd, 4, EXI_WRITE, NULL);
            err |= !EXISync(chan);
            err |= !EXIImm(chan, &status, 1, EXI_READ, NULL);
            err |= !EXISync(chan);
            if (status != 4) {
                err = TRUE;
            } else {
                err |= !EXIImmEx(chan, data, 2, EXI_READ);
                err |= !EXISync(chan);
            }
            err |= !EXIDeselect(chan);
        } else {
            err = TRUE;
        }
        err |= !EXIUnlock(chan);
    } else {
        err = TRUE;
    }
    OSSignalSemaphore(&Sem);
    return !err;
}

BOOL fn_80287CCC(s32 chan, u32 dev, u16 data) {
    BOOL err = FALSE;
    u32 cmd = AddCheck(0xFF000000 | (data << 8));
    u8 status;

    OSWaitSemaphore(&Sem);
    if (EXILock(chan, dev, NULL)) {
        if (EXISelect(chan, dev, EXI_FREQ_16M)) {
            err |= !EXIImm(chan, &cmd, 4, EXI_WRITE, NULL);
            err |= !EXISync(chan);
            err |= !EXIImm(chan, &status, 1, EXI_READ, NULL);
            err |= !EXISync(chan);
            if (status != 4) {
                err = TRUE;
            }
            err |= !EXIDeselect(chan);
        } else {
            err = TRUE;
        }
        err |= !EXIUnlock(chan);
    } else {
        err = TRUE;
    }
    OSSignalSemaphore(&Sem);
    return !err;
}

void fn_80287E14(s32 chan, EXICallback callback) {
    EXISetExiCallback(chan, callback);
}
