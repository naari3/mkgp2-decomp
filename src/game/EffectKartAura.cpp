/* Native draft for the aura parent and its six independently owned children. */
struct AuraVec { float x, y, z; };
struct AuraEffect;
struct AuraGroup {
    char pad00[0x10];
    AuraEffect* children[6];
    char pad28[0x28];
    void* kart;
    char pad54[0x30];
    float phase;
    char pad88[0x3c];
    signed char mode;
};
struct AuraEffect {
    char pad00[0x14];
    char slot[0x14];
    unsigned char visible;
    char pad29[3];
    float opacity;
    char pad30[0x5c];
    AuraVec position;
    char pad98[0xc];
    AuraVec velocity;
    float scale;
    signed char state;
    char padb5[0x14];
    signed char cleanup;
    char padca[2];
    union {
        AuraGroup group;
        struct {
            char padcc[0x50];
            void* kart;
            AuraVec previous;
            AuraVec current;
        } child;
    } payload;
};
extern "C" {
extern const float lbl_806D5494, lbl_806D5400, lbl_806D546C, lbl_806D5420, lbl_806D5454;
void VfxSlot_BindResourceEx(void*, unsigned char, int);
void Vec3_Subtract_DestFirst(AuraVec*, const AuraVec*, const AuraVec*);
void Vec3_Add_DestFirst(AuraVec*, const AuraVec*, const AuraVec*);
void Vec3_Copy(AuraVec*, const AuraVec*);
void Vec3_Scale(AuraVec*, const AuraVec*, float);
void* KartDriver_GetKartRootMtx(void*);
void Mtx44_GetTranslation_RowMajor(AuraVec*, const void*);
void DrawEffect_Free(AuraEffect*);
AuraEffect* DrawEffect_SpawnDirect(void (*)(AuraEffect*));
void VfxSlot_SetPositionFromVec(void*, const AuraVec*);
void VfxSlot_SetScaleUniform(void*, float);

void Effect_KartAuraChild_Update(AuraEffect* effect);
#ifndef AURA_PARENT_ONLY
void Effect_KartAuraChild_Update(AuraEffect* effect) {
    switch (effect->state) {
    case 0:
        VfxSlot_BindResourceEx(effect->slot, 0x49, 0);
        effect->visible = 0;
        ++effect->state;
    case 1:
        if (effect->cleanup) {
            Vec3_Subtract_DestFirst(&effect->velocity, &effect->payload.child.current, &effect->payload.child.previous);
            if (effect->payload.child.kart)
                Mtx44_GetTranslation_RowMajor(&effect->payload.child.previous, KartDriver_GetKartRootMtx(effect->payload.child.kart));
            ++effect->state;
        }
        break;
    case 2:
        effect->opacity -= lbl_806D5494;
        if (effect->opacity < lbl_806D5400) {
            DrawEffect_Free(effect);
            break;
        }
        Vec3_Scale(&effect->velocity, &effect->velocity, lbl_806D546C);
        effect->velocity.y = lbl_806D5420;
        effect->scale += lbl_806D5454;
        if (effect->payload.child.kart) {
            AuraVec translation;
            AuraVec delta;
            Mtx44_GetTranslation_RowMajor(&translation, KartDriver_GetKartRootMtx(effect->payload.child.kart));
            Vec3_Subtract_DestFirst(&delta, &translation, &effect->payload.child.previous);
            Vec3_Add_DestFirst(&effect->position, &effect->position, &delta);
            Vec3_Copy(&effect->payload.child.previous, &translation);
        }
        Vec3_Add_DestFirst(&effect->position, &effect->position, &effect->velocity);
        AuraVec position = effect->position;
        VfxSlot_SetPositionFromVec(effect->slot, &position);
        VfxSlot_SetScaleUniform(effect->slot, effect->scale);
        break;
    }
}

#else
void Effect_KartAuraCompound_Update(AuraEffect* effect) {
    AuraGroup* group = &effect->payload.group;
    int freeIndex;
    switch (effect->state) {
    case 0:
        for (int i = 0; i < 6; ++i) {
            group->children[i] = DrawEffect_SpawnDirect(Effect_KartAuraChild_Update);
            if (group->children[i])
                Vec3_Copy(&group->children[i]->position, &effect->position);
        }
        group->mode = 0;
        group->phase = lbl_806D5400;
        ++effect->state;
    case 1:
        switch (effect->cleanup) {
        case 1:
        {
            AuraEffect* empty = 0;
            signed char detach = 1;
            for (int i = 0; i < 6; ++i) {
                if (group->children[i]) {
                    group->children[i]->payload.child.kart = group->kart;
                    group->children[i]->cleanup = detach;
                    group->children[i] = empty;
                }
            }
            DrawEffect_Free(effect);
            break;
        }
        case 2:
            for (freeIndex = 0; freeIndex < 6; ++freeIndex) {
                DrawEffect_Free(group->children[freeIndex]);
                group->children[freeIndex] = 0;
            }
            DrawEffect_Free(effect);
            break;
        }
        break;
    }
}
#endif
}
