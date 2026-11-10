/* Complete native BurnoutCharge callback. Local views contain observed fields;
 * children are independent draw effects, not C++ owned allocations.
 * Text 3920B, native EH and index are byte-identical.
 * Accumulator expressions preserve the scale calculation webs.
 * Float literals preserve native clamp webs; FAbs returns float. */
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
extern float KartFx_BurnoutChargeTick_rodata_8032A30C[15];
extern int g_gameMode,g_kartVariant,g_cupId;
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
float FAbs_FloatAsDouble(float);
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
    BurnOwner *owner=e->owner;
    int charging=0;
    BurnVec *camera;
    BurnChildCursor *cursor;
    int i;
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
        e->size=1.0f; e->active=0; e->channel=-1; e->state=2; e->phase=0;
        break;
    case 1:
        switch(e->phase) {
        case 0:
            e->visible=1; e->opacity=1.0f; e->rotation.z=0.0f;
            if(e->child0) { e->child0->visible=1; e->child0->opacity=1.0f; }
            if(e->child1) e->child1->visible=0;
            if(e->child2) { e->child2->visible=1; e->child2->opacity=1.0f; }
            if(e->child3) e->child3->visible=0;
            e->size=1.0f; e->progress=0.0f; ++e->phase;
            break;
        case 1: break;
        }
        if(e->index==0) {
            float f=3.0f*e->progress-1.0f;
            if(f<0.0f) f=0.0f;
            if(1.0f<f) f=1.0f;
            e->rotation.z=BuildOrientationFromYaw(6.283184f * -f);
        }
        if(e->child0) e->child0->rotation.z=BuildOrientationFromYaw(6.283184f*e->progress+-0.785398f);
        if(e->child2) e->child2->rotation.z=BuildOrientationFromYaw(6.283184f*e->progress+-0.785398f);
        e->progress+=0.033333335f;
        if(1.0f<e->progress) { e->state=2; e->phase=0; }
        else if(e->active && released) { e->state=3; e->phase=0; }
        break;
    case 2:
        switch(e->phase) {
        case 0:
            e->visible=1;
            if(charging) e->opacity=1.0f; else e->opacity=0.0f;
            e->rotation.z=0.0f;
            if(e->child0) {
                e->child0->visible=1;
                if(charging) e->child0->opacity=1.0f; else e->child0->opacity=0.0f;
                e->child0->rotation.z=-0.785398f;
            }
            if(e->child1) e->child1->visible=0;
            if(e->child2) {
                e->child2->visible=1;
                if(charging) e->child2->opacity=1.0f; else e->child2->opacity=0.0f;
                e->child2->rotation.z=-0.785398f;
            }
            if(e->child3) { e->child3->visible=1; e->child3->opacity=0.0f; }
            e->size=1.0f; e->progress=0.0f; ++e->phase;
            break;
        case 1: break;
        }
        if(charging) {
            if(!e->active) { e->opacity=1.0f; e->active=1; e->state=1; e->phase=0; break; }
        } else {
            if(e->index==0 && e->channel>=0) e->channel=-1;
            e->opacity-=0.05f;
            if(e->opacity<0.0f) e->opacity=0.0f;
            e->active=0;
        }
        e->progress=BuildOrientationFromYaw(0.087266445f+e->progress);
        if(e->index==0) e->size=0.02f*(float)sin(e->progress)+1.0f;
        if(e->index==0) {
            if(0.5f<=owner->speed) {
                Vec2_RotateY(&rotated,&owner->velocity,-Mtx44_GetYawOfPosZ_Padded(KartDriver_GetKartRootMtx(e->kart)));
                float f=rotated.x/10.0f;
                if(f<-1.0f) f=-1.0f;
                if(1.0f<f) f=1.0f;
                e->rotation.z=1.570796f*f;
                if(e->child3) {
                    float yaw;
                    if(0.0f<f) yaw=1.570796f; else yaw=-1.570796f;
                    if(yaw!=e->child3->rotation.y) e->child3->opacity=0.0f;
                    e->child3->rotation.y=yaw;
                }
            } else e->rotation.z*=0.95f;
        }
        if(e->child0) { e->child0->opacity-=0.1f; if(e->child0->opacity<0.0f) e->child0->opacity=0.0f; }
        if(e->child2) { e->child2->opacity-=0.1f; if(e->child2->opacity<0.0f) e->child2->opacity=0.0f; }
        if(e->child3) {
            if(charging && 0.5f<=owner->speed) {
                e->child3->opacity+=0.1f;
                if(1.0f<e->child3->opacity) e->child3->opacity=1.0f;
            } else {
                e->child3->opacity-=0.05f;
                if(e->child3->opacity<0.0f) e->child3->opacity=0.0f;
            }
        }
        if(e->active && released) { e->state=3; e->phase=0; }
        break;
    case 3:
        switch(e->phase) {
        case 0:
            if(e->index==0) e->visible=0;
            else { e->visible=1; e->opacity=1.0f; e->rotation.z=0.0f; }
            if(e->child0) e->child0->visible=0;
            if(e->child1) { e->child1->visible=1; e->child1->opacity=1.0f; }
            if(e->child2) { e->child2->visible=1; e->child2->opacity=1.0f; e->child2->rotation.z=0.0f; }
            if(e->child3) e->child3->visible=0;
            e->size=1.0f; e->progress=0.0f;
            if(e->index!=0) SoundMgr_PlaySE_Positional(0xA4,e->position,0);
            ++e->phase;
            break;
        case 1: break;
        }
        if(e->index==0) e->size=0.2f*FAbs_FloatAsDouble((float)sin(4.712388f*e->progress))+1.0f;
        if(e->child2) e->child2->rotation.z=BuildOrientationFromYaw(6.283184f*e->progress+-0.785398f);
        e->progress+=0.125f;
        if(1.0f<e->progress) { e->state=1; e->phase=0; }
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
    GetSpawnPosition(&offset,0.0f,7.0f,0.0f);
    Vec3_Scale(&offset,&offset,KartCharacterParam_GetFxSizeFactor(e->kart));
    Mtx44_TransformVec3(&world,&root,offset);
    camera=&lbl_805DF3D0.position;
    Vec3_Subtract_DestFirst(&offset,&world,camera);
    float distance=Vec3_Magnitude_Wrapper(&offset);
    distance=1.0f/distance;
    distance=-8.0f*distance;
    distance=e->scale*distance;
    Vec3_Scale(&offset,&offset,distance);
    Vec3_Add_DestFirst(&e->position,&world,&offset);
    int character=BurnCharacter(e->kart);
    float factor=character<0 ? 1.0f : KartFx_BurnoutChargeTick_rodata_8032A30C[character];
    float scale=1.3f*KartCharacterParam_GetFxSizeFactor(e->kart);
    scale=e->size*scale;
    scale=scale*factor;
    e->scale=scale;
    if(e->index!=0) {
        float f=Vec3_Magnitude_Wrapper(&owner->velocity)/100.0f;
        if(0.033333335f<f) f=0.033333335f;
        if(f<0.001f) f=0.001f;
        VfxSlot_SetUVScroll(e->slot,f,0.0f);
    }
    VfxSlot_SetPositionFromVec(e->slot,e->position);
    VfxSlot_SetRotationZ(e->slot,e->rotation.z);
    VfxSlot_SetScaleUniform(e->slot,e->scale);
    if(FinalLapCoinJump_CheckActiveForObject(e->kart)) e->slot[0]|=2;
    else e->slot[0]&=~2;
    cursor=(BurnChildCursor *)((unsigned char *)e+0xD0);
    for(i=1;i<5;++i,cursor=(BurnChildCursor *)((unsigned char *)cursor+4)) {
        if(cursor->child) {
            if(FinalLapCoinJump_CheckActiveForObject(e->kart)) cursor->child->slot[0]|=2;
            else cursor->child->slot[0]&=~2;
            Vec3_Copy(&cursor->child->position,&e->position);
            cursor->child->scale=e->scale;
            if(i==4) cursor->child->scale*=0.9f;
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
