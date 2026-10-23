/* Narrow target-observed layout; live Ghidra types unavailable in this worker. */
struct CoinJumpVec { float x,y,z; };
struct CoinJumpEffect;
struct CoinJumpGroup {
    char pad00[0x10]; CoinJumpEffect *children[5];
    char pad24[0x60]; float phase[5];
};
struct CoinJumpEffect {
    char pad00[0x10]; int extra;
    char slot[0x14]; unsigned char visible; char pad29[3]; float alpha;
    char pad30[0x5C]; CoinJumpVec position;
    char pad98[8]; float rotation; char padA4[0xC]; float scale;
    signed char state; char padB5[0x14]; signed char cleanup; char padCA[2];
    CoinJumpGroup group;
};
struct CoinJumpCamera { char pad[0x80]; CoinJumpVec position; };
extern "C" {
extern CoinJumpCamera lbl_805DF3D0;
extern const float lbl_806D5770, lbl_806D577C, lbl_806D5780, lbl_806D5784, lbl_806D5790, lbl_806D5798, lbl_806D57D8, lbl_806D57F4;
extern const float lbl_806D5810, lbl_806D5814, lbl_806D581C, lbl_806D5820, lbl_806D5824, lbl_806D5828, lbl_806D582C, lbl_806D5830, lbl_806D5834, lbl_806D5838, lbl_806D583C, lbl_806D5840, lbl_806D5844, lbl_806D5848, lbl_806D584C;
void Vec3_Copy(CoinJumpVec *,const CoinJumpVec *);
void Vec3_Subtract_DestFirst(CoinJumpVec *,const CoinJumpVec *,const CoinJumpVec *);
void Vec3_Add_DestFirst(CoinJumpVec *,const CoinJumpVec *,const CoinJumpVec *);
float Vec3_Magnitude_Wrapper(const CoinJumpVec *);
void Vec3_Scale(CoinJumpVec *,const CoinJumpVec *,float);
float BuildOrientationFromYaw(float);
void VfxSlot_SetPositionFromVec(void *,CoinJumpVec);
void VfxSlot_SetRotationZ(void *,float);
void VfxSlot_SetScaleUniform(void *,float);
void VfxSlot_SetUVScroll(void *,float,float);
void VfxSlot_BindResourceEx(void *,int,int);
CoinJumpEffect *DrawEffect_SpawnDirect(void (*)(CoinJumpEffect *));
void fn_800AF4F8(CoinJumpEffect *);
void DrawEffect_Free(CoinJumpEffect *);
void CoinJumpFx_UpdateParticleGrid(CoinJumpEffect *effect,const CoinJumpVec *position,float scale,float alpha) {
    CoinJumpEffect *child;
    if(effect) {
        float particleScale=lbl_806D581C*scale;
        CoinJumpGroup *group=&effect->group;
        for(int i=0;i<2;++i) {
            for(int j=0;j<2;++j) {
                int index=i*2+j;
                child=group->children[index];
                if(child) {
                    Vec3_Copy(&child->position,position);
                    child->scale=particleScale;
                    child->alpha=alpha;
                    if(i==0) {
                        group->phase[index]+=lbl_806D57D8;
                        if(lbl_806D5820<group->phase[index]) group->phase[index]-=lbl_806D5820;
                        child->rotation=BuildOrientationFromYaw(lbl_806D577C*(lbl_806D5824*group->phase[index]));
                        child->scale*=lbl_806D5828*group->phase[index]+lbl_806D5790;
                        if(lbl_806D5770<=group->phase[index] && group->phase[index]<=lbl_806D582C)
                            child->alpha*=lbl_806D5830*group->phase[index];
                        else if(lbl_806D582C<=group->phase[index] && group->phase[index]<=lbl_806D5834) { }
                        else if(lbl_806D5834<=group->phase[index] && group->phase[index]<=lbl_806D5820)
                            child->alpha*=lbl_806D5798*(group->phase[index]-lbl_806D5834)+lbl_806D5790;
                    } else {
                        group->phase[index]+=lbl_806D57D8;
                        if(lbl_806D5784<group->phase[index]) group->phase[index]-=lbl_806D5784;
                        CoinJumpVec delta;
                        Vec3_Subtract_DestFirst(&delta,&lbl_805DF3D0.position,&child->position);
                        float inv=lbl_806D5790/Vec3_Magnitude_Wrapper(&delta);
                        Vec3_Scale(&delta,&delta,scale*(lbl_806D5810*inv));
                        Vec3_Add_DestFirst(&child->position,&child->position,&delta);
                        if(lbl_806D5770<=group->phase[index] && group->phase[index]<=lbl_806D5780)
                            child->scale*=lbl_806D5838*group->phase[index]+lbl_806D5790;
                        else child->scale*=lbl_806D5840*(group->phase[index]-lbl_806D5780)+lbl_806D583C;
                        if(lbl_806D5770<=group->phase[index] && group->phase[index]<=lbl_806D582C)
                            child->alpha*=lbl_806D5830*group->phase[index];
                    }
                    VfxSlot_SetPositionFromVec(child->slot,child->position);
                    VfxSlot_SetRotationZ(child->slot,child->rotation);
                    VfxSlot_SetScaleUniform(child->slot,child->scale);
                    child->visible=1;
                }
            }
        }
        if(effect->extra) {
            CoinJumpEffect *child=group->children[4];
            if(child) {
                Vec3_Copy(&child->position,position);
                child->scale=lbl_806D5844*scale;
                child->alpha=alpha;
                group->phase[4]+=lbl_806D5790;
                if(lbl_806D5848<group->phase[4]) group->phase[4]-=lbl_806D5848;
                CoinJumpVec delta;
                Vec3_Subtract_DestFirst(&delta,&lbl_805DF3D0.position,&child->position);
                float inv=lbl_806D5790/Vec3_Magnitude_Wrapper(&delta);
                Vec3_Scale(&delta,&delta,scale*(lbl_806D57F4*inv));
                Vec3_Add_DestFirst(&child->position,&child->position,&delta);
                child->rotation=BuildOrientationFromYaw(lbl_806D577C*(-group->phase[4]));
                VfxSlot_SetPositionFromVec(child->slot,child->position);
                VfxSlot_SetRotationZ(child->slot,child->rotation);
                VfxSlot_SetScaleUniform(child->slot,child->scale);
                child->visible=1;
            }
        }
    }
}
}
