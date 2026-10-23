/* Narrow target-observed field views; live Ghidra types unavailable. */
struct ClusterVec { float x,y,z; };
struct ClusterEffect;
struct ClusterGroup {
    unsigned char pad00[0x10];
    ClusterEffect *children[16];
    unsigned char pad50[0x34];
    float growth;
};
struct ClusterEffect {
    unsigned char pad00[0x10];
    int variant;
    unsigned char slot[0x14];
    unsigned char visible;
    unsigned char pad29[3];
    float alpha;
    ClusterVec color;
    unsigned char pad3C[0x50];
    ClusterVec position;
    unsigned char pad98[0x18];
    float scale;
    signed char state;
    unsigned char padB5[0x14];
    signed char cleanup;
    unsigned char padCA[2];
    ClusterGroup group;
};
extern "C" {
extern const float lbl_806D54E8,lbl_806D54E4,lbl_806D54B8,lbl_806D54D4;
extern const float lbl_806D54C8,lbl_806D54CC,lbl_806D54C4;
extern const float lbl_806D5540,lbl_806D553C,lbl_806D5544,lbl_806D5538,lbl_806D5524;
extern const float lbl_806D5508,lbl_806D54AC,lbl_806D54F8,lbl_806D551C,lbl_806D5548;
ClusterEffect *DrawEffect_SpawnDirect(void (*)(ClusterEffect *));
void fn_800AF4F8(ClusterEffect *);
void DrawEffect_Free(ClusterEffect *);
void VfxSlot_BindResourceEx(void *,int,int);
void Vec3_Copy(ClusterVec *,const ClusterVec *);
void Vec3_Subtract_DestFirst(ClusterVec *,const ClusterVec *,const ClusterVec *);
void Vec3_Add_DestFirst(ClusterVec *,const ClusterVec *,const ClusterVec *);
float Vec3_Magnitude_Wrapper(const ClusterVec *);
void Vec3_Scale(ClusterVec *,const ClusterVec *,float);
void VfxSlot_SetPositionFromVec(void *,ClusterVec);
void VfxSlot_SetRotationZ(void *,float);
void VfxSlot_SetScaleUniform(void *,float);
float Rand_RangeFloat(float,float);
void Effect_Cluster16_Update(ClusterEffect *effect) {
    int i;
    int shift;
    ClusterGroup *group=&effect->group;
    float ordinal;
    switch(effect->state) {
    case 0:
        for(int spawn=0;spawn<16;++spawn) {
            group->children[spawn]=DrawEffect_SpawnDirect(fn_800AF4F8);
            if(group->children[spawn]) {
                switch(effect->variant) {
                case 0: VfxSlot_BindResourceEx(group->children[spawn]->slot,0x8A,0); break;
                case 1: VfxSlot_BindResourceEx(group->children[spawn]->slot,0x89,0); break;
                case 2: VfxSlot_BindResourceEx(group->children[spawn]->slot,0x57,0); break;
                case 3: VfxSlot_BindResourceEx(group->children[spawn]->slot,0x58,0); break;
                }
                Vec3_Copy(&group->children[spawn]->color,&effect->color);
                Vec3_Copy(&group->children[spawn]->position,&effect->position);
            }
        }
        group->growth=lbl_806D54E8;
        ++effect->state;
    case 1:
        group->growth+=lbl_806D54E4;
        if(lbl_806D54B8<group->growth) group->growth=lbl_806D54B8;
        for(shift=0;shift<15;++shift) {
            if(group->children[15-shift] && group->children[14-shift])
                Vec3_Copy(&group->children[15-shift]->position,&group->children[14-shift]->position);
        }
        if(group->children[0]) Vec3_Copy(&group->children[0]->position,&effect->position);
        ordinal=lbl_806D54E8;
        for(i=0;i<16;++i,ordinal+=lbl_806D54B8) {
            if(group->children[i]) {
                ClusterVec delta;
                Vec3_Subtract_DestFirst(&delta,&group->children[i]->position,&effect->position);
                float magnitude=Vec3_Magnitude_Wrapper(&delta);
                float limit=lbl_806D54D4*((lbl_806D54B8+ordinal)*(effect->scale*group->growth));
                if(limit<magnitude) {
                    Vec3_Scale(&delta,&delta,lbl_806D54B8/limit);
                    Vec3_Add_DestFirst(&group->children[i]->position,&effect->position,&delta);
                }
                VfxSlot_SetPositionFromVec(group->children[i]->slot,group->children[i]->position);
                if(effect->variant==2 || effect->variant==3)
                    VfxSlot_SetRotationZ(group->children[i]->slot,lbl_806D54C4*Rand_RangeFloat(lbl_806D54C8,lbl_806D54CC));
                float scale=ordinal-lbl_806D5540;
                scale=lbl_806D553C-scale;
                scale=scale*lbl_806D5544;
                scale=lbl_806D5538*scale+lbl_806D5524;
                if(lbl_806D54B8<scale) scale=lbl_806D54B8;
                switch(effect->variant) {
                case 0: break;
                case 1: scale*=lbl_806D5508; break;
                case 2: scale*=lbl_806D54AC; break;
                case 3: scale*=lbl_806D54AC; break;
                }
                group->children[i]->scale=scale*effect->scale;
                VfxSlot_SetScaleUniform(group->children[i]->slot,group->children[i]->scale);
                float alpha=lbl_806D553C-ordinal;
                alpha=alpha*lbl_806D5544;
                alpha=lbl_806D54F8*alpha+lbl_806D551C;
                switch(effect->variant) {
                case 0: alpha*=lbl_806D5548; break;
                case 1: alpha*=lbl_806D5548; break;
                }
                group->children[i]->alpha=alpha*effect->alpha;
                group->children[i]->visible=effect->visible;
                if(effect->variant==2 || effect->variant==3)
                    Vec3_Copy(&group->children[i]->color,&effect->color);
            }
        }
        if(effect->cleanup) {
            for(i=0;i<16;++i) {
                DrawEffect_Free(group->children[i]);
                group->children[i]=0;
            }
            DrawEffect_Free(effect);
        }
        break;
    }
}
}
