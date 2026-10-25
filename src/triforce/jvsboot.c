/* Triforce JVS I/O bring-up run once after the HSD/zlib libraries. */
#include <dolphin.h>

void fn_80282F3C(void);
void fn_80285638(u8 node);
BOOL fn_80285048(u8* str);
BOOL fn_80284480(u8 len, u8* data, u8 rlen);
BOOL fn_802854B0(void);
BOOL fn_80282EB8(void);
void fn_80282E60(void);

void fn_802E5380(void) {
    fn_80282F3C();
    fn_80285638(1);
    fn_80285048((u8*)"namco ltd.;GC-AM BASE PCB;Ver1.00;JPN,TRIFORCE");
    {
        u8 cmd[6] = { 0x70, 0x18, 0x50, 0x4C, 0x14, 0xFE };
        fn_80284480(6, cmd, 2);
    }
    fn_802854B0();
    fn_80282EB8();
    fn_80282E60();
    VIWaitForRetrace();
}
