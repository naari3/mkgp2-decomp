/* Narrow target-observed layouts; live Ghidra types unavailable. */
struct FourSparkVec { float x,y,z; };
struct FourSparkEffect;
struct FourSparkGroup {
    char pad00[0x10]; FourSparkEffect *children[4];
    char pad20[0x30]; void *kart;
    FourSparkVec offset;
    char pad60[0x24]; float phase;
};
struct FourSparkEffect {
    char pad00[0x14]; char slot[8]; unsigned char resource;
    char pad1D[0xB]; unsigned char visible; char pad29[3]; float alpha;
    char pad30[0x5C]; FourSparkVec position;
    char pad98[8]; float rotation;
    char padA4[0xC]; float scale;
    signed char state; char padB5[0x17]; FourSparkGroup group;
};
extern "C" {
extern const float lbl_806D5770, lbl_806D5774, lbl_806D5790, lbl_806D57A0;
extern const float lbl_806D57C8, lbl_806D57D8, lbl_806D57E8, lbl_806D57EC;
extern const float lbl_806D57F0, lbl_806D57F4, lbl_806D57F8, lbl_806D57FC;
extern const float lbl_806D5800, lbl_806D5804, lbl_806D5808;
void *KartDriver_GetKartRootMtx(void *);
void Mtx44_GetTranslation_RowMajor(FourSparkVec *, const void *);
FourSparkEffect *DrawEffect_SpawnDirect(void (*)(FourSparkEffect *));
void fn_800AF4F8(FourSparkEffect *);
void DrawEffect_Free(FourSparkEffect *);
void VfxSlot_BindResourceEx(void *, int, int);
void Vec3_Subtract_DestFirst(FourSparkVec *,const FourSparkVec *,const FourSparkVec *);
void Vec3_Add_DestFirst(FourSparkVec *,const FourSparkVec *,const FourSparkVec *);
void Vec3_Copy(FourSparkVec *,const FourSparkVec *);
unsigned char FinalLapCoinJump_CheckActiveForObject(void *);
void VfxSlot_SetPositionFromVec(void *,FourSparkVec);
void VfxSlot_SetRotationZ(void *,float);
void VfxSlot_SetScaleUniform(void *,float);
void Effect_FourSpark_Res65_68_Update(FourSparkEffect *effect) {
    int i;
    FourSparkGroup *group=&effect->group;
    FourSparkVec root;
    if(group->kart) Mtx44_GetTranslation_RowMajor(&root,KartDriver_GetKartRootMtx(group->kart));
    switch(effect->state) {
    case 0:
        for(i=0;i<4;++i) {
            group->children[i]=DrawEffect_SpawnDirect(fn_800AF4F8);
            if(group->children[i]) {
                switch(i) {
                case 0: VfxSlot_BindResourceEx(group->children[i]->slot,0x68,0); break;
                case 1: VfxSlot_BindResourceEx(group->children[i]->slot,0x65,0); break;
                case 2: VfxSlot_BindResourceEx(group->children[i]->slot,0x66,0); break;
                case 3: VfxSlot_BindResourceEx(group->children[i]->slot,0x67,0); break;
                }
            }
        }
        effect->scale *= lbl_806D57EC;
        if(group->kart) Vec3_Subtract_DestFirst(&group->offset,&effect->position,&root);
        group->phase=lbl_806D5770;
        ++effect->state;
        break;
    case 1: break;
    }
    group->phase += lbl_806D5790;
    if(lbl_806D57F0 < group->phase) {
        for(i=0;i<4;++i) { DrawEffect_Free(group->children[i]); group->children[i]=0; }
        DrawEffect_Free(effect);
        return;
    }
    if(group->kart) Vec3_Add_DestFirst(&effect->position,&root,&group->offset);
    if(FinalLapCoinJump_CheckActiveForObject(group->kart)) effect->visible=0;
    else effect->visible=1;
    for(i=0;i<4;++i) {
        if(group->children[i]) {
            switch(group->children[i]->resource) {
            case 0x68: {
                float t=group->phase / lbl_806D57F4;
                if(lbl_806D5770<=t && t<=lbl_806D5790) {
                    Vec3_Copy(&group->children[i]->position,&effect->position);
                    group->children[i]->rotation=lbl_806D57F8*t;
                    group->children[i]->scale=t*effect->scale;
                    VfxSlot_SetPositionFromVec(group->children[i]->slot,group->children[i]->position);
                    VfxSlot_SetRotationZ(group->children[i]->slot,group->children[i]->rotation);
                    VfxSlot_SetScaleUniform(group->children[i]->slot,group->children[i]->scale);
                    group->children[i]->visible=effect->visible;
                } else group->children[i]->visible=0;
                break;
            }
            case 0x65: {
                float t=group->phase;
                t -= lbl_806D57F4;
                t /= lbl_806D57F4;
                if(lbl_806D5770<=t && t<=lbl_806D5790) {
                    Vec3_Copy(&group->children[i]->position,&effect->position);
                    float threshold=lbl_806D57FC;
                    group->children[i]->rotation=lbl_806D57F8*t;
                    group->children[i]->scale=effect->scale;
                    if(t<threshold) group->children[i]->scale *= t/threshold;
                    else group->children[i]->scale *= lbl_806D5790-(t-threshold)/lbl_806D5774;
                    VfxSlot_SetPositionFromVec(group->children[i]->slot,group->children[i]->position);
                    VfxSlot_SetRotationZ(group->children[i]->slot,group->children[i]->rotation);
                    VfxSlot_SetScaleUniform(group->children[i]->slot,group->children[i]->scale);
                    group->children[i]->visible=effect->visible;
                } else group->children[i]->visible=0;
                break;
            }
            case 0x66: {
                float t=(group->phase-lbl_806D5800)/lbl_806D57F4;
                if(lbl_806D5770<=t && t<=lbl_806D5790) {
                    Vec3_Copy(&group->children[i]->position,&effect->position);
                    group->children[i]->rotation=lbl_806D57A0*t;
                    group->children[i]->scale=lbl_806D5804*effect->scale;
                    VfxSlot_SetPositionFromVec(group->children[i]->slot,group->children[i]->position);
                    VfxSlot_SetRotationZ(group->children[i]->slot,group->children[i]->rotation);
                    VfxSlot_SetScaleUniform(group->children[i]->slot,group->children[i]->scale);
                    group->children[i]->visible=effect->visible;
                } else group->children[i]->visible=0;
                break;
            }
            case 0x67: {
                float t=group->phase;
                t -= lbl_806D5800;
                t /= lbl_806D5800;
                if(lbl_806D5770<=t && t<=lbl_806D5790) {
                    Vec3_Copy(&group->children[i]->position,&effect->position);
                    group->children[i]->rotation=lbl_806D5808*t;
                    float growth=lbl_806D5790+lbl_806D57C8*t;
                    growth=lbl_806D57E8*growth;
                    group->children[i]->scale=growth*effect->scale;
                    group->children[i]->alpha=lbl_806D5790-lbl_806D57D8*t;
                    VfxSlot_SetPositionFromVec(group->children[i]->slot,group->children[i]->position);
                    VfxSlot_SetRotationZ(group->children[i]->slot,group->children[i]->rotation);
                    VfxSlot_SetScaleUniform(group->children[i]->slot,group->children[i]->scale);
                    group->children[i]->visible=effect->visible;
                } else group->children[i]->visible=0;
                break;
            }
            }
        }
    }
}
}
