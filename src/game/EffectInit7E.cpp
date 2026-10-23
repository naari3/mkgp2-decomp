/* Narrow target-observed layout; live Ghidra types unavailable. */
struct Init7ESlot {
    unsigned char pad00[0x14];
    unsigned char visible;
    unsigned char pad15[0x8B];
};
struct Init7EEffect {
    unsigned char pad00[0x10];
    int variant;
    Init7ESlot slot;
    signed char state;
    unsigned char padB5[0x9B];
    float growth;
};
extern "C" {
extern const float lbl_806D55E4, lbl_806D5584, lbl_806D555C;
void VfxSlot_BindResourceEx(void *, int, int);
void VfxSlot_SetAnimSpeed(void *, float);
void Effect_Res7Eor62_Variant_Init(Init7EEffect *effect) {
    switch (effect->state) {
    case 0:
        if (effect->variant == 0) {
            VfxSlot_BindResourceEx(&effect->slot, 0x7E, 0);
            VfxSlot_SetAnimSpeed(&effect->slot, lbl_806D55E4);
        } else {
            VfxSlot_BindResourceEx(&effect->slot, 0x62, 0);
            VfxSlot_SetAnimSpeed(&effect->slot, lbl_806D5584);
        }
        effect->slot.visible = 0;
        effect->growth = lbl_806D555C;
        ++effect->state;
        break;
    case 1:
        break;
    }
}
}
