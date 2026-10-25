extern void OSResetSystem(int reset, unsigned long reset_code, int force_menu);

__declspec(section ".init") void __TRK_reset(void) {
    OSResetSystem(0, 0, 0);
}
