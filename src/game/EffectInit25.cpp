/* Narrow target-observed layout; live Ghidra types unavailable. */
struct Init25Effect {
    unsigned char pad00[0x14];
    unsigned char slot[0x14];
    unsigned char visible;
    unsigned char pad29[0x8B];
    signed char state;
    unsigned char padB5[0x14];
    signed char finished;
    unsigned char padCA[0x86];
    float matrixPhase;
};
extern "C" {
extern const float lbl_806D5770;
void VfxSlot_BindResource(void *, int);
void VfxSlot_SetMatrixSourceEnabled(void *, int);
void DrawEffect_Free(void *);
void Effect_BindRes25_Init(Init25Effect *effect) {
    switch (effect->state) {
    case 0:
        VfxSlot_BindResource(effect->slot, 0x25);
        VfxSlot_SetMatrixSourceEnabled(effect->slot, 1);
        effect->matrixPhase = lbl_806D5770;
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
