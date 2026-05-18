/*
 * InitRumbleController @ 0x80169D60 (size 0x90).
 *
 * Lazy-init for the global rumble controller state buffer (`lbl_806D15B0`,
 * .sbss). On first call, allocates a 0x20 byte buffer via Alloc(), stores
 * the device id at +0, and zero-initialises the remaining 0x1F bytes in
 * a fixed mixed byte/word store order (matches the dtk-extracted target
 * asm). Returns 1 if the buffer is (now) non-NULL, otherwise 0.
 *
 * Singleton dtk reversed-extab group `auto_InitRumbleController_text` --
 * the function has an extab/extabindex entry (Large-Frame flag, saved
 * GPR range r31). #pragma exceptions on/reset wraps the function so CW
 * auto-emits the extab/extabindex entry (same pattern as AI_GetYaw.c,
 * GetCourseSectionType.c).
 */

extern unsigned char *lbl_806D15B0;
extern void *Alloc(int size);

#pragma exceptions on
int InitRumbleController(int deviceId) {
    unsigned char *p;
    if (lbl_806D15B0 == 0) {
        p = (unsigned char *)Alloc(0x20);
        if (p != 0) {
            p[0]                  = (unsigned char)deviceId;
            p[1]                  = 0;
            p[3]                  = 0;
            *(unsigned int *)(p + 0x8)  = 0;
            *(unsigned int *)(p + 0x10) = 0;
            *(unsigned int *)(p + 0x18) = 0;
            p[2]                  = 0;
            p[4]                  = 0;
            *(unsigned int *)(p + 0xc)  = 0;
            *(unsigned int *)(p + 0x14) = 0;
            *(unsigned int *)(p + 0x1c) = 0;
        }
        lbl_806D15B0 = p;
    }
    if (lbl_806D15B0 != 0) return 1;
    return 0;
}
#pragma exceptions reset
