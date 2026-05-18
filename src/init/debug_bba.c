extern unsigned char Debug_BBA;

__declspec(section ".init") void __set_debug_bba(void) {
    Debug_BBA = 1;
}

__declspec(section ".init") unsigned char __get_debug_bba(void) {
    return Debug_BBA;
}
