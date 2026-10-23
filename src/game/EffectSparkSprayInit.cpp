/* Narrow target-observed views; live Ghidra types were unavailable. */
struct SprayInitVec3 { float x, y, z; };
struct SprayInitEffect;
struct SprayInitGroup {
    unsigned char pad00[0x10];
    SprayInitEffect *children[3];
};
struct SprayInitEffect {
    unsigned char pad00[0x10];
    int kind;
    unsigned char slot[0x14];
    unsigned char visible;
    unsigned char pad29[0x63];
    SprayInitVec3 position;
    unsigned char pad98[0x1C];
    signed char state;
    unsigned char padB5[0x14];
    signed char cleanup;
    unsigned char padCA[2];
    SprayInitGroup group;
};
extern "C" {
SprayInitEffect *DrawEffect_SpawnDirect(void (*)(SprayInitEffect *));
void fn_800AF4F8(SprayInitEffect *);
void Effect_SparkSprayCompound_Update(SprayInitEffect *);
void DrawEffect_Free(SprayInitEffect *);
void VfxSlot_BindResourceEx(void *, int, int);
void Vec3_Copy(SprayInitVec3 *, const SprayInitVec3 *);

void Effect_SparkSprayCompound_Init(SprayInitEffect *effect) {
    SprayInitGroup *group = &effect->group;
    int i;
    switch (effect->state) {
    case 0:
        for (i = 0; i < 2; ++i) {
            group->children[i] = DrawEffect_SpawnDirect(fn_800AF4F8);
            if (group->children[i]) {
                if (i == 0)
                    VfxSlot_BindResourceEx(group->children[i]->slot, 0x26, 0);
                else
                    VfxSlot_BindResourceEx(group->children[i]->slot, 0x27, 0);
                group->children[i]->visible = 0;
            }
        }
        group->children[2] = DrawEffect_SpawnDirect(Effect_SparkSprayCompound_Update);
        if (group->children[2]) {
            Vec3_Copy(&group->children[2]->position, &effect->position);
            group->children[2]->kind = 1;
        }
        ++effect->state;
        break;
    case 1: break;
    }
    if (effect->cleanup) {
        DrawEffect_Free(group->children[0]);
        DrawEffect_Free(group->children[1]);
        DrawEffect_Free(group->children[2]);
        group->children[0] = 0;
        group->children[1] = 0;
        group->children[2] = 0;
        DrawEffect_Free(effect);
    }
}
}
