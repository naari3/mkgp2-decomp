#include <dolphin.h>
#include <dolphin/hw_regs.h>
#include <triforce/dvdlow_private.h>
extern u32 fn_802867B8(u32, u32);

void fn_8028625C(u32 cmd, u32 offset, u32 length) {
    u32 v[11];
    u16 key = fn_802867B8(0, 0x7FFF);
    key = key * 2 + 1;
    v[0] = __DIKey->cmd;
    v[1] = __DIKey->offset;
    v[2] = __DIKey->length;
    v[0] ^= (key << 16) | cmd;
    v[1] ^= offset;
    v[2] ^= length;
    __DIKey->cmd *= key;
    __DIKey->offset *= key;
    __DIKey->length *= key;
    __DIRegs[2] = v[0];
    __DIRegs[3] = v[1];
    __DIRegs[4] = v[2];
}
