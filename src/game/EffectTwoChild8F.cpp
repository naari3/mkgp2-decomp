/* Narrow target-observed views; live Ghidra types were unavailable. */
struct TwoChildEffect;
struct TwoChildGroup {
    unsigned char pad00[0x10];
    TwoChildEffect *children[2];
    unsigned char pad18[0xAC];
    signed char soundHandle;
};
struct TwoChildEffect {
    unsigned char pad00[0x14];
    unsigned char slot[0x14];
    unsigned char visible;
    unsigned char pad29[0x8B];
    signed char state;
    unsigned char padB5[0x14];
    signed char cleanup;
    unsigned char padCA[2];
    TwoChildGroup group;
};
extern "C" {
TwoChildEffect *DrawEffect_SpawnDirect(void (*)(TwoChildEffect *));
void fn_800AF4F8(TwoChildEffect *);
void DrawEffect_Free(TwoChildEffect *);
void VfxSlot_BindResourceEx(void *, int, int);
void SoundMgr_StopSE_OrSpecial(int, int);

void Effect_TwoChild_Res8F_Update(TwoChildEffect *effect) {
    TwoChildGroup *group = &effect->group;
    switch (effect->state) {
    case 0:
        for (int i = 0; i < 2; ++i) {
            group->children[i] = DrawEffect_SpawnDirect(fn_800AF4F8);
            if (group->children[i]) {
                VfxSlot_BindResourceEx(group->children[i]->slot, 0x8F, 0);
                group->children[i]->visible = 0;
            }
        }
        group->soundHandle = -1;
        ++effect->state;
        break;
    case 1: break;
    }
    if (effect->cleanup) {
        DrawEffect_Free(group->children[0]);
        DrawEffect_Free(group->children[1]);
        group->children[0] = 0;
        group->children[1] = 0;
        if (group->soundHandle >= 0) {
            SoundMgr_StopSE_OrSpecial(0xBA, group->soundHandle);
            group->soundHandle = -1;
        }
        DrawEffect_Free(effect);
    }
}
}
