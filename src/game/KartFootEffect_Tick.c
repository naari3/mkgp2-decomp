/* Actor is opaque in Ghidra; named accessors document the observed layout. */
#include "game/types/Vec.h"
const float KartFootEffect_Tick_rodata_80329908[255] = {
    1.0f, 0.7f, 0.9f, 0.0f, 0.0f, 5e+02f, 66.66667f, 1e+03f,
    66.66667f, 2e+03f, 66.66667f, 3e+03f, 66.66667f, 4e+03f, 66.66667f, 5e+03f,
    66.66667f, 0.0f, 0.0f, 5e+02f, 66.66667f, 1e+03f, 66.66667f, 2e+03f,
    66.66667f, 3e+03f, 66.66667f, 4e+03f, 66.66667f, 5e+03f, 66.66667f, 0.0f,
    0.0f, 5e+02f, 66.66667f, 1e+03f, 66.66667f, 2e+03f, 66.66667f, 3e+03f,
    66.66667f, 4e+03f, 66.66667f, 5e+03f, 66.66667f, 0.0f, 0.0f, 5e+02f,
    66.66667f, 1e+03f, 66.66667f, 2e+03f, 66.66667f, 3e+03f, 66.66667f, 4e+03f,
    66.66667f, 5e+03f, 66.66667f, 0.0f, 0.0f, 5e+02f, 66.66667f, 1e+03f,
    66.66667f, 2e+03f, 66.66667f, 3e+03f, 66.66667f, 4e+03f, 66.66667f, 5e+03f,
    66.66667f, 0.0f, 0.0f, 5e+02f, 66.66667f, 1e+03f, 66.66667f, 2e+03f,
    66.66667f, 3e+03f, 66.66667f, 4e+03f, 66.66667f, 5e+03f, 66.66667f, 0.0f,
    0.0f, 5e+02f, 66.66667f, 1e+03f, 66.66667f, 2e+03f, 66.66667f, 3e+03f,
    66.66667f, 4e+03f, 66.66667f, 5e+03f, 66.66667f, 0.0f, 0.0f, 5e+02f,
    66.66667f, 1e+03f, 66.66667f, 2e+03f, 66.66667f, 3e+03f, 66.66667f, 4e+03f,
    66.66667f, 5e+03f, 66.66667f, 0.0f, 0.0f, 5e+02f, 66.66667f, 1e+03f,
    66.66667f, 2e+03f, 66.66667f, 3e+03f, 66.66667f, 4e+03f, 66.66667f, 5e+03f,
    66.66667f, 0.0f, 0.0f, 5e+02f, 66.66667f, 1e+03f, 66.66667f, 2e+03f,
    66.66667f, 3e+03f, 66.66667f, 4e+03f, 66.66667f, 5e+03f, 66.66667f, 0.0f,
    0.0f, 5e+02f, 66.66667f, 1e+03f, 66.66667f, 2e+03f, 66.66667f, 3e+03f,
    66.66667f, 4e+03f, 66.66667f, 5e+03f, 66.66667f, 0.0f, 0.0f, 5e+02f,
    66.66667f, 1e+03f, 66.66667f, 2e+03f, 66.66667f, 3e+03f, 66.66667f, 4e+03f,
    66.66667f, 5e+03f, 66.66667f, 0.0f, 0.0f, 5e+02f, 83.333336f, 1e+03f,
    83.333336f, 2e+03f, 83.333336f, 3e+03f, 83.333336f, 4e+03f, 83.333336f, 5e+03f,
    83.333336f, 0.0f, 0.0f, 5e+02f, 83.333336f, 1e+03f, 83.333336f, 2e+03f,
    83.333336f, 3e+03f, 83.333336f, 4e+03f, 83.333336f, 5e+03f, 83.333336f, 0.0f,
    0.0f, 5e+02f, 83.333336f, 1e+03f, 83.333336f, 2e+03f, 83.333336f, 3e+03f,
    83.333336f, 4e+03f, 83.333336f, 5e+03f, 83.333336f, 0.0f, 0.0f, 5e+02f,
    83.333336f, 1e+03f, 83.333336f, 2e+03f, 83.333336f, 3e+03f, 83.333336f, 4e+03f,
    83.333336f, 5e+03f, 83.333336f, 0.0f, 0.0f, 5e+02f, 83.333336f, 1e+03f,
    83.333336f, 2e+03f, 83.333336f, 3e+03f, 83.333336f, 4e+03f, 83.333336f, 5e+03f,
    83.333336f, 0.0f, 0.0f, 5e+02f, 83.333336f, 1e+03f, 83.333336f, 2e+03f,
    83.333336f, 3e+03f, 83.333336f, 4e+03f, 83.333336f, 5e+03f, 83.333336f
};
static const float footKeys[5][9] = {
    {1.0f, 5.0f, 7.0f, 0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f},
    {1.0f, 5.0f, 8.0f, 0.5f, 1.2f, 1.2f, 1.0f, 1.0f, 0.0f},
    {1.0f, 6.0f, 1e+01f, 0.3f, 0.96f, 1.5f, 1.0f, 1.0f, 0.0f},
    {1.0f, 6.0f, 1e+01f, 0.1f, 0.6f, 1.0f, 1.0f, 1.0f, 0.0f},
    {1.0f, 8.0f, 11.0f, 0.1f, 0.87f, 1.2f, 1.0f, 1.0f, 0.0f}
};
const unsigned char KartFootEffect_Spawn_rodata_80329DB8[3][3][3] = {{{0x1F, 0x22, 0x00}, {0x23, 0x00, 0x00}, {0x00, 0x00, 0x00}}, {{0x20, 0x22, 0x00}, {0x23, 0x23, 0x00}, {0x24, 0x00, 0x00}}, {{0x21, 0x22, 0x00}, {0x23, 0x23, 0x23}, {0x24, 0x24, 0x00}}};
static const unsigned char footKeyIdx[3][3][3] = {{{0x00, 0x00, 0x00}, {0x02, 0x00, 0x00}, {0x00, 0x00, 0x00}}, {{0x01, 0x01, 0x00}, {0x02, 0x02, 0x00}, {0x03, 0x00, 0x00}}, {{0x01, 0x01, 0x00}, {0x02, 0x02, 0x02}, {0x04, 0x04, 0x00}}};
static const float footRoleScale[3] = {0.0f, 2e+01f, 1e+02f};
static const float footBase[3][3] = {{0.0f, 0.0f, 0.0f}, {0.0f, 3.0f, 5.0f}, {0.0f, 4.0f, 0.0f}};
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
    const float *keys;
    if (DRIVER) Mtx44_GetTranslation_RowMajor(&parent,KartDriver_GetKartRootMtx(DRIVER));
    switch ((signed char)self[0xb4]) {
    case 0:
        self[0x1c]=KartFootEffect_Spawn_rodata_80329DB8[BANK][ROLE][SLOT];
        VfxSlot_BindResourceEx(self+0x14,self[0x1c],0);
        if (ROLE==1) F(0xa0)=lbl_806D5168*footRoleScale[SLOT];
        F(0x150)=lbl_806D516C;
        F(0x154)=footBase[BANK][SLOT];
        if(DRIVER) Vec3_Subtract_DestFirst(V(0x120),V(0x8c),&parent);
        self[0xb4]++;
        break;
    case 1: break;
    }
    F(0x150)+=lbl_806D5170;
    phase=F(0x150);
    if(lbl_806D5174<phase) { DrawEffect_Free(self); return; }
    {int k=footKeyIdx[BANK][ROLE][SLOT];
    t0=F(0x154)+footKeys[k][0];t1=F(0x154)+footKeys[k][1];t2=F(0x154)+footKeys[k][2];
    s0=footKeys[k][3];s1=footKeys[k][4];s2=footKeys[k][5];a0=footKeys[k][6];a1=footKeys[k][7];a2=footKeys[k][8];}
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
        {float inv=lbl_806D5178/Vec3_Magnitude_Wrapper(&delta);
        Vec3_Scale(lbl_806D5198*inv,&delta,&delta);
        Vec3_Add_DestFirst(&delta,V(0x8c),&delta);
        }attractor=delta;VfxSlot_SetPositionFromVec(self+0x14,&attractor);
    }
}
