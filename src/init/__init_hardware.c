extern void __OSPSInit(void);
extern void __OSFPRInit(void);
extern void __OSCacheInit(void);

__declspec(section ".init") asm void __init_hardware(void) {
    nofralloc
    mfmsr r0
    ori r0, r0, 0x2000
    mtmsr r0
    mflr r31
    bl __OSPSInit
    bl __OSFPRInit
    bl __OSCacheInit
    mtlr r31
    blr
}
