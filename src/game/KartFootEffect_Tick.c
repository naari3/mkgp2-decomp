/* Actor is opaque in Ghidra; named accessors document the observed layout. */
typedef struct Vec { float x,y,z; } Vec;
extern unsigned char lbl_80329908[];
extern unsigned char lbl_805DF3D0[];
extern const float lbl_806D5168,lbl_806D516C,lbl_806D5170,lbl_806D5174,lbl_806D5178;
extern const float lbl_806D517C,lbl_806D5180,lbl_806D5184,lbl_806D5188,lbl_806D518C;
extern const float lbl_806D5190,lbl_806D5194,lbl_806D5198;
extern void *KartDriver_GetKartRootMtx(void *);
extern void Mtx44_GetTranslation_RowMajor(Vec *,void *);
extern void VfxSlot_BindResourceEx(void *,unsigned int,int);
extern void Vec3_Subtract_DestFirst(Vec *,const Vec *,const Vec *);
extern void Vec3_Add_DestFirst(Vec *,const Vec *,const Vec *);
extern float fn_800D3184(const Vec *,const Vec *);
extern float Vec3_Magnitude_Wrapper(const Vec *);
extern void Vec3_Scale(float,Vec *,const Vec *);
extern void VfxSlot_SetPositionFromVec(void *,const Vec *);
extern void VfxSlot_SetRotationZ(float,void *);
extern void VfxSlot_SetScaleUniform(float,void *);
extern void DrawEffect_Free(void *);
#define F(o) (*(float *)(self+(o)))
#define V(o) ((Vec *)(self+(o)))
#define DRIVER (*(void **)(self+0x11c))
#define BANK ((signed char)self[0x190])
#define ROLE ((signed char)self[0x191])
#define SLOT ((signed char)self[0x192])
void KartFootEffect_Tick(unsigned char *self) {
    Vec parent,delta,pos,attractor;
    float t0,t1,t2,s0,s1,s2,a0,a1,a2,phase,blend;
    Vec *camera;
    float *keys;
    unsigned char *data=lbl_80329908;
    if (DRIVER) Mtx44_GetTranslation_RowMajor(&parent,KartDriver_GetKartRootMtx(DRIVER));
    switch ((signed char)self[0xb4]) {
    case 0:
        self[0x1c]=(data+0x4b0)[BANK*9+ROLE*3+SLOT];
        VfxSlot_BindResourceEx(self+0x14,self[0x1c],0);
        if (ROLE==1) F(0xa0)=lbl_806D5168*((float *)(data+0x4e8))[SLOT];
        F(0x150)=lbl_806D516C;
        F(0x154)=((float (*)[3])(data+0x4f4))[BANK][SLOT];
        if(DRIVER) Vec3_Subtract_DestFirst(V(0x120),V(0x8c),&parent);
        self[0xb4]++;
        break;
    case 1: break;
    }
    F(0x150)+=lbl_806D5170;
    phase=F(0x150);
    if(lbl_806D5174<phase) { DrawEffect_Free(self); return; }
    keys=((float (*)[9])(data+0x3fc))[(data+0x4cc)[BANK*9+ROLE*3+SLOT]];
    t0=F(0x154)+keys[0];t1=F(0x154)+keys[1];t2=F(0x154)+keys[2];
    s0=keys[3];s1=keys[4];s2=keys[5];a0=keys[6];a1=keys[7];a2=keys[8];
    if(phase<t0) { F(0xb0)=lbl_806D516C; F(0x2c)=lbl_806D516C; }
    else if(phase<t1) {
        blend=(lbl_806D5178/(t1-t0))*(phase-t0);
        F(0xb0)=blend*(s1-s0)+s0;F(0x2c)=blend*(a1-a0)+a0;
    } else if(phase<t2) {
        blend=(lbl_806D5178/(t2-t1))*(phase-t1);
        F(0xb0)=blend*(s2-s1)+s1;F(0x2c)=blend*(a2-a1)+a1;
    } else {F(0xb0)=s2;F(0x2c)=a2;}
    switch(ROLE) {
    case 0:F(0xb0)*=lbl_806D517C;break;
    case 1:F(0xb0)*=lbl_806D5180;break;
    case 2:F(0xb0)*=lbl_806D5184;F(0x2c)*=lbl_806D5188;break;
    }
    F(0xb0)*=lbl_806D518C;
    if(DRIVER) Vec3_Add_DestFirst(V(0x8c),&parent,V(0x120));
    camera=(Vec *)(lbl_805DF3D0+0x80);
    phase=fn_800D3184(V(0x8c),camera);
    if(lbl_806D5190<phase) F(0xb0)*=lbl_806D5194*(phase-lbl_806D5190)+lbl_806D5178;
    pos=*V(0x8c);VfxSlot_SetPositionFromVec(self+0x14,&pos);
    VfxSlot_SetRotationZ(F(0xa0),self+0x14);VfxSlot_SetScaleUniform(F(0xb0),self+0x14);
    if(self[0x1c]==0x22) {
        Vec3_Subtract_DestFirst(&delta,V(0x8c),camera);
        phase=Vec3_Magnitude_Wrapper(&delta);
        Vec3_Scale((lbl_806D5178/phase)*lbl_806D5198,&delta,&delta);
        Vec3_Add_DestFirst(&delta,V(0x8c),&delta);
        attractor=delta;VfxSlot_SetPositionFromVec(self+0x14,&attractor);
    }
}
