/* Narrow target-observed layout; live Ghidra types unavailable in this worker. */
#include "game/types/CoinJumpVec.h"
struct CoinJumpEffect;
#include "game/types/CoinJumpGroup.h"
struct CoinJumpEffect {
    char pad00[0x10]; int extra;
    char slot[0x14]; unsigned char visible; char pad29[3]; float alpha;
    char pad30[0x5C]; CoinJumpVec position;
    char pad98[8]; float rotation; char padA4[0xC]; float scale;
    signed char state; char padB5[0x14]; signed char cleanup; char padCA[2];
    CoinJumpGroup group;
};
#include "game/types/CoinJumpCamera.h"
extern "C" {
extern CoinJumpCamera lbl_805DF3D0;
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
static inline CoinJumpEffect *CoinJumpGroup_GetChild(CoinJumpGroup *group,int index) {
    return group->children[index];
}

void CoinJumpFx_UpdateParticleGrid(CoinJumpEffect *effect,const CoinJumpVec *position,float scale,float alpha) {
    if(effect) {
        float particleScale=1.8f*scale;
        CoinJumpGroup *group=&effect->group;
        CoinJumpEffect *child;
        for(int i=0;i<2;++i) {
            for(int j=0;j<2;++j) {
                int index=i*2+j;
                child=CoinJumpGroup_GetChild(group,index);
                if(child) {
                    Vec3_Copy(&child->position,position);
                    child->scale=particleScale;
                    child->alpha=alpha;
                    if(i==0) {
                        group->phase[index]+=0.5f;
                        if(90.0f<group->phase[index]) group->phase[index]-=90.0f;
                        child->rotation=BuildOrientationFromYaw(0.017453288659453392f*((-6.0f)*group->phase[index]));
                        child->scale*=(-0.006666666828095913f)*group->phase[index]+1.0f;
                        if(0.0f<=group->phase[index] && group->phase[index]<=15.0f)
                            child->alpha*=0.06666667014360428f*group->phase[index];
                        else if(15.0f<=group->phase[index] && group->phase[index]<=70.0f) { }
                        else if(70.0f<=group->phase[index] && group->phase[index]<=90.0f)
                            child->alpha*=(-0.05f)*(group->phase[index]-70.0f)+1.0f;
                    } else {
                        group->phase[index]+=0.5f;
                        if(60.0f<group->phase[index]) group->phase[index]-=60.0f;
                        CoinJumpVec delta;
                        Vec3_Subtract_DestFirst(&delta,&lbl_805DF3D0.position,&child->position);
                        float inv=1.0f/Vec3_Magnitude_Wrapper(&delta);
                        Vec3_Scale(&delta,&delta,scale*(5.0f*inv));
                        Vec3_Add_DestFirst(&child->position,&child->position,&delta);
                        if(0.0f<=group->phase[index] && group->phase[index]<=30.0f)
                            child->scale*=(-0.0033333341125398874f)*group->phase[index]+1.0f;
                        else child->scale*=(-0.026666665449738503f)*(group->phase[index]-30.0f)+0.9f;
                        if(0.0f<=group->phase[index] && group->phase[index]<=15.0f)
                            child->alpha*=0.06666667014360428f*group->phase[index];
                    }
                    VfxSlot_SetPositionFromVec(child->slot,child->position);
                    VfxSlot_SetRotationZ(child->slot,child->rotation);
                    VfxSlot_SetScaleUniform(child->slot,child->scale);
                    child->visible=1;
                }
            }
        }
        if(effect->extra) {
            child=group->children[4];
            if(child) {
                Vec3_Copy(&child->position,position);
                child->scale=1.2f*scale;
                child->alpha=alpha;
                group->phase[4]+=1.0f;
                if(360.0f<group->phase[4]) group->phase[4]-=360.0f;
                CoinJumpVec delta;
                Vec3_Subtract_DestFirst(&delta,&lbl_805DF3D0.position,&child->position);
                float inv=1.0f/Vec3_Magnitude_Wrapper(&delta);
                Vec3_Scale(&delta,&delta,scale*(6.0f*inv));
                Vec3_Add_DestFirst(&child->position,&child->position,&delta);
                child->rotation=BuildOrientationFromYaw(0.017453288659453392f*(-group->phase[4]));
                VfxSlot_SetPositionFromVec(child->slot,child->position);
                VfxSlot_SetRotationZ(child->slot,child->rotation);
                VfxSlot_SetScaleUniform(child->slot,child->scale);
                child->visible=1;
            }
        }
    }
}
}
