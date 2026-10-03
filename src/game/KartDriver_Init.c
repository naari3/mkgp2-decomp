/* Bounded genuine C++ retrofit: approach 2 reaches text 99.98008%,
 * automatic extab/index 100%. Residue: root r22 vs target r23 at
 * 800447A4 and 800447BC. Three structural approaches exhausted.
 * Original exact ASM remains active; this is not a genuine matching gain. */
#if 0
#pragma cplusplus on
#pragma exceptions on
/* Observed views only; external constructors own opaque allocation storage. */
struct Driver;
struct Normal3D { unsigned char opaque[92]; Normal3D(const char *, int); };
struct EffectBus { unsigned char opaque[88]; EffectBus(Driver *); };
struct TireFX { unsigned char opaque[196]; TireFX(int,int,void*,void*,void*,void*); };
struct DriverTail {
    Driver *owner; int a04, a08, a0C, a10;
    unsigned char a14,a15,pad16[2]; int a18;
    DriverTail(Driver *p) { owner=p; a04=0; a0C=0; a10=0; a14=0; a15=0; a18=-1; }
};
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
struct CharacterEntry { unsigned char pad00[4]; const char *file,*anim,*other; unsigned char pad10[8]; const char **motion; unsigned char pad1C[16]; };
struct JointMatrix { unsigned char pad00[28]; float value; };
extern "C" {
extern int g_kartStartSlot; extern void *g_raceCamera;
extern const float lbl_806D2540,lbl_806D2570,lbl_806D2574;
extern const char lbl_806D263C[7],lbl_806D2644[6],lbl_802E9F80[];
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
static inline void BlendRoots(Driver *self, void *to) {
    ObjectTree_BlendOrCopy_Timed(self->character,Archive_GetRootJObj(self->animation),to,0,lbl_806D2540);
}
extern "C" int KartDriver_Init(Driver *self,int id,int characterId,void *matrix,int slot,int unused,int mode) {
    const char *pool=lbl_802E9F80;
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
    BlendRoots(self,Archive_GetRootJObj(self->character));
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
#endif

/* === extracted from auto_KartDriver_Init_text === */
/* Copy into the TU between forward decls and function bodies; */
/* keep emit order = target section layout (do not sort). */

/* --- extern decls: branch callees (bl/b targets) --- */
/* Open prototype (`extern void Foo();`) accepts any call signature; */
/* refine if the real prototype matters for header consumers. */
extern void Alloc();
extern void Archive_GetRootJObj();
extern void GetCharacterDataEntry();
extern void GetKartModelNameEntry();
extern void GetRaceContextPtr();
extern void HeapStats_DumpForTag();
extern void ItemEffectBus_Init();
extern void JObj_Hide();
extern void JObj_Show();
extern void KartDriver_GetJointByIdx();
extern void KartTireFX_Ctor();
extern void KartTireFX_SetVisibleAll4Wheels();
extern void ObjectTree_BlendOrCopy_Timed();
extern void Object_BindMatrixSource();
extern void Object_DriveAnimAndSkin();
extern void RaceContextSlot_AllocDriver();
extern void RaceSlot_SetDriverPtr();
extern void ResolveJointByName();
extern void SceneRender_CmdB_8aa20();
extern void clNormal3D_Construct();
extern void clNormal3D_SetScale();

/* --- extern decls: sda21-referenced data --- */
extern unsigned int g_kartStartSlot;
extern unsigned int g_raceCamera;
extern unsigned int lbl_806D2540;
extern unsigned int lbl_806D2570;
extern unsigned int lbl_806D2574;

/* --- extern decls: large-data refs (@ha/@l pairs) --- */
/* Open array (`[]`) avoids sda21 strict-mode link errors when a future */
/* promote rewrites the asm_fn to C and references the symbol as `arr[i]`. */
extern unsigned int chara_mario_hand_goo_joint[];
extern unsigned int chara_mario_hand_pa_joint[];
extern unsigned int chara_mario_head_null_joint[];
extern unsigned int chara_mario_r_hand_null_joint[];
extern unsigned int lbl_802E9F80[];
extern unsigned int mario_cart_body_joint[];
extern unsigned int mario_cart_engine_joint[];
extern unsigned int mario_cart_ground_fl_joint[];
extern unsigned int mario_cart_ground_fr_joint[];
extern unsigned int mario_cart_ground_rl_joint[];
extern unsigned int mario_cart_ground_rr_joint[];
extern unsigned int mario_cart_info_null_joint[];
extern unsigned int mario_cart_muffler_l_joint[];
extern unsigned int mario_cart_muffler_r_joint[];
extern unsigned int mario_cart_position_joint[];
extern unsigned int mario_cart_teresa_null_joint[];
extern unsigned int mario_cart_tire_fl_joint[];
extern unsigned int mario_cart_tire_fr_joint[];
extern unsigned int mario_cart_tire_rl_joint[];
extern unsigned int mario_cart_tire_rr_joint[];
extern unsigned int mario_shadow_dat[];

/* --- function index (1 fns, .text 0x80044578..0x80044D50) ---
 * [  0] 0x80044578 size:0x7D8   global KartDriver_Init
 */

/* --- forward decls --- */
asm void KartDriver_Init(void);

/* --- extern decls: extab symbolic refs (dtors / typeids) --- */
extern void MemoryManager_TimedFree();

/* --- extab (manual emit, .extab_user -> extab via objcopy) --- */
#pragma section R ".extab_user"
__declspec(section ".extab_user") static const struct { unsigned int f0; unsigned int f1; unsigned int f2; unsigned int f3; unsigned int f4; unsigned int f5; unsigned int f6; unsigned int f7; unsigned int f8; unsigned int f9; unsigned int f10; unsigned int f11; unsigned int f12; unsigned int f13; unsigned int f14; unsigned int f15; unsigned int f16; unsigned int f17; unsigned int f18; unsigned int f19; unsigned int f20; void *f21; unsigned int f22; void *f23; unsigned int f24; void *f25; unsigned int f26; void *f27; unsigned int f28; void *f29; unsigned int f30; void *f31; unsigned int f32; void *f33; unsigned int f34; void *f35; unsigned int f36; void *f37; } extab_KartDriver_Init = { 0x580A0000, 0x00000084, 0x00000050, 0x000000A4, 0x00000058, 0x000000C4, 0x00000060, 0x000000E4, 0x00000068, 0x000001E8, 0x00000070, 0x000004AC, 0x00000078, 0x00000610, 0x00000080, 0x000006F0, 0x00000088, 0x00000754, 0x00000090, 0x00000000, 0x8A800015, (void *)&MemoryManager_TimedFree, 0x8A800015, (void *)&MemoryManager_TimedFree, 0x8A800015, (void *)&MemoryManager_TimedFree, 0x8A800015, (void *)&MemoryManager_TimedFree, 0x8A800015, (void *)&MemoryManager_TimedFree, 0x8A800015, (void *)&MemoryManager_TimedFree, 0x8A800015, (void *)&MemoryManager_TimedFree, 0x8A800015, (void *)&MemoryManager_TimedFree, 0x8A800015, (void *)&MemoryManager_TimedFree };

/* --- extabindex (manual emit, .extabindex_user -> extabindex via objcopy) --- */
#pragma section R ".extabindex_user"
__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_KartDriver_Init = {
    (void *)&KartDriver_Init, 0x000007D8, (void *)&extab_KartDriver_Init
};

/* --- asm function bodies (.text order = fn address order) --- */
asm void KartDriver_Init(void) { /* 0x80044578 size:0x7D8 */
    nofralloc
    stwu r1, -0x40(r1)
    mflr r0
    lis r8, lbl_802E9F80@ha
    stw r0, 0x44(r1)
    stmw r21, 0x14(r1)
    mr r31, r3
    mr r23, r4
    mr r29, r5
    mr r24, r6
    mr r25, r7
    mr r30, r9
    addi r27, r8, lbl_802E9F80@l
    addi r3, r2, -0x7C24  /* lbl_806D263C */
    li r4, 0x0
    bl HeapStats_DumpForTag
    mr r0, r3
    mr r3, r29
    mr r26, r0
    mr r4, r30
    bl GetKartModelNameEntry
    mr r22, r3
    mr r3, r29
    bl GetCharacterDataEntry
    stw r23, 0x1f4(r31)
    mr r28, r3
    li r3, 0x5c
    stw r29, 0x1f8(r31)
    bl Alloc
    mr. r21, r3
    beq KartDriver_Init_L_800445FC
    lwz r4, 0x0(r22)
    li r5, 0x0
    bl clNormal3D_Construct
    KartDriver_Init_L_800445FC:
    stw r21, 0x0(r31)
    li r3, 0x5c
    bl Alloc
    mr. r21, r3
    beq KartDriver_Init_L_8004461C
    lwz r4, 0x4(r28)
    li r5, 0x0
    bl clNormal3D_Construct
    KartDriver_Init_L_8004461C:
    stw r21, 0xc(r31)
    li r3, 0x5c
    bl Alloc
    mr. r21, r3
    beq KartDriver_Init_L_8004463C
    lwz r4, 0x8(r28)
    li r5, 0x0
    bl clNormal3D_Construct
    KartDriver_Init_L_8004463C:
    stw r21, 0x10(r31)
    li r3, 0x5c
    bl Alloc
    mr. r21, r3
    beq KartDriver_Init_L_8004465C
    lwz r4, 0xc(r28)
    li r5, 0x0
    bl clNormal3D_Construct
    KartDriver_Init_L_8004465C:
    stw r21, 0x14(r31)
    stw r25, 0x23c(r31)
    stw r25, 0x248(r31)
    lwz r0, 0x0(r31)
    cmplwi r0, 0x0
    beq KartDriver_Init_L_80044698
    lwz r0, 0xc(r31)
    cmplwi r0, 0x0
    beq KartDriver_Init_L_80044698
    lwz r0, 0x10(r31)
    cmplwi r0, 0x0
    beq KartDriver_Init_L_80044698
    lwz r0, 0x14(r31)
    cmplwi r0, 0x0
    bne KartDriver_Init_L_800446A0
    KartDriver_Init_L_80044698:
    li r3, 0x0
    b KartDriver_Init_L_80044D3C
    KartDriver_Init_L_800446A0:
    lwz r3, 0x248(r31)
    mr r4, r31
    bl RaceSlot_SetDriverPtr
    lwz r3, 0x248(r31)
    lwz r0, g_kartStartSlot(r13)
    cmpw r3, r0
    bne KartDriver_Init_L_800446C8
    li r0, 0x1
    stb r0, 0x2d0(r31)
    b KartDriver_Init_L_800446D0
    KartDriver_Init_L_800446C8:
    li r0, 0x0
    stb r0, 0x2d0(r31)
    KartDriver_Init_L_800446D0:
    stw r24, 0x17c(r31)
    bl GetRaceContextPtr
    mr r4, r23
    mr r5, r29
    mr r6, r24
    mr r7, r31
    mr r8, r25
    bl RaceContextSlot_AllocDriver
    stw r3, 0x218(r31)
    mr r4, r24
    li r5, 0x0
    lwz r3, 0x0(r31)
    bl Object_BindMatrixSource
    lwz r3, 0xc(r31)
    mr r4, r24
    li r5, 0x0
    bl Object_BindMatrixSource
    lwz r3, 0xc(r31)
    li r4, 0x0
    lfs f1, lbl_806D2540(r2)
    lfs f2, lbl_806D2570(r2)
    bl Object_DriveAnimAndSkin
    li r22, 0x0
    mr r24, r31
    mr r23, r22
    li r25, 0x0
    KartDriver_Init_L_80044738:
    cmpwi r25, 0x0
    bne KartDriver_Init_L_80044768
    li r3, 0x5c
    bl Alloc
    mr. r21, r3
    beq KartDriver_Init_L_80044760
    lwz r4, 0x18(r28)
    li r5, 0x0
    lwzx r4, r4, r22
    bl clNormal3D_Construct
    KartDriver_Init_L_80044760:
    stw r21, 0x24(r24)
    b KartDriver_Init_L_8004476C
    KartDriver_Init_L_80044768:
    stw r23, 0x24(r24)
    KartDriver_Init_L_8004476C:
    addi r25, r25, 0x1
    addi r24, r24, 0x4
    cmpwi r25, 0x31
    addi r22, r22, 0x4
    blt KartDriver_Init_L_80044738
    li r0, 0x1
    lfs f1, lbl_806D2574(r2)
    stb r0, 0x368(r31)
    lfs f2, lbl_806D2540(r2)
    lwz r3, 0x10(r31)
    lwz r4, 0x24(r31)
    bl Object_DriveAnimAndSkin
    lwz r3, 0xc(r31)
    bl Archive_GetRootJObj
    mr r23, r3
    lwz r3, 0x10(r31)
    bl Archive_GetRootJObj
    mr r4, r3
    lwz r3, 0xc(r31)
    lfs f1, lbl_806D2540(r2)
    mr r5, r23
    li r6, 0x0
    bl ObjectTree_BlendOrCopy_Timed
    mr r4, r26
    addi r3, r2, -0x7C1C  /* lbl_806D2644 */
    bl HeapStats_DumpForTag
    lis r3, mario_cart_tire_fl_joint@ha
    slwi r28, r29, 2
    addi r4, r3, mario_cart_tire_fl_joint@l
    lwz r3, 0x0(r31)
    lwzx r4, r4, r28
    bl ResolveJointByName
    stw r3, 0xe8(r31)
    lis r3, mario_cart_tire_fr_joint@ha
    addi r4, r3, mario_cart_tire_fr_joint@l
    lwz r3, 0x0(r31)
    lwzx r4, r4, r28
    bl ResolveJointByName
    stw r3, 0xec(r31)
    lis r3, mario_cart_tire_rl_joint@ha
    addi r4, r3, mario_cart_tire_rl_joint@l
    lwz r3, 0x0(r31)
    lwzx r4, r4, r28
    bl ResolveJointByName
    stw r3, 0xf0(r31)
    lis r3, mario_cart_tire_rr_joint@ha
    addi r4, r3, mario_cart_tire_rr_joint@l
    lwz r3, 0x0(r31)
    lwzx r4, r4, r28
    bl ResolveJointByName
    stw r3, 0xf4(r31)
    lis r3, mario_cart_ground_fl_joint@ha
    addi r4, r3, mario_cart_ground_fl_joint@l
    lwz r3, 0x0(r31)
    lwzx r4, r4, r28
    bl ResolveJointByName
    stw r3, 0xf8(r31)
    lis r3, mario_cart_ground_fr_joint@ha
    addi r4, r3, mario_cart_ground_fr_joint@l
    lwz r3, 0x0(r31)
    lwzx r4, r4, r28
    bl ResolveJointByName
    stw r3, 0xfc(r31)
    lis r3, mario_cart_ground_rl_joint@ha
    addi r4, r3, mario_cart_ground_rl_joint@l
    lwz r3, 0x0(r31)
    lwzx r4, r4, r28
    bl ResolveJointByName
    stw r3, 0x100(r31)
    lis r3, mario_cart_ground_rr_joint@ha
    addi r4, r3, mario_cart_ground_rr_joint@l
    lwz r3, 0x0(r31)
    lwzx r4, r4, r28
    bl ResolveJointByName
    stw r3, 0x104(r31)
    lis r3, mario_cart_engine_joint@ha
    addi r4, r3, mario_cart_engine_joint@l
    lwz r3, 0x0(r31)
    lwzx r4, r4, r28
    bl ResolveJointByName
    stw r3, 0x10c(r31)
    lis r3, mario_cart_body_joint@ha
    addi r4, r3, mario_cart_body_joint@l
    lwz r3, 0x0(r31)
    lwzx r4, r4, r28
    bl ResolveJointByName
    stw r3, 0x110(r31)
    lis r3, mario_cart_muffler_l_joint@ha
    addi r4, r3, mario_cart_muffler_l_joint@l
    lwz r3, 0x0(r31)
    lwzx r4, r4, r28
    bl ResolveJointByName
    stw r3, 0x114(r31)
    lis r3, mario_cart_muffler_r_joint@ha
    addi r4, r3, mario_cart_muffler_r_joint@l
    lwz r3, 0x0(r31)
    lwzx r4, r4, r28
    bl ResolveJointByName
    stw r3, 0x118(r31)
    lis r3, mario_cart_teresa_null_joint@ha
    addi r4, r3, mario_cart_teresa_null_joint@l
    lwz r3, 0x0(r31)
    lwzx r4, r4, r28
    bl ResolveJointByName
    stw r3, 0x120(r31)
    lis r3, mario_cart_info_null_joint@ha
    addi r4, r3, mario_cart_info_null_joint@l
    lwz r3, 0xc(r31)
    lwzx r4, r4, r28
    bl ResolveJointByName
    stw r3, 0x124(r31)
    lis r3, chara_mario_head_null_joint@ha
    addi r4, r3, chara_mario_head_null_joint@l
    lwz r3, 0xc(r31)
    lwzx r4, r4, r28
    bl ResolveJointByName
    stw r3, 0x128(r31)
    lis r3, chara_mario_r_hand_null_joint@ha
    addi r4, r3, chara_mario_r_hand_null_joint@l
    lwz r3, 0xc(r31)
    lwzx r4, r4, r28
    bl ResolveJointByName
    stw r3, 0x11c(r31)
    li r3, 0x0
    lfs f0, lbl_806D2540(r2)
    stw r3, 0x138(r31)
    stw r3, 0x12c(r31)
    stw r3, 0x154(r31)
    stw r3, 0x164(r31)
    stw r3, 0x168(r31)
    stfs f0, 0x170(r31)
    stw r3, 0x16c(r31)
    stw r3, 0x108(r31)
    stfs f0, 0x318(r31)
    lwz r0, 0x1f8(r31)
    cmpwi r0, 0xc
    bne KartDriver_Init_L_800449CC
    stw r3, 0x130(r31)
    addi r4, r27, 0xe64
    stw r3, 0x134(r31)
    lwz r3, 0xc(r31)
    bl ResolveJointByName
    stw r3, 0x158(r31)
    addi r4, r27, 0xe84
    lwz r3, 0xc(r31)
    bl ResolveJointByName
    stw r3, 0x15c(r31)
    addi r4, r27, 0xea4
    lwz r3, 0xc(r31)
    bl ResolveJointByName
    stw r3, 0x160(r31)
    b KartDriver_Init_L_80044A0C
    KartDriver_Init_L_800449CC:
    lis r4, chara_mario_hand_goo_joint@ha
    lwz r3, 0xc(r31)
    addi r4, r4, chara_mario_hand_goo_joint@l
    lwzx r4, r4, r28
    bl ResolveJointByName
    stw r3, 0x130(r31)
    lis r3, chara_mario_hand_pa_joint@ha
    addi r4, r3, chara_mario_hand_pa_joint@l
    lwz r3, 0xc(r31)
    lwzx r4, r4, r28
    bl ResolveJointByName
    stw r3, 0x134(r31)
    li r0, 0x0
    stw r0, 0x158(r31)
    stw r0, 0x15c(r31)
    stw r0, 0x160(r31)
    KartDriver_Init_L_80044A0C:
    li r3, 0x58
    bl Alloc
    mr. r21, r3
    beq KartDriver_Init_L_80044A24
    mr r4, r31
    bl ItemEffectBus_Init
    KartDriver_Init_L_80044A24:
    cmpwi r30, 0x2
    stw r21, 0x304(r31)
    beq KartDriver_Init_L_80044A38
    cmpwi r30, 0x3
    bne KartDriver_Init_L_80044A54
    KartDriver_Init_L_80044A38:
    lis r4, mario_cart_position_joint@ha
    lwz r3, 0x0(r31)
    addi r4, r4, mario_cart_position_joint@l
    lwzx r4, r4, r28
    bl ResolveJointByName
    stw r3, 0x154(r31)
    b KartDriver_Init_L_80044A5C
    KartDriver_Init_L_80044A54:
    li r0, 0x0
    stw r0, 0x154(r31)
    KartDriver_Init_L_80044A5C:
    lwz r0, 0x1f8(r31)
    cmpwi r0, 0xb
    bne KartDriver_Init_L_80044A98
    cmpwi r30, 0x2
    beq KartDriver_Init_L_80044A78
    cmpwi r30, 0x3
    bne KartDriver_Init_L_80044A8C
    KartDriver_Init_L_80044A78:
    lwz r3, 0x0(r31)
    addi r4, r27, 0xec4
    bl ResolveJointByName
    stw r3, 0x164(r31)
    b KartDriver_Init_L_80044AA0
    KartDriver_Init_L_80044A8C:
    li r0, 0x0
    stw r0, 0x164(r31)
    b KartDriver_Init_L_80044AA0
    KartDriver_Init_L_80044A98:
    li r0, 0x0
    stw r0, 0x164(r31)
    KartDriver_Init_L_80044AA0:
    lwz r0, 0x1f8(r31)
    cmpwi r0, 0xa
    bne KartDriver_Init_L_80044AF0
    cmpwi r30, 0x2
    beq KartDriver_Init_L_80044ABC
    cmpwi r30, 0x3
    bne KartDriver_Init_L_80044AE0
    KartDriver_Init_L_80044ABC:
    lwz r3, 0x0(r31)
    addi r4, r27, 0xee4
    bl ResolveJointByName
    stw r3, 0x168(r31)
    addi r4, r27, 0xf04
    lwz r3, 0x0(r31)
    bl ResolveJointByName
    stw r3, 0x16c(r31)
    b KartDriver_Init_L_80044AFC
    KartDriver_Init_L_80044AE0:
    li r0, 0x0
    stw r0, 0x16c(r31)
    stw r0, 0x168(r31)
    b KartDriver_Init_L_80044AFC
    KartDriver_Init_L_80044AF0:
    li r0, 0x0
    stw r0, 0x16c(r31)
    stw r0, 0x168(r31)
    KartDriver_Init_L_80044AFC:
    lfs f0, lbl_806D2540(r2)
    stfs f0, 0x170(r31)
    lwz r0, 0x1f8(r31)
    cmpwi r0, 0xc
    bne KartDriver_Init_L_80044B40
    cmpwi r30, 0x2
    beq KartDriver_Init_L_80044B20
    cmpwi r30, 0x3
    bne KartDriver_Init_L_80044B34
    KartDriver_Init_L_80044B20:
    lwz r3, 0x0(r31)
    addi r4, r27, 0xf1c
    bl ResolveJointByName
    stw r3, 0x108(r31)
    b KartDriver_Init_L_80044B48
    KartDriver_Init_L_80044B34:
    li r0, 0x0
    stw r0, 0x108(r31)
    b KartDriver_Init_L_80044B48
    KartDriver_Init_L_80044B40:
    li r0, 0x0
    stw r0, 0x108(r31)
    KartDriver_Init_L_80044B48:
    lfs f0, lbl_806D2540(r2)
    stfs f0, 0x318(r31)
    lwz r0, 0x1f8(r31)
    cmpwi r0, 0x3
    bne KartDriver_Init_L_80044BAC
    lwz r3, 0xc(r31)
    addi r4, r27, 0xf34
    bl ResolveJointByName
    stw r3, 0x150(r31)
    li r3, 0x5c
    bl Alloc
    mr. r21, r3
    beq KartDriver_Init_L_80044B88
    addi r4, r27, 0xf50
    li r5, 0x0
    bl clNormal3D_Construct
    KartDriver_Init_L_80044B88:
    lfs f1, lbl_806D2540(r2)
    li r4, 0x0
    stw r21, 0x20(r31)
    fmr f3, f1
    lfs f2, lbl_806D2570(r2)
    lwz r3, 0x20(r31)
    lfs f4, lbl_806D2574(r2)
    bl clNormal3D_SetScale
    b KartDriver_Init_L_80044BB8
    KartDriver_Init_L_80044BAC:
    li r0, 0x0
    stw r0, 0x150(r31)
    stw r0, 0x20(r31)
    KartDriver_Init_L_80044BB8:
    lwz r4, 0x158(r31)
    cmplwi r4, 0x0
    beq KartDriver_Init_L_80044BD0
    lwz r3, 0xc(r31)
    li r5, 0x10
    bl JObj_Hide
    KartDriver_Init_L_80044BD0:
    lwz r4, 0x15c(r31)
    cmplwi r4, 0x0
    beq KartDriver_Init_L_80044BE8
    lwz r3, 0xc(r31)
    li r5, 0x10
    bl JObj_Show
    KartDriver_Init_L_80044BE8:
    lwz r4, 0x160(r31)
    cmplwi r4, 0x0
    beq KartDriver_Init_L_80044C00
    lwz r3, 0xc(r31)
    li r5, 0x10
    bl JObj_Hide
    KartDriver_Init_L_80044C00:
    mr r3, r31
    li r4, 0x8
    bl KartDriver_GetJointByIdx
    lfs f0, 0x1c(r3)
    mr r3, r31
    li r4, 0x9
    stfs f0, 0x324(r31)
    bl KartDriver_GetJointByIdx
    lfs f0, 0x1c(r3)
    lfs f1, lbl_806D2570(r2)
    stfs f0, 0x328(r31)
    lfs f0, lbl_806D2540(r2)
    stfs f1, 0x31c(r31)
    stfs f0, 0x320(r31)
    lwz r0, g_raceCamera(r13)
    cmplwi r0, 0x0
    beq KartDriver_Init_L_80044C88
    li r3, 0x5c
    bl Alloc
    mr. r21, r3
    beq KartDriver_Init_L_80044C68
    lis r4, mario_shadow_dat@ha
    li r5, 0x0
    addi r4, r4, mario_shadow_dat@l
    lwzx r4, r4, r28
    bl clNormal3D_Construct
    KartDriver_Init_L_80044C68:
    stw r21, 0x18(r31)
    lwz r22, g_raceCamera(r13)
    lwz r3, 0x18(r31)
    bl Archive_GetRootJObj
    mr r4, r3
    mr r3, r22
    bl SceneRender_CmdB_8aa20
    b KartDriver_Init_L_80044C90
    KartDriver_Init_L_80044C88:
    li r0, 0x0
    stw r0, 0x18(r31)
    KartDriver_Init_L_80044C90:
    li r0, 0x0
    li r3, 0xc4
    stw r0, 0x1c(r31)
    stw r0, 0x35c(r31)
    stw r0, 0x360(r31)
    bl Alloc
    mr. r21, r3
    beq KartDriver_Init_L_80044CCC
    lwz r6, 0xe8(r31)
    mr r4, r29
    lwz r7, 0xec(r31)
    mr r5, r30
    lwz r8, 0xf0(r31)
    lwz r9, 0xf4(r31)
    bl KartTireFX_Ctor
    KartDriver_Init_L_80044CCC:
    stw r21, 0x30c(r31)
    lwz r3, 0x30c(r31)
    cmplwi r3, 0x0
    beq KartDriver_Init_L_80044CE4
    li r4, 0x0
    bl KartTireFX_SetVisibleAll4Wheels
    KartDriver_Init_L_80044CE4:
    li r0, 0x0
    li r3, 0x1c
    stw r0, 0x32c(r31)
    bl Alloc
    cmplwi r3, 0x0
    beq KartDriver_Init_L_80044D20
    stw r31, 0x0(r3)
    li r4, 0x0
    li r0, -0x1
    stw r4, 0x4(r3)
    stw r4, 0xc(r3)
    stw r4, 0x10(r3)
    stb r4, 0x14(r3)
    stb r4, 0x15(r3)
    stw r0, 0x18(r3)
    KartDriver_Init_L_80044D20:
    stw r3, 0x344(r31)
    li r4, 0x0
    li r0, -0x1
    li r3, 0x1
    stw r4, 0x378(r31)
    stw r4, 0x380(r31)
    stw r0, 0x374(r31)
    KartDriver_Init_L_80044D3C:
    lmw r21, 0x14(r1)
    lwz r0, 0x44(r1)
    mtlr r0
    addi r1, r1, 0x40
    blr
}
