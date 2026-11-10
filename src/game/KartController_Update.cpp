#include "game/KartControllerUpdatePrivate.h"
#pragma use_lmw_stmw on
#pragma force_active on
extern "C" {
// Shared AI tuning curves, followed by kart bounds and attachment offsets.
static const float KartController_Update_rodata_803BD320[255] = {
    1.0f, 0.7f, 0.9f, 0.0f, 0.0f, 500.0f, 66.6666718f,
    1000.0f, 66.6666718f, 2000.0f, 66.6666718f, 3000.0f, 66.6666718f, 4000.0f,
    66.6666718f, 5000.0f, 66.6666718f, 0.0f, 0.0f, 500.0f, 66.6666718f,
    1000.0f, 66.6666718f, 2000.0f, 66.6666718f, 3000.0f, 66.6666718f, 4000.0f,
    66.6666718f, 5000.0f, 66.6666718f, 0.0f, 0.0f, 500.0f, 66.6666718f,
    1000.0f, 66.6666718f, 2000.0f, 66.6666718f, 3000.0f, 66.6666718f, 4000.0f,
    66.6666718f, 5000.0f, 66.6666718f, 0.0f, 0.0f, 500.0f, 66.6666718f,
    1000.0f, 66.6666718f, 2000.0f, 66.6666718f, 3000.0f, 66.6666718f, 4000.0f,
    66.6666718f, 5000.0f, 66.6666718f, 0.0f, 0.0f, 500.0f, 66.6666718f,
    1000.0f, 66.6666718f, 2000.0f, 66.6666718f, 3000.0f, 66.6666718f, 4000.0f,
    66.6666718f, 5000.0f, 66.6666718f, 0.0f, 0.0f, 500.0f, 66.6666718f,
    1000.0f, 66.6666718f, 2000.0f, 66.6666718f, 3000.0f, 66.6666718f, 4000.0f,
    66.6666718f, 5000.0f, 66.6666718f, 0.0f, 0.0f, 500.0f, 66.6666718f,
    1000.0f, 66.6666718f, 2000.0f, 66.6666718f, 3000.0f, 66.6666718f, 4000.0f,
    66.6666718f, 5000.0f, 66.6666718f, 0.0f, 0.0f, 500.0f, 66.6666718f,
    1000.0f, 66.6666718f, 2000.0f, 66.6666718f, 3000.0f, 66.6666718f, 4000.0f,
    66.6666718f, 5000.0f, 66.6666718f, 0.0f, 0.0f, 500.0f, 66.6666718f,
    1000.0f, 66.6666718f, 2000.0f, 66.6666718f, 3000.0f, 66.6666718f, 4000.0f,
    66.6666718f, 5000.0f, 66.6666718f, 0.0f, 0.0f, 500.0f, 66.6666718f,
    1000.0f, 66.6666718f, 2000.0f, 66.6666718f, 3000.0f, 66.6666718f, 4000.0f,
    66.6666718f, 5000.0f, 66.6666718f, 0.0f, 0.0f, 500.0f, 66.6666718f,
    1000.0f, 66.6666718f, 2000.0f, 66.6666718f, 3000.0f, 66.6666718f, 4000.0f,
    66.6666718f, 5000.0f, 66.6666718f, 0.0f, 0.0f, 500.0f, 66.6666718f,
    1000.0f, 66.6666718f, 2000.0f, 66.6666718f, 3000.0f, 66.6666718f, 4000.0f,
    66.6666718f, 5000.0f, 66.6666718f, 0.0f, 0.0f, 500.0f, 83.3333359f,
    1000.0f, 83.3333359f, 2000.0f, 83.3333359f, 3000.0f, 83.3333359f, 4000.0f,
    83.3333359f, 5000.0f, 83.3333359f, 0.0f, 0.0f, 500.0f, 83.3333359f,
    1000.0f, 83.3333359f, 2000.0f, 83.3333359f, 3000.0f, 83.3333359f, 4000.0f,
    83.3333359f, 5000.0f, 83.3333359f, 0.0f, 0.0f, 500.0f, 83.3333359f,
    1000.0f, 83.3333359f, 2000.0f, 83.3333359f, 3000.0f, 83.3333359f, 4000.0f,
    83.3333359f, 5000.0f, 83.3333359f, 0.0f, 0.0f, 500.0f, 83.3333359f,
    1000.0f, 83.3333359f, 2000.0f, 83.3333359f, 3000.0f, 83.3333359f, 4000.0f,
    83.3333359f, 5000.0f, 83.3333359f, 0.0f, 0.0f, 500.0f, 83.3333359f,
    1000.0f, 83.3333359f, 2000.0f, 83.3333359f, 3000.0f, 83.3333359f, 4000.0f,
    83.3333359f, 5000.0f, 83.3333359f, 0.0f, 0.0f, 500.0f, 83.3333359f,
    1000.0f, 83.3333359f, 2000.0f, 83.3333359f, 3000.0f, 83.3333359f, 4000.0f,
    83.3333359f, 5000.0f, 83.3333359f,
};
static const KCVec lbl_803BD71C = {9.6f, 9.6f, 12.0f};
static const KCVec lbl_803BD728[4] = {
    {7.20000029f, 0.0f, 9.6f},
    {-7.20000029f, 0.0f, 9.6f},
    {7.20000029f, 0.0f, -9.6f},
    {-7.20000029f, 0.0f, -9.6f},
};
static const KCVec lbl_803BD758 = {0.0f, 4.8f, 2.4f};
static const KCVec lbl_803BD764 = {0.0f, 12.0f, 0.0f};
#include "game/types/shared_data.h"
SHARED_STATIC const int KartController_Update_rodata_803BD770[3] = {73,43,62};
SHARED_STATIC const char lbl_803BD77C[13] = "clEnemyThink";
SHARED_STATIC const char lbl_803BD78C[19] = "clItemBoxResponder";
static const char lbl_803BD7A0[38] = "GRID %d: speed %6.2f(km/h) line %d-%d";
}
#pragma force_active reset

#pragma inline_max_size(10000)
#pragma inline_max_total_size(100000)
static inline void TransformOffset(const KCMatrix *matrix, KCVec *offset) {
    float mtx[12];
    Mtx4x4_TransposeTo4x3(matrix,mtx);
    PSMTXMultVec(mtx,offset,offset);
}
static inline void *UpdateTerrainColors(AIKart *self, const KCMatrix &mat, KCVec &left, KCVec &right, KCVec &normal, float &ground, int &color) {
    void *tornado=self->tornado.p;
    TornadoEffect_SetScalePairB0BC(tornado,lbl_806DA388,lbl_806DA390);
    int c0,c1; // Inline locals permit the shared zero to coalesce.
    c0=0; c1=0;
    const KCVec *coords=lbl_803BD728;
    const KCMatrix &matrix=mat;
    const KCVec &a=coords[3], &b=coords[2];

    float ax=a.x, ay=a.y, az=a.z;
    float bx=b.x, by=b.y, bz=b.z;
    float lx=ay*matrix.m[1][0];
    float ly=ay*matrix.m[1][1];
    float lz=ay*matrix.m[1][2];
    float rx=by*matrix.m[1][0];
    float ry=by*matrix.m[1][1];
    float rz=by*matrix.m[1][2];
    lx+=matrix.m[0][0]*ax;
    ly+=matrix.m[0][1]*ax;
    lz+=ax*matrix.m[0][2];
    rx+=matrix.m[0][0]*bx;
    ry+=matrix.m[0][1]*bx;
    rz+=bx*matrix.m[0][2];
    lx+=az*matrix.m[2][0];
    ly+=az*matrix.m[2][1];
    lz+=az*matrix.m[2][2];
    rx+=bz*matrix.m[2][0];
    ry+=bz*matrix.m[2][1];
    rz+=bz*matrix.m[2][2];
    left.x=matrix.m[3][0]+lx;
    left.y=matrix.m[3][1]+ly;
    left.z=matrix.m[3][2]+lz;
    right.x=matrix.m[3][0]+rx;
    right.y=matrix.m[3][1]+ry;
    right.z=matrix.m[3][2]+rz;

    if(Terrain_GetGroundHeightWithPenetration(&left,&ground,&normal,&color,lbl_806DA394)) c0=color;
    if(Terrain_GetGroundHeightWithPenetration(&right,&ground,&normal,&color,lbl_806DA394)) c1=color;
    TornadoEffect_SetColorPairC8CC(tornado,c0,c1);
    return tornado;
}
extern "C" void KartController_Update(AIKart *self) {
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
    KCMatrix *mp=&mat; /* &mat stays in r29 across the three multiplies (regalloc_patterns 14) */
    *mp *= *fn_801DF3A8(self->steering.p);
    *mp *= *fn_801DEC6C(self->aux.p);
    *mp *= *PhysicsState_GetOrientMatrixPtr(self->run.p);
    AIPosition *pos=PhysicsState_GetPositionPtr(self->run.p);
    self->position.x=pos->x; self->position.y=pos->y; self->position.z=pos->z;
    mat.setTranslation(self->position);
    mat *= *fn_801DF3A0(self->steering.p);
    KCMatrix scaled;
    scaled.m[2][2]=scaled.m[1][1]=scaled.m[0][0]=lbl_806DA3B8;
    scaled *= mat;
    mat=scaled;
    KCVec rotation,bounds,center,velocity;
    velocity.x=(self->position.x-self->previous.x)*lbl_806DA38C;
    velocity.y=(self->position.y-self->previous.y)*lbl_806DA38C;
    velocity.z=(self->position.z-self->previous.z)*lbl_806DA38C;
    PSMTXMultVec(KartDriver_GetKartRootMtx(self->driver.p),&lbl_803BD758,&center);
    PSVECAdd(&center,&velocity,&center);
    bounds=lbl_803BD71C;
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
    KCVec offset,normal,right,left;
    float ground;
    int color;
    void *tornado=UpdateTerrainColors(self,mat,left,right,normal,ground,color);
    const KCVec *offsetData=&lbl_803BD764;
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
        OverlayText(1,1,pathpos,lbl_803BD7A0,self->kartId,a,b,s);
    }
}
#pragma use_lmw_stmw reset
