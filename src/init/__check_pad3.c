extern void OSResetSystem(int reset, unsigned long reset_code, int force_menu);

__declspec(section ".init") void __check_pad3(void) {
    if ((*(volatile unsigned short *)0x800030E4 & 0xEEF) == 0xEEF) {
        OSResetSystem(0, 0, 0);
    }
}
