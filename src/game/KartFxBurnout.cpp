/* Complete native BurnoutCharge callback. Local views contain observed fields;
 * children are independent draw effects, not C++ owned allocations.
 * NonMatching: text 98.97959%, native EH 100%, index 91.66667%.
 * Target 3920B, candidate 3916B; FP clamp webs/constant reloads and GPR
 * partitions remain different. No instruction patch or manual EH is used. */
struct BurnVec { float x,y,z; };
struct BurnMtx { float m[16]; };
struct BurnMotion { unsigned char pad00[0x10]; unsigned long long flags; };
struct BurnKart { unsigned char pad00[0x1F4]; int player, character; unsigned char pad1FC[0x108]; BurnMotion *motion; };
struct BurnOwner { unsigned char pad00[0xE4]; BurnVec velocity; unsigned char padF0[0x18]; float speed; };
struct BurnCamera { unsigned char pad00[0x80]; BurnVec position; };
struct BurnChildCursor { unsigned char preceding[0x10]; struct BurnEffect *child; };
struct BurnEffect {
    unsigned char pad00[0x10]; int index; unsigned char slot[0x14], visible, pad29[3];
    float opacity; unsigned char pad30[0x18]; float matrix[12]; unsigned char pad78[0x14];
    BurnVec position, rotation; unsigned char padA4[0xC]; float scale;
    signed char state, phase; unsigned char padB6[0x13]; signed char expired;
    unsigned char padCA[0x12]; BurnOwner *owner; BurnEffect *child0,*child1,*child2,*child3;
    unsigned char padF0[0x2C]; BurnKart *kart; unsigned char pad120[0x30]; float size, progress;
    unsigned char pad158[0x28]; unsigned int timer0,timer1,timer2,timer3; signed char active, channel;
};
extern "C" {
extern BurnCamera lbl_805DF3D0;
extern float lbl_8032A30C[15];
extern int g_gameMode,g_kartVariant,g_cupId;
extern const float lbl_806D51C0,lbl_806D51C4,lbl_806D51C8,lbl_806D51D0,lbl_806D51D4,lbl_806D51D8,lbl_806D51E8;
extern const float lbl_806D5200,lbl_806D5230,lbl_806D5268,lbl_806D5274,lbl_806D527C,lbl_806D5284,lbl_806D5288,lbl_806D5290,lbl_806D52B8;
extern const float lbl_806D5324,lbl_806D5328,lbl_806D532C,lbl_806D5330,lbl_806D5334,lbl_806D5338,lbl_806D533C,lbl_806D5340,lbl_806D5344;
void fn_800AF4F8(BurnEffect *);
BurnEffect *DrawEffect_SpawnDirect(void (*)(BurnEffect *));
void DrawEffect_Free(BurnEffect *);
void VfxSlot_BindResourceEx(void *,int,int);
void VfxSlot_BindResource(void *,int);
void VfxSlot_SetMatrixSourceEnabled(void *,int);
void VfxSlot_SetUVScroll(void *,float,float);
void VfxSlot_SetPositionFromVec(void *,BurnVec);
void VfxSlot_SetRotationZ(void *,float);
void VfxSlot_SetScaleUniform(void *,float);
float BuildOrientationFromYaw(float);
double sin(double);
double FAbs_FloatAsDouble(float);
void *KartDriver_GetKartRootMtx(BurnKart *);
float Mtx44_GetYawOfPosZ_Padded(const void *);
float Mtx44_GetPitchOfPosZ_Padded(const void *);
float Mtx44_GetPitchOfNegX(const void *);
void Vec2_RotateY(BurnVec *,const BurnVec *,float);
void Mtx_TransposeToMtx44(BurnMtx *,const void *);
void Mtx44_TransformVec3(BurnVec *,const BurnMtx *,BurnVec);
void GetSpawnPosition(BurnVec *,float,float,float);
float KartCharacterParam_GetFxSizeFactor(BurnKart *);
void Vec3_Scale(BurnVec *,const BurnVec *,float);
void Vec3_Subtract_DestFirst(BurnVec *,const BurnVec *,const BurnVec *);
void Vec3_Add_DestFirst(BurnVec *,const BurnVec *,const BurnVec *);
float Vec3_Magnitude_Wrapper(const BurnVec *);
void Vec3_Copy(BurnVec *,const BurnVec *);
float Vec3_HorizontalYawTo(const BurnVec *,const BurnVec *);
unsigned char *PcbSlot_GetByIndex(int);
unsigned char FinalLapCoinJump_CheckActiveForObject(BurnKart *);
void Matrix4_Identity(BurnMtx *);
void Mtx44_Scale_Uniform(BurnMtx *,const BurnMtx *,float);
void Matrix4_PreMultiplyRotX(BurnMtx *,const BurnMtx *,float);
void Matrix4_PreMultiplyRotY(BurnMtx *,const BurnMtx *,float);
void Matrix4_PreMultiplyRotZ(BurnMtx *,const BurnMtx *,float);
void Mtx44_Translate(BurnMtx *,const BurnMtx *,BurnVec);
void DbgScene_CopyMatrix3x4Transpose(float *,const BurnMtx *);
int SoundMgr_CountActiveSEInstances(int);
void SoundMgr_PlaySE_Positional(int,BurnVec,int);
void SoundMgr_PlaySE_WithChannel(int,BurnVec,int);
static inline int BurnCharacter(BurnKart *kart) {
    if (!kart) return -1;
    if (kart->player < 0 || kart->player > 3) return -1;
    if (g_gameMode == 2) {
        if ((((unsigned int)PcbSlot_GetByIndex(kart->player)[6] >> 1)&3U)<2U) return -1;
    } else {
        if (g_kartVariant < 2) return -1;
        if (g_cupId >= 9) return -1;
    }
    int c=kart->character;
    if (c<0 || c>=15) return -1;
    return c;
}

void KartFx_BurnoutChargeTick(BurnEffect *e) {
    BurnMtx root, matrix;
    BurnVec rotated, offset, world;
    int charging=0;
    BurnOwner *owner=e->owner;
    BurnMotion *motion=e->kart->motion;
    if (e->index==0 && (motion->flags & 0x40ULL)!=0) charging=1;
    if (e->index==0 && (motion->flags & 0x400ULL)!=0) charging=0;
    if (e->index!=0 && (motion->flags & 0x400ULL)!=0) charging=1;
    int released=0;
    if ((motion->flags & 0x8000000000000000ULL)!=0) released=1;
    switch(e->state) {
    case 0:
        if (e->index==0) VfxSlot_BindResourceEx(e->slot,0x2F,0);
        else VfxSlot_BindResourceEx(e->slot,0x32,0);
        e->visible=0;
        if (e->index==0) {
            e->child0=DrawEffect_SpawnDirect(fn_800AF4F8);
            if(e->child0) { VfxSlot_BindResourceEx(e->child0->slot,0x2D,0); e->child0->visible=0; }
        }
        if (e->index==0) {
            e->child1=DrawEffect_SpawnDirect(fn_800AF4F8);
            if(e->child1) { VfxSlot_BindResourceEx(e->child1->slot,0x2E,0); e->child1->visible=0; }
        }
        if (e->index!=0) {
            e->child2=DrawEffect_SpawnDirect(fn_800AF4F8);
            if(e->child2) { VfxSlot_BindResourceEx(e->child2->slot,0x33,0); e->child2->visible=0; }
        }
        if (e->index==0) {
            e->child3=DrawEffect_SpawnDirect(fn_800AF4F8);
            if(e->child3) { VfxSlot_BindResource(e->child3->slot,0x30); e->child3->visible=0; VfxSlot_SetMatrixSourceEnabled(e->child3->slot,1); }
        }
        e->size=lbl_806D51C4; e->active=0; e->channel=-1; e->state=2; e->phase=0;
        break;
    case 1:
        switch(e->phase) {
        case 0:
            e->visible=1; e->opacity=lbl_806D51C4; e->rotation.z=lbl_806D51C0;
            if(e->child0) { e->child0->visible=1; e->child0->opacity=lbl_806D51C4; }
            if(e->child1) e->child1->visible=0;
            if(e->child2) { e->child2->visible=1; e->child2->opacity=lbl_806D51C4; }
            if(e->child3) e->child3->visible=0;
            e->size=lbl_806D51C4; e->progress=lbl_806D51C0; ++e->phase;
            break;
        case 1: break;
        }
        if(e->index==0) {
            float f=lbl_806D51D0*e->progress-lbl_806D51C4;
            if(f<lbl_806D51C0) f=lbl_806D51C0;
            if(lbl_806D51C4<f) f=lbl_806D51C4;
            e->rotation.z=BuildOrientationFromYaw(lbl_806D5324 * -f);
        }
        if(e->child0) e->child0->rotation.z=BuildOrientationFromYaw(lbl_806D5324*e->progress+lbl_806D527C);
        if(e->child2) e->child2->rotation.z=BuildOrientationFromYaw(lbl_806D5324*e->progress+lbl_806D527C);
        e->progress+=lbl_806D5328;
        if(lbl_806D51C4<e->progress) { e->state=2; e->phase=0; }
        else if(e->active && released) { e->state=3; e->phase=0; }
        break;
    case 2:
        switch(e->phase) {
        case 0:
            e->visible=1;
            if(charging) e->opacity=lbl_806D51C4; else e->opacity=lbl_806D51C0;
            e->rotation.z=lbl_806D51C0;
            if(e->child0) {
                e->child0->visible=1;
                if(charging) e->child0->opacity=lbl_806D51C4; else e->child0->opacity=lbl_806D51C0;
                e->child0->rotation.z=lbl_806D527C;
            }
            if(e->child1) e->child1->visible=0;
            if(e->child2) {
                e->child2->visible=1;
                if(charging) e->child2->opacity=lbl_806D51C4; else e->child2->opacity=lbl_806D51C0;
                e->child2->rotation.z=lbl_806D527C;
            }
            if(e->child3) { e->child3->visible=1; e->child3->opacity=lbl_806D51C0; }
            e->size=lbl_806D51C4; e->progress=lbl_806D51C0; ++e->phase;
            break;
        case 1: break;
        }
        if(charging) {
            if(!e->active) { e->opacity=lbl_806D51C4; e->active=1; e->state=1; e->phase=0; break; }
        } else {
            if(e->index==0 && e->channel>=0) e->channel=-1;
            e->opacity-=lbl_806D51D8;
            if(e->opacity<lbl_806D51C0) e->opacity=lbl_806D51C0;
            e->active=0;
        }
        e->progress=BuildOrientationFromYaw(lbl_806D5288+e->progress);
        if(e->index==0) e->size=lbl_806D5284*(float)sin(e->progress)+lbl_806D51C4;
        if(e->index==0) {
            if(lbl_806D51E8<=owner->speed) {
                Vec2_RotateY(&rotated,&owner->velocity,-Mtx44_GetYawOfPosZ_Padded(KartDriver_GetKartRootMtx(e->kart)));
                float f=rotated.x/lbl_806D5200;
                if(f<lbl_806D5230) f=lbl_806D5230;
                if(lbl_806D51C4<f) f=lbl_806D51C4;
                e->rotation.z=lbl_806D52B8*f;
                if(e->child3) {
                    float yaw;
                    if(lbl_806D51C0<f) yaw=lbl_806D52B8; else yaw=lbl_806D532C;
                    if(yaw!=e->child3->rotation.y) e->child3->opacity=lbl_806D51C0;
                    e->child3->rotation.y=yaw;
                }
            } else e->rotation.z*=lbl_806D5268;
        }
        if(e->child0) { e->child0->opacity-=lbl_806D51C8; if(e->child0->opacity<lbl_806D51C0) e->child0->opacity=lbl_806D51C0; }
        if(e->child2) { e->child2->opacity-=lbl_806D51C8; if(e->child2->opacity<lbl_806D51C0) e->child2->opacity=lbl_806D51C0; }
        if(e->child3) {
            if(charging && lbl_806D51E8<=owner->speed) {
                e->child3->opacity+=lbl_806D51C8;
                if(lbl_806D51C4<e->child3->opacity) e->child3->opacity=lbl_806D51C4;
            } else {
                e->child3->opacity-=lbl_806D51D8;
                if(e->child3->opacity<lbl_806D51C0) e->child3->opacity=lbl_806D51C0;
            }
        }
        if(e->active && released) { e->state=3; e->phase=0; }
        break;
    case 3:
        switch(e->phase) {
        case 0:
            if(e->index==0) e->visible=0;
            else { e->visible=1; e->opacity=lbl_806D51C4; e->rotation.z=lbl_806D51C0; }
            if(e->child0) e->child0->visible=0;
            if(e->child1) { e->child1->visible=1; e->child1->opacity=lbl_806D51C4; }
            if(e->child2) { e->child2->visible=1; e->child2->opacity=lbl_806D51C4; e->child2->rotation.z=lbl_806D51C0; }
            if(e->child3) e->child3->visible=0;
            e->size=lbl_806D51C4; e->progress=lbl_806D51C0;
            if(e->index!=0) SoundMgr_PlaySE_Positional(0xA4,e->position,0);
            ++e->phase;
            break;
        case 1: break;
        }
        if(e->index==0) e->size=lbl_806D51D4*(float)FAbs_FloatAsDouble((float)sin(lbl_806D5330*e->progress))+lbl_806D51C4;
        if(e->child2) e->child2->rotation.z=BuildOrientationFromYaw(lbl_806D5324*e->progress+lbl_806D527C);
        e->progress+=lbl_806D5334;
        if(lbl_806D51C4<e->progress) { e->state=1; e->phase=0; }
        else if(e->active && released) { e->state=3; e->phase=0; }
        break;
    }
    if(e->expired) {
        DrawEffect_Free(e->child0); DrawEffect_Free(e->child1); DrawEffect_Free(e->child2); DrawEffect_Free(e->child3);
        e->child0=0; e->child1=0; e->child2=0; e->child3=0;
        if(e->channel>=0) e->channel=-1;
        DrawEffect_Free(e); return;
    }
    Mtx_TransposeToMtx44(&root,KartDriver_GetKartRootMtx(e->kart));
    GetSpawnPosition(&offset,lbl_806D51C0,lbl_806D5338,lbl_806D51C0);
    Vec3_Scale(&offset,&offset,KartCharacterParam_GetFxSizeFactor(e->kart));
    Mtx44_TransformVec3(&world,&root,offset);
    BurnVec *camera=&lbl_805DF3D0.position;
    Vec3_Subtract_DestFirst(&offset,&world,camera);
    float distance=Vec3_Magnitude_Wrapper(&offset);
    Vec3_Scale(&offset,&offset,e->scale*(lbl_806D533C*(lbl_806D51C4/distance)));
    Vec3_Add_DestFirst(&e->position,&world,&offset);
    int character=BurnCharacter(e->kart);
    float factor=character<0 ? lbl_806D51C4 : lbl_8032A30C[character];
    e->scale=(e->size*(lbl_806D5340*KartCharacterParam_GetFxSizeFactor(e->kart)))*factor;
    if(e->index!=0) {
        float f=Vec3_Magnitude_Wrapper(&owner->velocity)/lbl_806D5344;
        if(lbl_806D5328<f) f=lbl_806D5328;
        if(f<lbl_806D5290) f=lbl_806D5290;
        VfxSlot_SetUVScroll(e->slot,f,lbl_806D51C0);
    }
    VfxSlot_SetPositionFromVec(e->slot,e->position);
    VfxSlot_SetRotationZ(e->slot,e->rotation.z);
    VfxSlot_SetScaleUniform(e->slot,e->scale);
    if(FinalLapCoinJump_CheckActiveForObject(e->kart)) e->slot[0]|=2;
    else e->slot[0]&=~2;
    BurnChildCursor *cursor=(BurnChildCursor *)((unsigned char *)e+0xD0);
    for(int i=1;i<5;++i,cursor=(BurnChildCursor *)((unsigned char *)cursor+4)) {
        if(cursor->child) {
            if(FinalLapCoinJump_CheckActiveForObject(e->kart)) cursor->child->slot[0]|=2;
            else cursor->child->slot[0]&=~2;
            Vec3_Copy(&cursor->child->position,&e->position);
            cursor->child->scale=e->scale;
            if(i==4) cursor->child->scale*=lbl_806D5274;
            if(i!=4) {
                VfxSlot_SetPositionFromVec(cursor->child->slot,cursor->child->position);
                VfxSlot_SetRotationZ(cursor->child->slot,cursor->child->rotation.z);
                VfxSlot_SetScaleUniform(cursor->child->slot,cursor->child->scale);
            } else {
                float pitch=Mtx44_GetPitchOfPosZ_Padded(KartDriver_GetKartRootMtx(e->kart));
                float yaw=Vec3_HorizontalYawTo(camera,&cursor->child->position);
                float roll=Mtx44_GetPitchOfNegX(KartDriver_GetKartRootMtx(e->kart));
                Matrix4_Identity(&matrix);
                Mtx44_Scale_Uniform(&matrix,&matrix,e->child3->scale);
                Matrix4_PreMultiplyRotY(&matrix,&matrix,cursor->child->rotation.y);
                Matrix4_PreMultiplyRotX(&matrix,&matrix,pitch);
                Matrix4_PreMultiplyRotZ(&matrix,&matrix,roll);
                Matrix4_PreMultiplyRotY(&matrix,&matrix,yaw);
                Mtx44_Translate(&matrix,&matrix,e->child3->position);
                DbgScene_CopyMatrix3x4Transpose(e->child3->matrix,&matrix);
            }
        }
    }
    if(e->index==0) {
        if(e->channel<0) {
            if(e->active) {
                e->channel=SoundMgr_CountActiveSEInstances(0xA3);
                if(e->channel>=0) SoundMgr_PlaySE_Positional(0xA3,e->position,e->channel);
            }
        } else SoundMgr_PlaySE_WithChannel(0xA3,e->position,e->channel);
    }
    if(e->timer0) --e->timer0;
    if(e->timer1) --e->timer1;
    if(e->timer2) --e->timer2;
    if(e->timer3) --e->timer3;
}
}
