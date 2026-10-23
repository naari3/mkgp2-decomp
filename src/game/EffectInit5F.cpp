/* Narrow target-observed layout; live Ghidra types unavailable. */
struct Init5FEffect {
    unsigned char pad00[0x14];
    unsigned char slot[0x14];
    unsigned char visible;
    unsigned char pad29[0x8B];
    signed char state;
};
extern "C" {
void VfxSlot_BindResourceEx(void *, int, int);
void Effect_Res5F_Init(Init5FEffect *effect) {
    switch (effect->state) {
    case 0:
        VfxSlot_BindResourceEx(effect->slot, 0x5F, 0);
        effect->visible = 0;
        ++effect->state;
        break;
    case 1:
        break;
    }
}
}
