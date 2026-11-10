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
ClusterEffect *DrawEffect_SpawnDirect(void (*)(ClusterEffect *));
void fn_800AF4F8(ClusterEffect *);
void DrawEffect_Free(ClusterEffect *);
void VfxSlot_BindResourceEx(void *,int,int);
void Vec3_Copy(ClusterVec *,const ClusterVec *);
void Vec3_Subtract_DestFirst(ClusterVec *,const ClusterVec *,const ClusterVec *);
void Vec3_Add_DestFirst(ClusterVec *,const ClusterVec *,const ClusterVec *);
float Vec3_Magnitude_Wrapper(const ClusterVec *);
void Vec3_Scale(ClusterVec *,const ClusterVec *,float);
#ifdef __MWERKS__
void VfxSlot_SetPositionFromVec(void *,ClusterVec);
#else
/* The definition takes these structs by address; see docs/notes/port_abi.md. */
extern void VfxSlot_SetPositionFromVec(void *, ClusterVec *);
static inline void VfxSlot_SetPositionFromVec_ByValue(void *a0, ClusterVec a1) { VfxSlot_SetPositionFromVec(a0, &a1); }
#define VfxSlot_SetPositionFromVec VfxSlot_SetPositionFromVec_ByValue
#endif
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
        group->growth=0.0f;
        ++effect->state;
    case 1:
        group->growth+=0.05f;
        if(1.0f<group->growth) group->growth=1.0f;
        for(shift=0;shift<15;++shift) {
            if(group->children[15-shift] && group->children[14-shift])
                Vec3_Copy(&group->children[15-shift]->position,&group->children[14-shift]->position);
        }
        if(group->children[0]) Vec3_Copy(&group->children[0]->position,&effect->position);
        ordinal=0.0f;
        for(i=0;i<16;++i,ordinal+=1.0f) {
            if(group->children[i]) {
                ClusterVec delta;
                Vec3_Subtract_DestFirst(&delta,&group->children[i]->position,&effect->position);
                float magnitude=Vec3_Magnitude_Wrapper(&delta);
                float limit=10.0f*((1.0f+ordinal)*(effect->scale*group->growth));
                if(limit<magnitude) {
                    Vec3_Scale(&delta,&delta,1.0f/limit);
                    Vec3_Add_DestFirst(&group->children[i]->position,&effect->position,&delta);
                }
                VfxSlot_SetPositionFromVec(group->children[i]->slot,group->children[i]->position);
                if(effect->variant==2 || effect->variant==3)
                    VfxSlot_SetRotationZ(group->children[i]->slot,0.017453288659453392f*Rand_RangeFloat(-180.0f,180.0f));
                float scale=0.9f*((16.0f-(ordinal-8.0f))/16.0f)+0.1f;
                if(1.0f<scale) scale=1.0f;
                switch(effect->variant) {
                case 0: break;
                case 1: scale*=2.0f; break;
                case 2: scale*=1.3f; break;
                case 3: scale*=1.3f; break;
                }
                group->children[i]->scale=scale*effect->scale;
                VfxSlot_SetScaleUniform(group->children[i]->slot,group->children[i]->scale);
                float alpha=0.8f*((16.0f-ordinal)/16.0f)+0.2f;
                switch(effect->variant) {
                case 2: break;
                case 3: break;
                case 0: alpha*=0.15f; break;
                case 1: alpha*=0.15f; break;
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
