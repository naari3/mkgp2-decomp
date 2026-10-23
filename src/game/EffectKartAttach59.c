/* Target-observed views; live Ghidra types were unavailable. */
typedef struct AttachVec { float x, y, z; } AttachVec;
typedef struct AttachEffect {
    unsigned char pad00[0x10];
    int delayed;
    unsigned char slot[0xA];
    signed char finished;
    unsigned char pad1F[9];
    unsigned char visible;
    unsigned char pad29[0x63];
    AttachVec position;
    unsigned char pad98[0x18];
    float scale;
    signed char state;
    unsigned char padB5[0x67];
    void *kart;
    AttachVec offset;
    unsigned char pad12C[0x54];
    unsigned int timer0, timer1, timer2, timer3;
} AttachEffect;
extern const float lbl_806D5568, lbl_806D556C, lbl_806D555C;
extern void *KartDriver_GetKartRootMtx(void *);
extern void Mtx44_GetTranslation_RowMajor(AttachVec *, const void *);
extern void VfxSlot_BindResourceEx(void *, int, int);
extern void VfxSlot_SetAnimSpeed(void *, float);
extern void Vec3_Subtract_DestFirst(AttachVec *, const AttachVec *, const AttachVec *);
extern void Vec3_Add_DestFirst(AttachVec *, const AttachVec *, const AttachVec *);
extern void VfxSlot_SetAnimFrame(void *, float);
extern void DrawEffect_Free(AttachEffect *);
extern void VfxSlot_SetPositionFromVec(void *, AttachVec);
extern void VfxSlot_SetScaleUniform(void *, float);
extern unsigned char FinalLapCoinJump_CheckActiveForObject(void *);
void Effect_KartAttach_Res59_Update(AttachEffect *effect) {
    AttachVec position;
    if (effect->kart) Mtx44_GetTranslation_RowMajor(&position, KartDriver_GetKartRootMtx(effect->kart));
    switch (effect->state) {
    case 0:
        VfxSlot_BindResourceEx(effect->slot, 0x59, 0);
        VfxSlot_SetAnimSpeed(effect->slot, lbl_806D5568);
        if (effect->kart) Vec3_Subtract_DestFirst(&effect->offset, &effect->position, &position);
        effect->scale = lbl_806D556C;
        if (effect->delayed) effect->timer0 = 4;
        else effect->timer0 = 0;
        effect->visible = 0;
        ++effect->state;
    case 1:
        if (effect->timer0 == 0) {
            effect->visible = 1;
            VfxSlot_SetAnimFrame(effect->slot, lbl_806D555C);
            ++effect->state;
        }
        break;
    case 2:
        if (effect->finished == 1) {
            DrawEffect_Free(effect);
            break;
        }
        if (effect->kart) Vec3_Add_DestFirst(&effect->position, &position, &effect->offset);
        VfxSlot_SetPositionFromVec(effect->slot, effect->position);
        VfxSlot_SetScaleUniform(effect->slot, effect->scale);
        break;
    }
    if (effect->timer0) --effect->timer0;
    if (effect->timer1) --effect->timer1;
    if (effect->timer2) --effect->timer2;
    if (effect->timer3) --effect->timer3;
    if (FinalLapCoinJump_CheckActiveForObject(effect->kart)) effect->visible = 0;
    else effect->visible = 1;
}

