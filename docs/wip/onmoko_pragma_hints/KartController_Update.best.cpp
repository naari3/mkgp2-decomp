#include "game/KartControllerUpdatePrivate.h"
#pragma use_lmw_stmw on
#pragma inline_max_size(10000)
#pragma inline_max_total_size(100000)
static inline void TransformOffset(const KCMatrix *matrix, KCVec *offset) {
    float mtx[12];
    Mtx4x4_TransposeTo4x3(matrix,mtx);
    PSMTXMultVec(mtx,offset,offset);
}
#pragma push
#pragma opt_common_subs off
extern "C" void KartController_Update(AIKart *self) {
    const char *data=KartController_Update_rodata_803BD320;
    if (!self->path) return;
    self->previous.x=self->position.x;
    self->previous.y=self->position.y;
    self->previous.z=self->position.z;
    if (fn_801DF358(self->steering.p)) PhysicsState_SetAccel(self->run.p,0);
    else PhysicsState_SetAccel(self->run.p,1);
    if (fn_801DF318(self->steering.p)) PhysicsState_SetBrake(self->run.p,0);
    else PhysicsState_SetBrake(self->run.p,1);
    void *aux=self->aux.p;
    float scale=fn_801DF310(self->steering.p);
    scale=fn_801DEC44(aux)*scale;
    if(scale<lbl_806DA390) PhysicsState_SetSpeedImmediate(self->run.p,self->f90*scale,self->f8c*scale);
    else PhysicsState_AccelInterpolate(self->run.p,self->f90*scale,self->f8c*scale);
    void *physics=self->run.p;
    PhysicsState_SetField90(physics,fn_801DEC54(self->aux.p));
    physics=self->run.p;
    PhysicsState_SetField94(physics,fn_801DEC4C(self->aux.p));
    int grounded=0;
    if(fn_801DF398(self->steering.p)==0 && !fn_801DEC5C(self->aux.p)) grounded=1;
    PhysicsState_SetGrounded(self->run.p,grounded);
    PhysicsState_SetFlag188(self->run.p,0);
    void *warp=WarpDashMgr_GetInstance(0);
    int zone=WarpZone_FindContaining(warp,self->position.x,self->position.y,self->position.z);
    if ((zone!=-1 && g_cupId==7) || zone==*(int *)((char *)self->driver.p+0x24c)) {
        AIPosition exit;
        float angle;
        WarpZone_CalcExitPosition(warp,zone,&exit.x,&exit.y,&exit.z,&angle,self->position.x,self->position.y,self->position.z);
        PhysicsState_SetPosition(self->run.p,&exit);
        fn_801EC830(self->run.p,angle);
        fn_801ECA14(self->run.p);
        RenderObj_ToggleLapSegment(self->driver.p,-1);
        PhysicsState_SetFlag188(self->run.p,1);
    }
    KartPhysics_UpdateSmoothing(self->run.p);
    physics=self->run.p;
    fn_801EC7B4(physics,fn_801DF308(self->steering.p));
    void *steering=self->steering.p;
    fn_801DF008(steering,fn_801EC784(self->run.p));
    fn_801DF3B0(self->steering.p);
    fn_801DEC74(self->aux.p);
    if(fn_801DEC3C(self->aux.p)) fn_801ECB04(self->run.p);
    void *bus=*(void **)((char *)self->driver.p+0x304);
    ItemEffectBus_SnapshotAndFullReset(bus);
    ((KCDispatch *)self)->collision(PhysicsState_GetCollisionKartIdx(self->run.p));
    KCMatrix mat;
    mat.multiply(fn_801DF3A8(self->steering.p));
    mat.multiply(fn_801DEC6C(self->aux.p));
    mat.multiply(PhysicsState_GetOrientMatrixPtr(self->run.p));
    AIPosition *pos=PhysicsState_GetPositionPtr(self->run.p);
    self->position.x=pos->x; self->position.y=pos->y; self->position.z=pos->z;
    mat.m[3][0]=self->position.x; mat.m[3][1]=self->position.y; mat.m[3][2]=self->position.z;
    mat.multiply(fn_801DF3A0(self->steering.p));
    KCMatrix scaled;
    scaled.m[0][0]=scaled.m[1][1]=scaled.m[2][2]=lbl_806DA3B8;
    scaled.multiply(&mat);
    mat=scaled;
    KCVec rotation,bounds,center,velocity;
    velocity.x=(self->position.x-self->previous.x)*lbl_806DA38C;
    velocity.y=(self->position.y-self->previous.y)*lbl_806DA38C;
    velocity.z=(self->position.z-self->previous.z)*lbl_806DA38C;
    PSMTXMultVec(KartDriver_GetKartRootMtx(self->driver.p),data+0x438,&center);
    PSVECAdd(&center,&velocity,&center);
    bounds=*(KCVec *)(data+0x3fc);
    PSVECScale(&bounds,&bounds,self->fa4);
    float z=Object_GetJObjRotationZ(KartDriver_GetJObjRootIfReady(self->driver.p));
    float heading=PhysicsState_GetHeading(self->run.p);
    rotation.x=Object_GetJObjRotationX(KartDriver_GetJObjRootIfReady(self->driver.p));
    rotation.y=heading; rotation.z=z;
    CollisionObject_SetPosAndBounds(self->extra.p,&center,&rotation,bounds.x,bounds.y,bounds.z);
    PhysicsState_SetCollidedObject(self->run.p,self->extra.p);
    Mtx4x4_TransposeTo4x3(&mat,self->matrix);
    float speed=PhysicsState_GetSpeed(self->run.p);
    float angular=PhysicsState_GetAngularVelocity(self->run.p);
    RenderObj_ItemStateMachine_Timed(self->driver.p,0,angular,speed);
    void *tornado=self->tornado.p;
    TornadoEffect_SetScalePairB0BC(tornado,lbl_806DA388,lbl_806DA390);
    KCVec offset,normal,right,left;
    float ground;
    int color,c0=0,c1=0;
    const float *coords=(const float *)(data+0x408);
    left.x=mat.m[3][0]+(coords[11]*mat.m[2][0]+(mat.m[0][0]*coords[9]+coords[10]*mat.m[1][0]));
    left.y=mat.m[3][1]+(coords[11]*mat.m[2][1]+(mat.m[0][1]*coords[9]+coords[10]*mat.m[1][1]));
    left.z=mat.m[3][2]+(coords[11]*mat.m[2][2]+(coords[9]*mat.m[0][2]+coords[10]*mat.m[1][2]));
    right.x=mat.m[3][0]+(coords[8]*mat.m[2][0]+(mat.m[0][0]*coords[6]+coords[7]*mat.m[1][0]));
    right.y=mat.m[3][1]+(coords[8]*mat.m[2][1]+(mat.m[0][1]*coords[6]+coords[7]*mat.m[1][1]));
    right.z=mat.m[3][2]+(coords[8]*mat.m[2][2]+(coords[6]*mat.m[0][2]+coords[7]*mat.m[1][2]));
    if(Terrain_GetGroundHeightWithPenetration(&left,&ground,&normal,&color,lbl_806DA394)) c0=color;
    if(Terrain_GetGroundHeightWithPenetration(&right,&ground,&normal,&color,lbl_806DA394)) c1=color;
    TornadoEffect_SetColorPairC8CC(tornado,c0,c1);
    const KCVec *offsetData=(const KCVec *)(data+0x444);
    offset.x=offsetData->x; offset.y=offsetData->y; offset.z=offsetData->z;
    TransformOffset(&mat,&offset);
    TornadoEffect_SetMatrixRow0_5c(tornado,offset.x,offset.y,offset.z);
    TornadoEffect_SetMatrix1c(tornado,&mat);
    TornadoEffect_Tick(self->tornado.p,6);
    if(ShadowAreaMgr_QueryPoint(g_shadowAreaMgr,mat.m[3][0],mat.m[3][1],mat.m[3][2])==1) TornadoEffect_TriggerField140(self->tornado.p);
    AI_UpdateItemEffects(self);
    ItemEffectBus_TickTornadoCooldown(bus);
    if(fn_801DE6E0(GetEnemyParam())) {
        void *pathpos=(char *)self->kartId+0x14;
        float s=PhysicsState_GetSpeed(self->run.p)/lbl_806DA3BC/lbl_806DA394;
        int a=fn_801EC700(self->run.p);
        int b=fn_801EC698(self->run.p);
        OverlayText(1,1,pathpos,data+0x480,self->kartId,a,b,s);
    }
}
#pragma pop

#pragma use_lmw_stmw reset
