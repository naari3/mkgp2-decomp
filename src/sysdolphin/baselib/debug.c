#include "debug.h"

#include <dolphin/os.h>

/* mkgp2: only __assert/HSD_Panic remain, plus a private context saver. */

void OSFillFPUContext(OSContext* context);

OSContext HSD_DebugContext;
static PanicCallback panicCallback;

static asm void HSD_SaveContext(void)
{
    // clang-format off
    nofralloc
    mtsprg 0, r3
    lis r3, HSD_DebugContext@ha
    addi r3, r3, HSD_DebugContext@l
    stmw r0, OSContext.gpr(r3)
    mfsprg r4, 0
    stw r4, OSContext.gpr[3](r3)
    mfspr r4, GQR0
    stw r4, OSContext.gqr[0](r3)
    mfspr r4, GQR1
    stw r4, OSContext.gqr[1](r3)
    mfspr r4, GQR2
    stw r4, OSContext.gqr[2](r3)
    mfspr r4, GQR3
    stw r4, OSContext.gqr[3](r3)
    mfspr r4, GQR4
    stw r4, OSContext.gqr[4](r3)
    mfspr r4, GQR5
    stw r4, OSContext.gqr[5](r3)
    mfspr r4, GQR6
    stw r4, OSContext.gqr[6](r3)
    mfspr r4, GQR7
    stw r4, OSContext.gqr[7](r3)
    mfcr r4
    stw r4, OSContext.cr(r3)
    mflr r4
    stw r4, OSContext.lr(r3)
    mfctr r4
    stw r4, OSContext.ctr(r3)
    mfxer r4
    stw r4, OSContext.xer(r3)
    mfsrr0 r4
    stw r4, OSContext.srr0(r3)
    mfsrr1 r4
    stw r4, OSContext.srr1(r3)
    lhz r4, OSContext.state(r3)
    ori r4, r4, 1
    sth r4, OSContext.state(r3)
    b OSFillFPUContext
    // clang-format on
}

void __assert(const char* str, u32 arg1, const char* arg2)
{
    OSReport("assertion \"%s\" failed", arg2);
    HSD_Panic(str, arg1, "");
}

void HSD_Panic(const char* arg0, u32 line, const char* arg2)
{
    if (panicCallback != NULL) {
        HSD_SaveContext();
        OSReport("%s in %s on line %d.\n", arg2, arg0, line);
        panicCallback(&HSD_DebugContext);
    }
    OSPanic(arg0, line, arg2);
}
