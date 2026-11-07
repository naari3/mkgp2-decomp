#include <dolphin.h>
#include <dolphin/hw_regs.h>
#include <triforce/dvdlow_private.h>
extern u32 fn_802867B8(u32, u32);

static inline u32 EncodeCommand(u32 command) {
    return command ^ __DIKey->cmd;
}

void fn_8028625C(u32 cmd, u32 offset, u32 length) {
    u32 v[9]; /* size fixes the 0x50 frame */
    u16 key = fn_802867B8(0, 0x7FFF);
    key = key * 2 + 1;
    v[0] = EncodeCommand((key << 16) | cmd);
    v[1] = offset ^ __DIKey->offset;
    v[2] = length ^ __DIKey->length;
    __DIKey->cmd *= key;
    __DIKey->offset *= key;
    __DIKey->length *= key;
    __DIRegs[2] = v[0];
    __DIRegs[3] = v[1];
    __DIRegs[4] = v[2];
}
