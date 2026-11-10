/* Complete ASM-derived flight/lock-on state machine. Ghidra unavailable.
 * Views are local to this TU and describe only observed fields.
 * Vec3 value arguments use the native C++ ABI and compiler-owned copies.
 * Text and compiler-owned EH match the target exactly. */
struct FlightVec { float x,y,z; };
struct FlightItem {
    unsigned char pad00[8]; int alias; unsigned char pad0C[4]; int launched;
    unsigned char sprite[0x14]; unsigned char active; unsigned char pad29[3]; float lifetime;
    unsigned char pad30[0xC]; unsigned char flag3C; unsigned char pad3D[0x50];
    signed char lockState, lockKind; unsigned char pad8F;
    FlightVec impulse; int effectId; FlightVec position; float pitch,yaw,roll;
    FlightVec velocity; float speed; unsigned char state; signed char phase,flightPhase;
    unsigned char reason;
};
struct FlightContext {
    unsigned char pad00[4]; unsigned int timer,effectTimer,trackTimer;
    unsigned char pad10[4]; float ground;
    unsigned char pad18[0x44]; void *sprite;
    unsigned char pad60[0x1C]; unsigned int field7C;
    unsigned char pad80[0x18]; void *kart,*target; signed char command;
};
struct FlightEffect {
    unsigned char pad00[0x10]; int enabled; unsigned char pad14[0x78];
    FlightVec position; unsigned char pad98[0xC]; FlightVec velocity;
    unsigned char padB0[0x1C]; int id;
    unsigned char padD0[0x4C]; void *target;
};
extern "C" {
extern const float lbl_806D62C0,lbl_806D62C4,lbl_806D62C8,lbl_806D62CC;
extern const float lbl_806D62D0,lbl_806D62D4,lbl_806D62D8,lbl_806D62DC;
extern const float lbl_806D62E0,lbl_806D62E4,lbl_806D62E8,lbl_806D62F8,lbl_806D62FC;
extern const float lbl_806D6300,lbl_806D630C,lbl_806D6314,lbl_806D6318,lbl_806D631C;
extern const float lbl_806D6320,lbl_806D6324,lbl_806D6328,lbl_806D632C;
extern const float lbl_806D6330,lbl_806D6334,lbl_806D6338,lbl_806D633C,lbl_806D6340,lbl_806D6344;
extern int g_ccClass;
#ifdef __MWERKS__
void Item_BendVelocityByGroundProbe(FlightVec *,FlightVec,float,float,float);
#else
/* The definition takes these structs by address; see docs/notes/port_abi.md. */
extern void Item_BendVelocityByGroundProbe(FlightVec *, FlightVec *, float, float, float);
static inline void Item_BendVelocityByGroundProbe_ByValue(FlightVec *a0, FlightVec a1, float a2, float a3, float a4) { Item_BendVelocityByGroundProbe(a0, &a1, a2, a3, a4); }
#define Item_BendVelocityByGroundProbe Item_BendVelocityByGroundProbe_ByValue
#endif
#ifdef __MWERKS__
void KartDriver_TransformWorldToLocalY0(FlightVec *,FlightVec,void *);
#else
/* The definition takes these structs by address; see docs/notes/port_abi.md. */
extern void KartDriver_TransformWorldToLocalY0(FlightVec *, FlightVec *, void *);
static inline void KartDriver_TransformWorldToLocalY0_ByValue(FlightVec *a0, FlightVec a1, void *a2) { KartDriver_TransformWorldToLocalY0(a0, &a1, a2); }
#define KartDriver_TransformWorldToLocalY0 KartDriver_TransformWorldToLocalY0_ByValue
#endif
void SpriteSlot_SetMatrixSourceEnabled_WithReseed(void *,int);
void *ItemObject_AllocGabyou();
void Item_RenderFlyingFromKart(FlightItem *,void *,int,float,float,float);
unsigned char FinalLapCoinJump_CheckActiveForObject(void *);
void SpriteSlot_Container_Free(void *);
void Item_InitLaunchFromKart(FlightItem *,int,float,float);
void ItemTracker_AcquireLock(FlightItem *);
void ItemTracker_SetTrackPhase(FlightItem *,int);
#ifdef __MWERKS__
signed char ItemObject_GetGroundTypeAt(FlightVec,float *,int);
#else
/* The definition takes these structs by address; see docs/notes/port_abi.md. */
extern signed char ItemObject_GetGroundTypeAt(FlightVec *, float *, int);
static inline signed char ItemObject_GetGroundTypeAt_ByValue(FlightVec a0, float *a1, int a2) { return ItemObject_GetGroundTypeAt(&a0, a1, a2); }
#define ItemObject_GetGroundTypeAt ItemObject_GetGroundTypeAt_ByValue
#endif
void Item_AccelClampVelocity(FlightItem *,float,float);
void fn_801B129C(FlightVec *);
void Item_HomingScanAndSteer(FlightItem *,float *,int);
void Item_DecayVelocityScalar(FlightItem *,float);
int ItemCollision_Check(FlightItem *);
short ItemAlias_HitRemapLookup(int);
void *ItemTracker_GetTargetKart(FlightItem *);
void fn_801B1D5C(void *,void *,int,int);
void fn_801B1660(void *,void *);
void fn_801B158C(void *,void *);
void fn_801B14B8(void *,void *);
void ItemHit_Dispatch(FlightItem *,int,int,int);
void ItemTracker_ReleaseLock(FlightItem *);
void SoundMgr_PlaySE_Positional(int,FlightVec,int);
void Effect_HitFlash_Update(void *);
FlightEffect *DrawEffect_SpawnDirect(void (*)(void *));
void Vec3_Copy(FlightVec *,const FlightVec *);
float Rand_RangeFloat(float,float);
void GetSpawnPosition(FlightVec *,float,float,float);
void Vec2_RotateX(FlightVec *,const FlightVec *,float);
void Vec2_RotateY(FlightVec *,const FlightVec *,float);
void *KartDriver_GetJointByIdx(void *,int);
void Mtx44_GetTranslation_RowMajor(FlightVec *,void *);
float fn_800D3184(const FlightVec *,const FlightVec *);
#ifdef __MWERKS__
void Item_ComputeYawRelativeApproach(FlightVec *,void *,FlightVec,FlightVec);
#else
/* The definition takes these structs by address; see docs/notes/port_abi.md. */
extern void Item_ComputeYawRelativeApproach(FlightVec *, void *, FlightVec *, FlightVec *);
static inline void Item_ComputeYawRelativeApproach_ByValue(FlightVec *a0, void *a1, FlightVec a2, FlightVec a3) { Item_ComputeYawRelativeApproach(a0, a1, &a2, &a3); }
#define Item_ComputeYawRelativeApproach Item_ComputeYawRelativeApproach_ByValue
#endif
float Vec3_ToYaw(const FlightVec *);
void Vec3_Add_DestFirst(FlightVec *,const FlightVec *,const FlightVec *);
int Item_CheckWallCollision(FlightItem *,FlightVec *,void *);
float BuildOrientationFromYaw(float);
int Item_AdvanceProjectileSimple(FlightItem *,float *,float,float);
float Vec3_ToPitch(const FlightVec *);
float AngleStepTowards_Shortest(float,float,float);
double sin(double);
int Item_AdvanceFallingDrop(FlightItem *,int *,float *,float);
float Vec3_Magnitude_Wrapper(const FlightVec *);
#ifdef __MWERKS__
void DrawEffect_ItemHitOriented_Spawn(FlightVec,FlightVec,int);
#else
/* The definition takes these structs by address; see docs/notes/port_abi.md. */
extern void DrawEffect_ItemHitOriented_Spawn(FlightVec *, FlightVec *, int);
static inline void DrawEffect_ItemHitOriented_Spawn_ByValue(FlightVec a0, FlightVec a1, int a2) { DrawEffect_ItemHitOriented_Spawn(&a0, &a1, a2); }
#define DrawEffect_ItemHitOriented_Spawn DrawEffect_ItemHitOriented_Spawn_ByValue
#endif
#ifdef __MWERKS__
float Item_ProbeForwardGroundPitch(FlightVec,float,float,float);
#else
/* The definition takes these structs by address; see docs/notes/port_abi.md. */
extern float Item_ProbeForwardGroundPitch(FlightVec *, float, float, float);
static inline float Item_ProbeForwardGroundPitch_ByValue(FlightVec a0, float a1, float a2, float a3) { return Item_ProbeForwardGroundPitch(&a0, a1, a2, a3); }
#define Item_ProbeForwardGroundPitch Item_ProbeForwardGroundPitch_ByValue
#endif
float AngleStepForward_OrSnap(float,float,float);
void Vec3_Scale(FlightVec *,const FlightVec *,float);
}
#define SET_REASON(n) do { item->state=2; item->phase=0; item->reason=(n); } while(0)
static inline void InitializeParticle(FlightEffect *effect, FlightItem *item, FlightContext *context, int kind, float angle)
{
    FlightVec velocity;
    effect->enabled=1;
    Vec3_Copy(&effect->position,&item->position);
    GetSpawnPosition(&velocity,0.0f,0.0f,Rand_RangeFloat(lbl_806D62C4,lbl_806D62C8));
    if(kind==0) {
        Vec2_RotateX(&velocity,&velocity,lbl_806D62CC*Rand_RangeFloat(lbl_806D62D0,lbl_806D62D4));
        Vec2_RotateY(&velocity,&velocity,lbl_806D62CC*Rand_RangeFloat(lbl_806D62D8,lbl_806D62DC));
    } else if(kind==1) {
        GetSpawnPosition(&velocity,lbl_806D62C0,lbl_806D62C0,lbl_806D62C0);
    } else if(kind==2) {
        Vec2_RotateX(&velocity,&velocity,lbl_806D62CC*Rand_RangeFloat(lbl_806D62D0,lbl_806D62D4));
        Vec2_RotateY(&velocity,&velocity,BuildOrientationFromYaw(lbl_806D62CC*Rand_RangeFloat(lbl_806D62E0,lbl_806D62E4)+angle));
    } else {
        Vec2_RotateY(&velocity,&velocity,lbl_806D62CC*Rand_RangeFloat(lbl_806D62D8,lbl_806D62DC));
        Vec2_RotateX(&velocity,&velocity,BuildOrientationFromYaw(lbl_806D62CC*Rand_RangeFloat(lbl_806D62E8,lbl_806D62E0)+item->pitch));
        Vec2_RotateY(&velocity,&velocity,item->yaw);
    }
    Vec3_Copy(&effect->velocity,&velocity);
    effect->target=context->target;
    if(kind==1) effect->id=item->effectId;
}
#define PARTICLES(kind,angle) for(i=0;i<8;++i) { FlightEffect *effect=DrawEffect_SpawnDirect(Effect_HitFlash_Update); if(effect) InitializeParticle(effect,item,context,kind,angle); }
extern "C" void GabyouItem_FlightAndLockOnTick(FlightItem *item,FlightContext *context)
{
    FlightVec hand,wall;
    int alive,hitGround,i;
    float height,angle;
    switch(item->phase) {
    case 0:
        if(item->launched) {
            Item_BendVelocityByGroundProbe(&item->velocity,item->position,item->yaw,lbl_806D6314,0.0f);
            KartDriver_TransformWorldToLocalY0(&item->position,item->position,context->kart);
            item->speed=lbl_806D6300; item->lifetime=lbl_806D62C4;
            item->active=1; item->phase=2; item->flightPhase=0; return;
        }
        ++item->phase; item->flightPhase=0;
    case 1:
        switch(item->flightPhase) {
        case 0:
            SpriteSlot_SetMatrixSourceEnabled_WithReseed(item->sprite,1);
            context->sprite=ItemObject_AllocGabyou(); item->active=1; item->lifetime=lbl_806D62C0;
            ++item->flightPhase;
        case 1:
            Item_RenderFlyingFromKart(item,context->sprite,1,lbl_806D62C0,lbl_806D62C0,lbl_806D6318);
            if(FinalLapCoinJump_CheckActiveForObject(context->kart)) item->active=0; else item->active=1;
            switch(context->command) {
            case 1:
                item->active=1; context->command=0;
                SpriteSlot_SetMatrixSourceEnabled_WithReseed(item->sprite,0);
                SpriteSlot_Container_Free(context->sprite); context->sprite=0;
                Item_InitLaunchFromKart(item,0,lbl_806D6314,lbl_806D62C0);
                ++item->phase; item->flightPhase=0; break;
            case 2:
                context->command=0; SpriteSlot_Container_Free(context->sprite); context->sprite=0;
                item->active=0; item->state=3; item->phase=0; break;
            }
        }
        return;
    case 2:
        switch(item->flightPhase) {
        case 3:
        case 4:
            break;
        case 0:
            ItemTracker_AcquireLock(item); ItemTracker_SetTrackPhase(item,1);
            item->lockState=1; item->flag3C=1;
            ItemObject_GetGroundTypeAt(item->position,&context->ground,0);
            context->ground=item->position.y-context->ground;
            context->timer=30; context->effectTimer=0; context->trackTimer=0; ++item->flightPhase;
        case 1:
            Item_AccelClampVelocity(item,g_ccClass==0?lbl_806D631C:lbl_806D631C,g_ccClass==0?lbl_806D62C4:lbl_806D6300);
            fn_801B129C(&item->position);
            Item_HomingScanAndSteer(item,&item->yaw,1);
            if(context->timer==0) ++item->flightPhase;
            break;
        case 2:
            item->velocity.y+=lbl_806D6320;
            Item_HomingScanAndSteer(item,&item->yaw,1); break;
        }
        Item_DecayVelocityScalar(item,lbl_806D6300);
        switch(ItemCollision_Check(item)) {
        case 1: {
            fn_801B1D5C(context->kart,ItemTracker_GetTargetKart(item),(short)ItemAlias_HitRemapLookup(item->alias),0);
            ItemHit_Dispatch(item,0,0,0); context->target=ItemTracker_GetTargetKart(item);
            ItemTracker_ReleaseLock(item); item->lockState=0;
            SoundMgr_PlaySE_Positional(0x84,item->position,0);
            PARTICLES(0,0.0f)
            Mtx44_GetTranslation_RowMajor(&hand,KartDriver_GetJointByIdx(context->target,15));
            if(fn_800D3184(&item->position,&hand)<lbl_806D6324) {SET_REASON(0); return;}
            item->velocity.y=lbl_806D6300; item->velocity.x*=lbl_806D6328; item->velocity.z*=lbl_806D6328;
            SET_REASON(1); return;
        }
        case 2:
            fn_801B1660(context->kart,ItemTracker_GetTargetKart(item));
            context->target=ItemTracker_GetTargetKart(item); ItemTracker_ReleaseLock(item); item->lockState=0;
            SoundMgr_PlaySE_Positional(0x84,item->position,0);
            item->velocity.y=lbl_806D6300; item->velocity.x*=lbl_806D6328; item->velocity.z*=lbl_806D6328;
            SET_REASON(1); return;
        case 3:
            fn_801B158C(context->kart,ItemTracker_GetTargetKart(item)); context->field7C=0;
            Item_ComputeYawRelativeApproach(&item->velocity,ItemTracker_GetTargetKart(item),item->position,item->velocity);
            item->yaw=Vec3_ToYaw(&item->velocity); ItemTracker_SetTrackPhase(item,0); context->trackTimer=5; break;
        case 4:
            fn_801B14B8(context->kart,ItemTracker_GetTargetKart(item));
            context->target=ItemTracker_GetTargetKart(item); ItemTracker_ReleaseLock(item); item->lockState=0;
            SET_REASON(3); return;
        case 5: ItemTracker_SetTrackPhase(item,1); break;
        }
        if(context->trackTimer==0) ItemTracker_SetTrackPhase(item,1);
        if(item->lockState==2) {
            ItemTracker_ReleaseLock(item);
            i=0;
            item->lockState=0;
            if(item->lockKind==1) {
                SoundMgr_PlaySE_Positional(0x84,item->position,0);
                PARTICLES(0,0.0f)
                Vec3_Add_DestFirst(&item->velocity,&item->velocity,&item->impulse);
                item->velocity.y=lbl_806D6300; item->velocity.x*=lbl_806D632C; item->velocity.z*=lbl_806D632C;
                SET_REASON(4); return;
            }
            for(;i<8;++i) { FlightEffect *effect=DrawEffect_SpawnDirect(Effect_HitFlash_Update); if(effect) InitializeParticle(effect,item,context,1,0.0f); }
            SET_REASON(6); return;
        }
        if(Item_CheckWallCollision(item,&wall,0)) {
            GetSpawnPosition(&item->velocity,lbl_806D62C0,lbl_806D62C0,lbl_806D62C0);
            if(item->flightPhase==1 || item->flightPhase==2) {
                ItemTracker_ReleaseLock(item); item->lockState=0; context->ground=Vec3_ToYaw(&wall);
                SoundMgr_PlaySE_Positional(0x84,item->position,0);
                angle=context->ground;
                PARTICLES(2,angle)
                SET_REASON(7); return;
            }
        }
        if(item->flightPhase==1) {
            alive=Item_AdvanceProjectileSimple(item,&context->ground,lbl_806D6330,lbl_806D6330);
            item->pitch=AngleStepTowards_Shortest(item->pitch,lbl_806D62F8+Vec3_ToPitch(&item->velocity),lbl_806D62FC);
        } else {
            if(item->flightPhase!=4) angle=lbl_806D630C*(float)sin(item->pitch);
            else angle=lbl_806D62C0;
            alive=Item_AdvanceFallingDrop(item,&hitGround,&height,angle);
            if(alive) switch(item->flightPhase) {
            case 2:
                item->pitch=AngleStepTowards_Shortest(item->pitch,lbl_806D62F8+Vec3_ToPitch(&item->velocity),lbl_806D62FC);
                if(hitGround) {
                    SoundMgr_PlaySE_Positional(0x84,item->position,0); context->ground=Vec3_Magnitude_Wrapper(&item->velocity);
                    GetSpawnPosition(&item->velocity,lbl_806D62C0,lbl_806D62C0,lbl_806D6334*context->ground);
                    Vec2_RotateY(&item->velocity,&item->velocity,item->yaw); ++item->flightPhase; return;
                }
                break;
            case 3: {
                float groundPitch;
                item->position.y=angle*item->speed+height;
                if(context->effectTimer==0) {
                    DrawEffect_ItemHitOriented_Spawn(item->position,item->velocity,2); context->effectTimer=3;
                }
                groundPitch=BuildOrientationFromYaw(lbl_806D6338+Item_ProbeForwardGroundPitch(item->position,item->yaw,lbl_806D630C,item->position.y-height));
                item->pitch=AngleStepForward_OrSnap(item->pitch,groundPitch,lbl_806D62FC);
                if(item->pitch==groundPitch) {
                    PARTICLES(3,0.0f)
                    GetSpawnPosition(&item->velocity,lbl_806D62C0,lbl_806D62C0,lbl_806D633C*context->ground);
                    Vec2_RotateY(&item->velocity,&item->velocity,item->yaw); ++item->flightPhase; return;
                }
                break;
            }
            case 4:
                item->position.y=height;
                if(context->effectTimer==0) {
                    DrawEffect_ItemHitOriented_Spawn(item->position,item->velocity,2); context->effectTimer=3;
                }
                item->pitch=BuildOrientationFromYaw(lbl_806D6338+Item_ProbeForwardGroundPitch(item->position,item->yaw,lbl_806D630C,lbl_806D62C0));
                Vec3_Scale(&item->velocity,&item->velocity,lbl_806D6340); item->velocity.y=lbl_806D62C0;
                if(Vec3_Magnitude_Wrapper(&item->velocity)<lbl_806D6344) {
                    ItemTracker_ReleaseLock(item); item->lockState=0;
                    GetSpawnPosition(&item->velocity,lbl_806D62C0,lbl_806D62C0,lbl_806D62C0); SET_REASON(8); return;
                }
                break;
            }
        }
        if(!alive) {ItemTracker_ReleaseLock(item); item->lockState=0; SET_REASON(9);}
        break;
    }
}
