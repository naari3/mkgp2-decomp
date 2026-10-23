/* Narrow target-observed layouts; live Ghidra types unavailable. */
struct Anim5AVec { float x, y, z; };
struct Anim5AMatrix { float m[16]; };
struct Anim5ASlot {
    char pad00[8];
    unsigned char resource;
    char pad09[11];
};
struct Anim5AEffect {
    char pad00[0x14];
    Anim5ASlot slot;
    unsigned char visible;
    char pad29[0x1F];
    float matrix[12];
    char pad78[0x14];
    Anim5AVec position;
    char pad98[0x18];
    float scale;
};
extern "C" {
extern float lbl_806D5790, lbl_806D5784, lbl_806D5770;
void VfxSlot_Release(Anim5ASlot *);
void VfxSlot_BindResource(Anim5ASlot *, int);
void VfxSlot_SetMatrixSourceEnabled(Anim5ASlot *, int);
void VfxSlot_SetAnimFrame(Anim5ASlot *, float);
void VfxSlot_SetAnimSpeed(Anim5ASlot *, float);
void DbgScene_CopyMatrix3x4Transpose(float *, const Anim5AMatrix *);
void Mtx44_GetTranslation_ColMajor(Anim5AVec *, const Anim5AMatrix *);
void Effect_BindRes5Aor5B_AnimSpeed(Anim5AEffect *effect, const Anim5AMatrix *matrix, float phase) {
    if (effect) {
        if (phase < lbl_806D5790) {
            if (effect->slot.resource != 0x5A) {
                VfxSlot_Release(&effect->slot);
                VfxSlot_BindResource(&effect->slot, 0x5A);
                VfxSlot_SetMatrixSourceEnabled(&effect->slot, 1);
            }
            VfxSlot_SetAnimFrame(&effect->slot, lbl_806D5784 * phase);
            VfxSlot_SetAnimSpeed(&effect->slot, lbl_806D5770);
        } else {
            if (effect->slot.resource != 0x5B) {
                VfxSlot_Release(&effect->slot);
                VfxSlot_BindResource(&effect->slot, 0x5B);
                VfxSlot_SetMatrixSourceEnabled(&effect->slot, 1);
                VfxSlot_SetAnimSpeed(&effect->slot, lbl_806D5790);
            }
        }
        if (phase != lbl_806D5770) effect->visible = 1;
        else effect->visible = 0;
        DbgScene_CopyMatrix3x4Transpose(effect->matrix, matrix);
        Mtx44_GetTranslation_ColMajor(&effect->position, matrix);
        effect->scale = lbl_806D5790;
    }
}
}
