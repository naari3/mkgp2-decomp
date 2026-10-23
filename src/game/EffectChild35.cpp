/* Narrow target-observed views; live Ghidra types were unavailable. */
struct Child35Effect;
struct Child35Group {
    unsigned char pad00[0x10];
    Child35Effect *children[2];
};
struct Child35Effect {
    unsigned char pad00[0x14];
    unsigned char slot[0x14];
    unsigned char visible;
    unsigned char pad29[0x8B];
    signed char state;
    unsigned char padB5[0x14];
    signed char cleanup;
    unsigned char padCA[2];
    Child35Group group;
};
extern "C" {
Child35Effect *DrawEffect_SpawnDirect(void (*)(Child35Effect *));
void fn_800AF4F8(Child35Effect *);
void DrawEffect_Free(Child35Effect *);
void VfxSlot_BindResourceEx(void *, int, int);
void VfxSlot_BindResource(void *, int);
void VfxSlot_SetMatrixSourceEnabled(void *, int);

void Effect_TwoChild_Res35_36_Init(Child35Effect *effect) {
    int i;
    Child35Group *group = &effect->group;
    switch (effect->state) {
    case 0:
        for (i = 0; i < 2; ++i) {
            group->children[i] = DrawEffect_SpawnDirect(fn_800AF4F8);
            if (group->children[i]) {
                if (i == 0)
                    VfxSlot_BindResource(group->children[i]->slot, 0x35);
                else
                    VfxSlot_BindResourceEx(group->children[i]->slot, 0x36, 0);
                if (i == 0)
                    VfxSlot_SetMatrixSourceEnabled(group->children[i]->slot, 1);
                group->children[i]->visible = 0;
            }
        }
        ++effect->state;
        break;
    case 1: break;
    }
    if (effect->cleanup) {
        for (i = 0; i < 2; ++i) {
            DrawEffect_Free(group->children[i]);
            group->children[i] = 0;
        }
        DrawEffect_Free(effect);
    }
}
}
