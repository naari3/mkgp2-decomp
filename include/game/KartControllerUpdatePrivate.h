#ifndef KART_CONTROLLER_UPDATE_PRIVATE_H
#define KART_CONTROLLER_UPDATE_PRIVATE_H
#include "game/AIKartInitPrivate.h"
extern "C" {
extern const float lbl_806DA388, lbl_806DA38C, lbl_806DA390;
extern const float lbl_806DA394, lbl_806DA3B8, lbl_806DA3BC;
}
struct KCVec { float x,y,z; };
struct KCMatrix {
    float m[4][4];
    KCMatrix() {
        m[3][3]=m[2][2]=m[1][1]=m[0][0]=lbl_806DA388;
        m[1][3]=m[1][2]=m[1][0]=m[0][3]=m[0][2]=m[0][1]=lbl_806DA388;
        m[3][2]=m[3][1]=m[3][0]=m[2][3]=m[2][1]=m[2][0]=lbl_806DA388;
        m[0][0]=m[1][1]=m[2][2]=m[3][3]=lbl_806DA390;
    }
    void setTranslation(const AIPosition &position) {
        float z=position.z, y=position.y, x=position.x;
        m[3][0]=x; m[3][1]=y; m[3][2]=z;
    }
    KCMatrix &operator*=(const KCMatrix &b) {
        float out[16];
        const float *row=&m[0][0];
        const float *column;
        float *output=out;
        const float *right=&b.m[0][0];
        int n=0;
        for (int i=0; i<4; ++i) {
            column=right;
            for(int j=0;j<4;++j,++column) {
                float v=row[0]*column[0];
                v+=row[1]*column[4];
                v+=row[2]*column[8];
                v+=row[3]*column[12];
                output[n+j]=v;
            }
            row+=4;
            n+=4;
        }
        for(int i=0;i<16;++i) (&m[0][0])[i]=out[i];
        return *this;
    }
};
struct KCDispatch {
    virtual void s08(); virtual void s0c(); virtual void s10(); virtual void s14();
    virtual void s18(); virtual void s1c(); virtual void s20(); virtual void s24();
    virtual void s28(); virtual void s2c(); virtual void s30(); virtual void s34();
    virtual void collision(int);
};
extern "C" {
extern int g_cupId;
extern void *g_shadowAreaMgr;
unsigned char fn_801DF358(void *),fn_801DF318(void *),fn_801DEC5C(void *),fn_801DEC3C(void *);
float fn_801DF310(void *),fn_801DEC44(void *),fn_801DEC54(void *),fn_801DEC4C(void *);
int fn_801DF398(void *),fn_801DF308(void *),fn_801EC784(void *);
void PhysicsState_SetAccel(void *,int),PhysicsState_SetBrake(void *,int);
void PhysicsState_SetSpeedImmediate(void *,float,float),PhysicsState_AccelInterpolate(void *,float,float);
void PhysicsState_SetField90(void *,float),PhysicsState_SetField94(void *,float);
void PhysicsState_SetGrounded(void *,int),PhysicsState_SetFlag188(void *,int);
void *WarpDashMgr_GetInstance(int);
int WarpZone_FindContaining(void *,float,float,float);
void WarpZone_CalcExitPosition(void *,int,float *,float *,float *,float *,float,float,float);
void PhysicsState_SetPosition(void *,AIPosition *),fn_801EC830(void *,float),fn_801ECA14(void *);
void RenderObj_ToggleLapSegment(void *,int),KartPhysics_UpdateSmoothing(void *);
void fn_801EC7B4(void *,int),fn_801DF008(void *,int),fn_801DF3B0(void *),fn_801DEC74(void *),fn_801ECB04(void *);
void ItemEffectBus_SnapshotAndFullReset(void *);
int PhysicsState_GetCollisionKartIdx(void *);
KCMatrix *fn_801DF3A8(void *),*fn_801DEC6C(void *),*PhysicsState_GetOrientMatrixPtr(void *),*fn_801DF3A0(void *);
AIPosition *PhysicsState_GetPositionPtr(void *);
void *KartDriver_GetKartRootMtx(void *),*KartDriver_GetJObjRootIfReady(void *);
void PSMTXMultVec(const void *,const void *,void *),PSVECAdd(const void *,const void *,void *),PSVECScale(const void *,void *,float);
float Object_GetJObjRotationZ(void *),Object_GetJObjRotationX(void *),PhysicsState_GetHeading(void *);
void CollisionObject_SetPosAndBounds(void *,const void *,const void *,float,float,float);
void PhysicsState_SetCollidedObject(void *,void *),Mtx4x4_TransposeTo4x3(const void *,void *);
float PhysicsState_GetSpeed(void *),PhysicsState_GetAngularVelocity(void *);
void RenderObj_ItemStateMachine_Timed(void *,int,float,float);
void TornadoEffect_SetScalePairB0BC(void *,float,float),TornadoEffect_SetColorPairC8CC(void *,int,int);
unsigned char Terrain_GetGroundHeightWithPenetration(const void *,float *,void *,int *,float);
void TornadoEffect_SetMatrixRow0_5c(void *,float,float,float),TornadoEffect_SetMatrix1c(void *,const void *),TornadoEffect_Tick(void *,int);
unsigned char ShadowAreaMgr_QueryPoint(void *,float,float,float);
void TornadoEffect_TriggerField140(void *),AI_UpdateItemEffects(AIKart *),ItemEffectBus_TickTornadoCooldown(void *);
void *GetEnemyParam();
unsigned char fn_801DE6E0(void *);
int fn_801EC700(void *),fn_801EC698(void *);
void OverlayText(int,int,void *,const char *,...);
}
#endif
