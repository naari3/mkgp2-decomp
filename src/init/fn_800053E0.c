extern void OSResetSystem(int reset, unsigned long reset_code, int force_menu);

__declspec(section ".init") void fn_800053E0(void) {
    OSResetSystem(0, 0, 0);
}
