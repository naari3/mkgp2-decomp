/* Narrow target-observed views; live Ghidra types were unavailable. */
struct Child3CEffect;
struct Child3CGroup {
    unsigned char pad00[0x10];
    Child3CEffect *children[2];
    unsigned char pad18[0x6C];
    float phase;
    float rotation;
    unsigned char pad8C[0x38];
    unsigned char flag;
};
struct Child3CEffect {
    unsigned char pad00[0x14];
    unsigned char slot[0x14];
    unsigned char visible;
    unsigned char pad29[0x8B];
    signed char state;
    unsigned char padB5[0x14];
    signed char cleanup;
    unsigned char padCA[2];
    Child3CGroup group;
};
extern "C" {
extern const float lbl_806D5770;
Child3CEffect *DrawEffect_SpawnDirect(void (*)(Child3CEffect *));
void fn_800AF4F8(Child3CEffect *);
void DrawEffect_Free(Child3CEffect *);
void VfxSlot_BindResourceEx(void *, int, int);

void Effect_TwoChild_Res3C_3D_Init(Child3CEffect *effect) {
    Child3CGroup *group = &effect->group;
    int i;
    switch (effect->state) {
    case 0:
        for (i = 0; i < 2; ++i) {
            group->children[i] = DrawEffect_SpawnDirect(fn_800AF4F8);
            if (group->children[i]) {
                if (i == 0)
                    VfxSlot_BindResourceEx(group->children[i]->slot, 0x3C, 0);
                else
                    VfxSlot_BindResourceEx(group->children[i]->slot, 0x3D, 0);
                group->children[i]->visible = 0;
            }
        }
        group->phase = lbl_806D5770;
        group->rotation = lbl_806D5770;
        group->flag = 0;
        ++effect->state;
        break;
    case 1: break;
    }
    if (effect->cleanup) {
        DrawEffect_Free(group->children[0]);
        DrawEffect_Free(group->children[1]);
        group->children[0] = 0;
        group->children[1] = 0;
        DrawEffect_Free(effect);
    }
}
}
