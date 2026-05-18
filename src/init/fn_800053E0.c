extern void OSResetSystem(int reset, unsigned long reset_code, int force_menu);

__declspec(section ".init") void OSResetSystem_NoArgs(void) {
    OSResetSystem(0, 0, 0);
}
