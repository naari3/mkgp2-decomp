/* KartDriver_Init (0x80044578): driver model/joint setup, written as C++ for the new-expression EH. */
#pragma cplusplus on
#pragma exceptions on
#pragma use_lmw_stmw on
/* Observed views only; external constructors own opaque allocation storage. */
struct Driver;
struct Normal3D { unsigned char opaque[92]; Normal3D(const char *, int); };
#include "game/types/EffectBus.h"
#include "game/types/TireFX.h"
#include "game/types/DriverTail.h"
struct Driver {
    Normal3D *kart; unsigned char pad04[8];
    Normal3D *character,*animation,*other,*shadow;
    void *a1C; Normal3D *extra,*slots[49];
    void *tires[4],*ground[4],*joint108,*engine,*body,*mufflerL,*mufflerR,*handNull,*teresa,*info,*head,*a12C,*handGoo,*handPa,*a138;
    unsigned char pad13C[20]; void *joint150,*joint154,*joint158,*joint15C,*joint160,*joint164,*joint168,*joint16C;
    float a170; unsigned char pad174[8]; void *matrix;
    unsigned char pad180[116]; int id,characterId;
    unsigned char pad1FC[28]; int contextSlot;
    unsigned char pad21C[32]; int slot;
    unsigned char pad240[8]; int raceSlot;
    unsigned char pad24C[132]; unsigned char startSlot;
    unsigned char pad2D1[51]; EffectBus *effects;
    unsigned char pad308[4]; TireFX *tireFX;
    unsigned char pad310[8]; float a318,a31C,a320,a324,a328;
    void *a32C; unsigned char pad330[20]; DriverTail *tail;
    unsigned char pad348[20]; void *a35C,*a360;
    unsigned char pad364[4]; unsigned char a368;
    unsigned char pad369[11]; int a374,a378; unsigned char pad37C[4]; int a380;
};
struct ModelEntry { const char *file; unsigned char pad04[8]; };
#include "game/types/CharacterEntry.h"
#include "game/types/JointMatrix.h"
extern "C" {
extern int g_kartStartSlot; extern void *g_raceCamera;
extern const float lbl_806D2540,lbl_806D2570,lbl_806D2574;
extern const char lbl_806D263C[7],lbl_806D2644[6],KartDriver_rodata_802E9F80[];
int HeapStats_DumpForTag(const char *,int);
ModelEntry *GetKartModelNameEntry(int,int);
CharacterEntry *GetCharacterDataEntry(int);
void *GetRaceContextPtr(void);
int RaceContextSlot_AllocDriver(void *,int,int,void*,Driver*,int);
int RaceSlot_SetDriverPtr(int,Driver*);
int Object_BindMatrixSource(Normal3D*,void*,void*);
int Object_DriveAnimAndSkin(Normal3D*,Normal3D*,float,float);
void *Archive_GetRootJObj(Normal3D*);
void ObjectTree_BlendOrCopy_Timed(Normal3D*,void*,void*,void*,float);
void *ResolveJointByName(Normal3D*,const char*);
void JObj_Hide(Normal3D*,void*,unsigned int);
void JObj_Show(Normal3D*,void*,unsigned int);
JointMatrix *KartDriver_GetJointByIdx(Driver*,int);
void SceneRender_CmdB_8aa20(void*,void*);
void KartTireFX_SetVisibleAll4Wheels(TireFX*,int);
int clNormal3D_SetScale(Normal3D*,Normal3D*,float,float,float,float);
extern const char *chara_mario_hand_goo_joint[];
extern const char *chara_mario_hand_pa_joint[];
extern const char *chara_mario_head_null_joint[];
extern const char *chara_mario_r_hand_null_joint[];
extern const char *mario_cart_body_joint[];
extern const char *mario_cart_engine_joint[];
extern const char *mario_cart_ground_fl_joint[];
extern const char *mario_cart_ground_fr_joint[];
extern const char *mario_cart_ground_rl_joint[];
extern const char *mario_cart_ground_rr_joint[];
extern const char *mario_cart_info_null_joint[];
extern const char *mario_cart_muffler_l_joint[];
extern const char *mario_cart_muffler_r_joint[];
extern const char *mario_cart_position_joint[];
extern const char *mario_cart_teresa_null_joint[];
extern const char *mario_cart_tire_fl_joint[];
extern const char *mario_cart_tire_fr_joint[];
extern const char *mario_cart_tire_rl_joint[];
extern const char *mario_cart_tire_rr_joint[];
extern const char *mario_shadow_dat[];
}
extern "C" int KartDriver_Init(Driver *self,int id,int characterId,void *matrix,int slot,int unused,int mode) {
    const char *pool=KartDriver_rodata_802E9F80;
    int heap=HeapStats_DumpForTag(lbl_806D263C,0);
    ModelEntry *model=GetKartModelNameEntry(characterId,mode);
    CharacterEntry *character=GetCharacterDataEntry(characterId);
    self->id=id; self->characterId=characterId;
    self->kart=new Normal3D(model->file,0);
    self->character=new Normal3D(character->file,0);
    self->animation=new Normal3D(character->anim,0);
    self->other=new Normal3D(character->other,0);
    self->slot=slot; self->raceSlot=slot;
    if (!self->kart || !self->character || !self->animation || !self->other) return 0;
    RaceSlot_SetDriverPtr(self->raceSlot,self);
    if (self->raceSlot==g_kartStartSlot) self->startSlot=1; else self->startSlot=0;
    self->matrix=matrix;
    self->contextSlot=RaceContextSlot_AllocDriver(GetRaceContextPtr(),id,characterId,matrix,self,slot);
    Object_BindMatrixSource(self->kart,matrix,0);
    Object_BindMatrixSource(self->character,matrix,0);
    Object_DriveAnimAndSkin(self->character,0,lbl_806D2540,lbl_806D2570);
    for (int i=0;i<49;++i) {
        if (i==0) self->slots[i]=new Normal3D(character->motion[i],0);
        else self->slots[i]=0;
    }
    self->a368=1;
    Object_DriveAnimAndSkin(self->animation,self->slots[0],lbl_806D2574,lbl_806D2540);
    ObjectTree_BlendOrCopy_Timed(self->character,Archive_GetRootJObj(self->animation),Archive_GetRootJObj(self->character),0,lbl_806D2540);
    HeapStats_DumpForTag(lbl_806D2644,heap);
    self->tires[0]=ResolveJointByName(self->kart,mario_cart_tire_fl_joint[characterId]);
    self->tires[1]=ResolveJointByName(self->kart,mario_cart_tire_fr_joint[characterId]);
    self->tires[2]=ResolveJointByName(self->kart,mario_cart_tire_rl_joint[characterId]);
    self->tires[3]=ResolveJointByName(self->kart,mario_cart_tire_rr_joint[characterId]);
    self->ground[0]=ResolveJointByName(self->kart,mario_cart_ground_fl_joint[characterId]);
    self->ground[1]=ResolveJointByName(self->kart,mario_cart_ground_fr_joint[characterId]);
    self->ground[2]=ResolveJointByName(self->kart,mario_cart_ground_rl_joint[characterId]);
    self->ground[3]=ResolveJointByName(self->kart,mario_cart_ground_rr_joint[characterId]);
    self->engine=ResolveJointByName(self->kart,mario_cart_engine_joint[characterId]);
    self->body=ResolveJointByName(self->kart,mario_cart_body_joint[characterId]);
    self->mufflerL=ResolveJointByName(self->kart,mario_cart_muffler_l_joint[characterId]);
    self->mufflerR=ResolveJointByName(self->kart,mario_cart_muffler_r_joint[characterId]);
    self->teresa=ResolveJointByName(self->kart,mario_cart_teresa_null_joint[characterId]);
    self->info=ResolveJointByName(self->character,mario_cart_info_null_joint[characterId]);
    self->head=ResolveJointByName(self->character,chara_mario_head_null_joint[characterId]);
    self->handNull=ResolveJointByName(self->character,chara_mario_r_hand_null_joint[characterId]);
    self->a138=0; self->a12C=0; self->joint154=0; self->joint164=0; self->joint168=0;
    self->a170=lbl_806D2540; self->joint16C=0; self->joint108=0; self->a318=lbl_806D2540;
    if (self->characterId==12) {
        self->handGoo=0; self->handPa=0;
        self->joint158=ResolveJointByName(self->character,pool+0xE64);
        self->joint15C=ResolveJointByName(self->character,pool+0xE84);
        self->joint160=ResolveJointByName(self->character,pool+0xEA4);
    } else {
        self->handGoo=ResolveJointByName(self->character,chara_mario_hand_goo_joint[characterId]);
        self->handPa=ResolveJointByName(self->character,chara_mario_hand_pa_joint[characterId]);
        self->joint158=0; self->joint15C=0; self->joint160=0;
    }
    self->effects=new EffectBus(self);
    if (mode==2 || mode==3) self->joint154=ResolveJointByName(self->kart,mario_cart_position_joint[characterId]);
    else self->joint154=0;
    if (self->characterId==11) {
        if (mode==2 || mode==3) self->joint164=ResolveJointByName(self->kart,pool+0xEC4);
        else self->joint164=0;
    } else self->joint164=0;
    if (self->characterId==10) {
        if (mode==2 || mode==3) {
            self->joint168=ResolveJointByName(self->kart,pool+0xEE4);
            self->joint16C=ResolveJointByName(self->kart,pool+0xF04);
        } else { self->joint16C=0; self->joint168=0; }
    } else { self->joint16C=0; self->joint168=0; }
    self->a170=lbl_806D2540;
    if (self->characterId==12) {
        if (mode==2 || mode==3) self->joint108=ResolveJointByName(self->kart,pool+0xF1C);
        else self->joint108=0;
    } else self->joint108=0;
    self->a318=lbl_806D2540;
    if (self->characterId==3) {
        self->joint150=ResolveJointByName(self->character,pool+0xF34);
        self->extra=new Normal3D(pool+0xF50,0);
        clNormal3D_SetScale(self->extra,0,lbl_806D2540,lbl_806D2570,lbl_806D2540,lbl_806D2574);
    } else { self->joint150=0; self->extra=0; }
    if (self->joint158) JObj_Hide(self->character,self->joint158,0x10);
    if (self->joint15C) JObj_Show(self->character,self->joint15C,0x10);
    if (self->joint160) JObj_Hide(self->character,self->joint160,0x10);
    self->a324=KartDriver_GetJointByIdx(self,8)->value;
    self->a328=KartDriver_GetJointByIdx(self,9)->value;
    self->a31C=lbl_806D2570; self->a320=lbl_806D2540;
    if (g_raceCamera) {
        self->shadow=new Normal3D(mario_shadow_dat[characterId],0);
        void *camera=g_raceCamera;
        SceneRender_CmdB_8aa20(camera,Archive_GetRootJObj(self->shadow));
    } else self->shadow=0;
    self->a1C=0; self->a35C=0; self->a360=0;
    self->tireFX=new TireFX(characterId,mode,self->tires[0],self->tires[1],self->tires[2],self->tires[3]);
    if (self->tireFX) KartTireFX_SetVisibleAll4Wheels(self->tireFX,0);
    self->a32C=0;
    self->tail=new DriverTail(self);
    self->a378=0; self->a380=0; self->a374=-1;
    return 1;
}
#pragma use_lmw_stmw reset
#pragma exceptions reset
#pragma cplusplus reset
