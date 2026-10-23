/* Narrow target-observed layout; live Ghidra types unavailable. */
struct Init31Effect {
    unsigned char pad00[0x10];
    int variant;
    unsigned char slot[0x14];
    unsigned char visible;
    unsigned char pad29[0x8B];
    signed char state;
    unsigned char padB5[0x14];
    signed char finished;
};
extern "C" {
void VfxSlot_BindResourceEx(void *, int, int);
void DrawEffect_Free(void *);
void Effect_BindRes31or34_Init(Init31Effect *effect) {
    switch (effect->state) {
    case 0:
        if (effect->variant == 0) {
            VfxSlot_BindResourceEx(effect->slot, 0x31, 0);
        } else {
            VfxSlot_BindResourceEx(effect->slot, 0x34, 0);
        }
        effect->visible = 0;
        ++effect->state;
        break;
    case 1:
        break;
    }
    if (effect->finished) {
        DrawEffect_Free(effect);
    }
}
}
