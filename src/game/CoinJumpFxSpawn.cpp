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
void CoinJumpFx_SpawnSlots(CoinJumpEffect *effect) {
    int i,j;
    CoinJumpGroup *group=&effect->group;
    switch(effect->state) {
    case 0:
        for(i=0;i<2;++i) {
            for(j=0;j<2;++j) {
                int index=i*2+j;
                group->children[index]=DrawEffect_SpawnDirect(fn_800AF4F8);
                if(group->children[index]) {
                    if(i==0) VfxSlot_BindResourceEx(group->children[index]->slot,0x2B,0);
                    else VfxSlot_BindResourceEx(group->children[index]->slot,0x2A,0);
                    group->children[index]->visible=0;
                    switch(index) {
                    case 0: group->phase[index]=lbl_806D5770; break;
                    case 1: group->phase[index]=lbl_806D5814; break;
                    case 2: group->phase[index]=lbl_806D5770; break;
                    case 3: group->phase[index]=lbl_806D5780; break;
                    }
                }
            }
        }
        if(effect->extra) {
            group->children[4]=DrawEffect_SpawnDirect(fn_800AF4F8);
            if(group->children[4]) {
                VfxSlot_BindResourceEx(group->children[4]->slot,0x2C,0);
                VfxSlot_SetUVScroll(group->children[4]->slot,lbl_806D5770,lbl_806D584C);
                group->children[4]->visible=0;
                group->phase[4]=lbl_806D5770;
            }
        }
        ++effect->state;
        break;
    case 1: break;
    }
    if(effect->cleanup) {
        for(i=0;i<2;++i) {
            for(j=0;j<2;++j) {
                int index=i*2+j;
                DrawEffect_Free(group->children[index]);
                group->children[index]=0;
            }
        }
        if(effect->extra) {
            DrawEffect_Free(group->children[4]);
            group->children[4]=0;
        }
        DrawEffect_Free(effect);
    }
}
}
