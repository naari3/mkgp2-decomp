/* Narrow target-observed fields; live Ghidra types unavailable. */
struct MatrixSourceEffect {
    unsigned char pad00[0x14];
    unsigned char slot[0x14];
    unsigned char visible;
    unsigned char pad29[0x77];
    float rotationZ;
    unsigned char padA4[0xC];
    float scale;
    signed char state;
    unsigned char padB5[0x9B];
    float matrixPhase;
};
extern "C" {
extern const float lbl_806D555C, lbl_806D5584;
void VfxSlot_BindResource(void *, int);
void VfxSlot_SetMatrixSourceEnabled(void *, int);
void Effect_Res76_MatrixSource_Init(MatrixSourceEffect *effect) {
    switch (effect->state) {
    case 0:
        VfxSlot_BindResource(effect->slot, 0x76);
        VfxSlot_SetMatrixSourceEnabled(effect->slot, 1);
        effect->rotationZ = lbl_806D555C;
        effect->matrixPhase = lbl_806D555C;
        effect->scale = lbl_806D5584;
        effect->visible = 0;
        ++effect->state;
        break;
    case 1:
        break;
    }
}
}
