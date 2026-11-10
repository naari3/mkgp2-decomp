/* Narrow target-observed layout; live Ghidra types unavailable. */
struct ChildPairVec { float x, y, z; };
struct ChildPairMatrix { float m[16]; };
struct ChildPairEffect {
    char pad00[0x14];
    char slot[0x14];
    unsigned char visible;
    char pad29[3];
    float alpha;
    char pad30[0x18];
    float matrix[12];
    char pad78[0x14];
    ChildPairVec position;
    char pad98[0x18];
    float scale;
    char padB4[0x28];
    ChildPairEffect *child0, *child1;
};
extern "C" {
void Mtx44_GetTranslation_ColMajor(ChildPairVec *, const ChildPairMatrix *);
void DbgScene_CopyMatrix3x4Transpose(float *, const ChildPairMatrix *);
void Vec3_Copy(ChildPairVec *, const ChildPairVec *);
float fn_800D4174(const ChildPairMatrix *);
#ifdef __MWERKS__
void VfxSlot_SetPositionFromVec(void *, ChildPairVec);
#else
/* The definition takes these structs by address; see docs/notes/port_abi.md. */
extern void VfxSlot_SetPositionFromVec(void *, ChildPairVec *);
static inline void VfxSlot_SetPositionFromVec_ByValue(void *a0, ChildPairVec a1) { VfxSlot_SetPositionFromVec(a0, &a1); }
#define VfxSlot_SetPositionFromVec VfxSlot_SetPositionFromVec_ByValue
#endif
void VfxSlot_SetScaleUniform(void *, float);
void Effect_ApplyParentToChildPair_DcDe(ChildPairEffect *effect, const ChildPairMatrix *matrix, float alpha) {
    if (effect) {
        Mtx44_GetTranslation_ColMajor(&effect->position, matrix);
        if (effect->child0) {
            DbgScene_CopyMatrix3x4Transpose(effect->child0->matrix, matrix);
            Vec3_Copy(&effect->child0->position, &effect->position);
            effect->child0->alpha = alpha;
            effect->child0->visible = 1;
        }
        if (effect->child1) {
            Vec3_Copy(&effect->child1->position, &effect->position);
            effect->child1->scale = fn_800D4174(matrix);
            effect->child1->alpha = alpha;
            effect->child1->visible = 1;
            VfxSlot_SetPositionFromVec(effect->child1->slot, effect->child1->position);
            VfxSlot_SetScaleUniform(effect->child1->slot, effect->child1->scale);
        }
    }
}
}
