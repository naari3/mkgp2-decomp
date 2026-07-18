/*
 * VolumeCalibration game mode @ 0x80039E10..0x8003A154 (unit-first TU, 4 fns).
 *
 *   VolumeCalibration_DrawOverlay @ 0x80039E10 (size 0xCC, extab 0x8  r27-r31) [asm_fn]
 *   VolumeCalibration_Tick        @ 0x80039EDC (size 0x130, extab 0x8 r30-r31) [asm_fn]
 *   VolumeCalibration_Dtor        @ 0x8003A00C (size 0xB8, extab 0x8  r30-r31) [C]
 *   VolumeCalibration_Ctor        @ 0x8003A0C4 (size 0x90, extab 0x18 r31 +
 *                                               DELETEPOINTER cleanup)        [C]
 *
 * Operator-menu "volume calibration" mode: tracks the raw JVS analog
 * channels (steering / accel / brake in g_jvsOperatorBits +0x8/+0xA/+0xC),
 * records min/max excursions per channel, and on teardown publishes the
 * calibration to JvsInput_Set*Calibration + the backup shadow block
 * (lbl_80598A60 +0x34..) before freeing itself.
 *
 * Object layout (size 0x28, vtable lbl_803F57CC = {RTTI 0x806CED98, 0,
 * Tick, DrawOverlay, Dtor}):
 *   +0x00 void* vtbl
 *   +0x04 s32   steer      (raw steering; ctor seeds center 0x7A40)
 *   +0x08 s32   posData    (StrPcb received position data; ctor 0x1FF)
 *   +0x0C s32   field_0c   (= 1)
 *   +0x10 s32   steerMin   (ctor 0x7A3F)
 *   +0x14 s32   steerMax   (ctor 0x7A41)
 *   +0x18 s32   accelMin   \ ctor seeds both from current accel
 *   +0x1C s32   accelMax   /
 *   +0x20 s32   brakeMin   \ ctor seeds both from current brake
 *   +0x24 s32   brakeMax   /
 *
 * Build shape: -lang=c++ / -Cpp_exceptions on with all definitions inside
 * extern "C" (unmangled names). Both C fns suppress auto extab emission
 * with #pragma exceptions off; all four extab/extabindex entries are
 * manually emitted (approach B, docs/per_fn_matching_strategy.md 14.1) in
 * target section order at the end of the file.
 *
 * --- asm_fn retreat notes (future retry) ---
 *
 * DrawOverlay: every instruction is reproduced 1:1 by the C body below
 * EXCEPT the overlay-string addressing. The target addresses all four
 * format strings as one base (r31 = lbl_802E9C50) + offsets 0x24/0x38/
 * 0x54/0x68. That shape is the CW -str reuse PER-TU LITERAL POOL: the
 * original TU owned the string literals ("RIGHT PEDAL", "LEFT  PEDAL",
 * "clJobRunner", "Volume caribration", "===== Now Setting Parameter",
 * "HANDLE NOW    %d", "%s NOW %08x", ...) and CW addresses the local pool
 * from a single callee-saved base. With the strings referenced as an
 * EXTERN symbol instead, CW 1.3.2 constant-folds each strs+K expression
 * and rematerializes lis/addi per call site (probed: char* local base,
 * struct-member view; both keep only the first + in-loop uses on r31).
 * Reconstructing the pool in-TU is blocked for now: the pool interleaves
 * "clJobRunner" (referenced by the RTTI object @ 0x806CED98 via sdata;
 * -RTTI off here) and "my class library"/"mode" (referenced by the
 * MObj*_ClassInit fns @ 0x8003A31C.. of the same original TU, outside
 * this batch), i.e. it needs a TU-level C++ class + RTTI retrofit.
 * Near-match C body (only the string-base residue):
 *
 *   void VolumeCalibration_DrawOverlay(VolumeCalibration *self) {
 *       VolumeCalibration *cur;
 *       const int *tbl;
 *       int row;
 *       int i;
 *       char *strs = lbl_802E9C50;
 *       OverlayText(2, 1, 0, strs + 0x24);            // "Volume caribration"
 *       OverlayText(2, 1, 10, strs + 0x38);           // "===== Now Setting Parameter"
 *       OverlayText(2, 1, 11, strs + 0x54, self->steer / 64);  // "HANDLE NOW    %d"
 *       cur = self;
 *       tbl = lbl_806D2480;      // {"RIGHT PEDAL", "LEFT  PEDAL"} char* pair
 *       row = 15;
 *       for (i = 0; i < 2; i++) {
 *           OverlayText(2, 1, row + 1, strs + 0x68, *tbl, cur->accelMax); // "%s NOW %08x"
 *           tbl++;
 *           row += 3;
 *           cur = (VolumeCalibration *)((char *)cur + 8);
 *       }
 *   }
 *
 * Tick (register-identity park family): the whole body is emitted 1:1 by
 * the C source below EXCEPT a pure register permutation in the jvs-load
 * head. Target: base=r5, accel=r4, brake=r0, steer=r5 (base reuse),
 * minmax temp=r3 (self's param home vacated lazily at the first temp
 * load). CW 1.3.2 vacates the self param to its callee-saved home (r30)
 * eagerly at entry, so the base web always grabs r3 and the permutation
 * cascades: base/steer=r3, brake=r5, temp=r0. Probed 7+ source shapes
 * with no movement: decl-order permutations, split-use m/self alias,
 * named jvs pointer, C++ member fn (plain + virtual w/ polymorphic
 * base), inline helper splice (per-channel int* form, whole-block form,
 * member-method form), register keyword. The tail (vcall part) needs
 * real C++ virtual dispatch for the r12-chained
 * `lwz r12, 0x0(rX); lwz r12, 0x20(r12)` form (solved via -lang=c++ +
 * polymorphic class w/ virtual getButton at vtable byte 0x20 = 2-word CW
 * vtable header + virtual index 6, see
 * docs/notes/cw132-allocator-phase2f-research.md).
 * Near-match C body (residue = jvs-head register identity only):
 *
 *   int VolumeCalibration_Tick(VolumeCalibration *self) {
 *       InputObject *p;                 // class w/ virtual getButton @ vtable +0x20
 *       int accel = g_jvsOperatorBits.accel;
 *       int brake = g_jvsOperatorBits.brake;
 *       int steer = g_jvsOperatorBits.steer;
 *       self->steer = steer;
 *       if (self->steerMin > steer) { self->steerMin = steer; }
 *       else if (self->steerMax < steer) { self->steerMax = steer; }
 *       if (self->accelMin > accel) { self->accelMin = accel; }
 *       else if (self->accelMax < accel) { self->accelMax = accel; }
 *       if (self->brakeMin > brake) { self->brakeMin = brake; }
 *       else if (self->brakeMax < brake) { self->brakeMax = brake; }
 *       p = InputMgr_GetPlayer(GetInputManager(), 0);
 *       if ((unsigned char)p->getButton(0x401) == 1) { return -4; }
 *       self->posData = StrPcb_GetReceivedPosData(StrPcb_GetInstance());
 *       if ((unsigned char)p->getButton(0x40) == 1) {
 *           StrPcb_SetStatusBits(StrPcb_GetInstance(), 0xC, 0);
 *       }
 *       return -2;
 *   }
 */

typedef struct VolumeCalibration {
    void *vtbl;    /* 0x00 -> lbl_803F57CC */
    int steer;     /* 0x04 */
    int posData;   /* 0x08 */
    int field_0c;  /* 0x0C */
    int steerMin;  /* 0x10 */
    int steerMax;  /* 0x14 */
    int accelMin;  /* 0x18 */
    int accelMax;  /* 0x1C */
    int brakeMin;  /* 0x20 */
    int brakeMax;  /* 0x24 */
} VolumeCalibration; /* size 0x28 */

typedef struct JvsOperatorInput {
    unsigned char pad_0x00[0x8];
    unsigned short steer; /* 0x08 */
    unsigned short accel; /* 0x0A */
    unsigned short brake; /* 0x0C */
} JvsOperatorInput;

/* backup shadow block @ lbl_80598A60 (.bss size 0x2A), calibration slice */
typedef struct BackupCalibView {
    unsigned char pad_0x00[0x34];
    int steer; /* 0x34 */
    int pos;   /* 0x38 */
    int brake; /* 0x3C */
    int accel; /* 0x40 */
} BackupCalibView;

extern "C" {

extern void OverlayText(int layer, int flag, int row, char *fmt, ...);
extern void *GetInputManager(void);
extern void *InputMgr_GetPlayer(void *mgr, unsigned int playerIdx);
extern void *StrPcb_GetInstance(void);
extern int StrPcb_GetReceivedPosData(void *pcb);
extern void StrPcb_SetStatusBits(void *pcb, int bits, int arg);
extern void StrPcb_SetPositionTarget(void *pcb, short target);
extern void JvsInput_SetSteeringCalibration(int value);
extern void JvsInput_SetAccelCalibration(int value);
extern void JvsInput_SetBrakeCalibration(int value);
extern void Backup_PublishShadowCopy_Inline(void);
extern void GameMode_BaseInit(void *self);
extern void *dtor_8002CDF4(void *self, short freeFlag); /* ObjectBase_Dtor */
extern void MemoryManager_TimedFree(void *p);
extern void *Alloc(int size);

extern char lbl_802E9C50[];          /* .rodata overlay string pool base */
extern const int lbl_806D2480[2];    /* .sdata2 {"RIGHT PEDAL","LEFT  PEDAL"} char* pair */
extern char lbl_803F57CC[];          /* VolumeCalibration vtable */
extern BackupCalibView lbl_80598A60; /* backup shadow block */
extern JvsOperatorInput g_jvsOperatorBits;

/* forward decls for manual extab emit */
asm void VolumeCalibration_DrawOverlay(VolumeCalibration *self);
asm int VolumeCalibration_Tick(VolumeCalibration *self);
void *VolumeCalibration_Dtor(VolumeCalibration *self, short freeFlag);
VolumeCalibration *VolumeCalibration_Ctor(void);

asm void VolumeCalibration_DrawOverlay(VolumeCalibration *self) {
    nofralloc
    stwu r1, -0x20(r1)
    mflr r0
    lis r4, lbl_802E9C50@ha
    li r5, 0x0
    stw r0, 0x24(r1)
    stmw r27, 0xc(r1)
    addi r31, r4, lbl_802E9C50@l
    mr r27, r3
    li r3, 0x2
    addi r6, r31, 0x24
    li r4, 0x1
    crxor 6, 6, 6
    bl OverlayText
    addi r6, r31, 0x38
    li r3, 0x2
    li r4, 0x1
    li r5, 0xa
    crxor 6, 6, 6
    bl OverlayText
    lwz r0, 0x4(r27)
    addi r6, r31, 0x54
    li r3, 0x2
    li r4, 0x1
    srawi r0, r0, 6
    li r5, 0xb
    addze r7, r0
    crxor 6, 6, 6
    bl OverlayText
    mr r30, r27
    li r27, 0x0
    la r29, lbl_806D2480(r2)  /* li r29, lbl_806D2480@sda21 */
    li r28, 0xf
    VolumeCalibration_DrawOverlay_L_80039E90:
    lwz r7, 0x0(r29)
    addi r5, r28, 0x1
    lwz r8, 0x1c(r30)
    addi r6, r31, 0x68
    li r3, 0x2
    li r4, 0x1
    crxor 6, 6, 6
    bl OverlayText
    addi r27, r27, 0x1
    addi r29, r29, 0x4
    cmpwi r27, 0x2
    addi r28, r28, 0x3
    addi r30, r30, 0x8
    blt VolumeCalibration_DrawOverlay_L_80039E90
    lmw r27, 0xc(r1)
    lwz r0, 0x24(r1)
    mtlr r0
    addi r1, r1, 0x20
    blr
}

asm int VolumeCalibration_Tick(VolumeCalibration *self) {
    nofralloc
    stwu r1, -0x10(r1)
    mflr r0
    lis r4, g_jvsOperatorBits@ha
    stw r0, 0x14(r1)
    addi r5, r4, g_jvsOperatorBits@l
    stw r31, 0xc(r1)
    stw r30, 0x8(r1)
    mr r30, r3
    lhz r4, 0xa(r5)
    lhz r0, 0xc(r5)
    lhz r5, 0x8(r5)
    stw r5, 0x4(r3)
    lwz r3, 0x10(r3)
    cmpw r3, r5
    ble VolumeCalibration_Tick_L_80039F20
    stw r5, 0x10(r30)
    b VolumeCalibration_Tick_L_80039F30
    VolumeCalibration_Tick_L_80039F20:
    lwz r3, 0x14(r30)
    cmpw r3, r5
    bge VolumeCalibration_Tick_L_80039F30
    stw r5, 0x14(r30)
    VolumeCalibration_Tick_L_80039F30:
    lwz r3, 0x18(r30)
    cmpw r3, r4
    ble VolumeCalibration_Tick_L_80039F44
    stw r4, 0x18(r30)
    b VolumeCalibration_Tick_L_80039F54
    VolumeCalibration_Tick_L_80039F44:
    lwz r3, 0x1c(r30)
    cmpw r3, r4
    bge VolumeCalibration_Tick_L_80039F54
    stw r4, 0x1c(r30)
    VolumeCalibration_Tick_L_80039F54:
    lwz r3, 0x20(r30)
    cmpw r3, r0
    ble VolumeCalibration_Tick_L_80039F68
    stw r0, 0x20(r30)
    b VolumeCalibration_Tick_L_80039F78
    VolumeCalibration_Tick_L_80039F68:
    lwz r3, 0x24(r30)
    cmpw r3, r0
    bge VolumeCalibration_Tick_L_80039F78
    stw r0, 0x24(r30)
    VolumeCalibration_Tick_L_80039F78:
    bl GetInputManager
    li r4, 0x0
    bl InputMgr_GetPlayer
    lwz r12, 0x0(r3)
    mr r31, r3
    li r4, 0x401
    lwz r12, 0x20(r12)
    mtctr r12
    bctrl
    clrlwi r0, r3, 24
    cmplwi r0, 0x1
    bne VolumeCalibration_Tick_L_80039FB0
    li r3, -0x4
    b VolumeCalibration_Tick_L_80039FF4
    VolumeCalibration_Tick_L_80039FB0:
    bl StrPcb_GetInstance
    bl StrPcb_GetReceivedPosData
    stw r3, 0x8(r30)
    mr r3, r31
    li r4, 0x40
    lwz r12, 0x0(r31)
    lwz r12, 0x20(r12)
    mtctr r12
    bctrl
    clrlwi r0, r3, 24
    cmplwi r0, 0x1
    bne VolumeCalibration_Tick_L_80039FF0
    bl StrPcb_GetInstance
    li r4, 0xc
    li r5, 0x0
    bl StrPcb_SetStatusBits
    VolumeCalibration_Tick_L_80039FF0:
    li r3, -0x2
    VolumeCalibration_Tick_L_80039FF4:
    lwz r0, 0x14(r1)
    lwz r31, 0xc(r1)
    lwz r30, 0x8(r1)
    mtlr r0
    addi r1, r1, 0x10
    blr
}

#pragma exceptions off
void *VolumeCalibration_Dtor(VolumeCalibration *self, short freeFlag) {
    if (self != 0) {
        self->vtbl = lbl_803F57CC;
        JvsInput_SetSteeringCalibration(self->steer);
        JvsInput_SetAccelCalibration(self->accelMin);
        JvsInput_SetBrakeCalibration(self->brakeMin);
        StrPcb_SetPositionTarget(StrPcb_GetInstance(), (short)self->posData);
        lbl_80598A60.steer = self->steer;
        lbl_80598A60.pos = self->posData;
        lbl_80598A60.accel = self->accelMin;
        lbl_80598A60.brake = self->brakeMin;
        Backup_PublishShadowCopy_Inline();
        dtor_8002CDF4(self, 0);
        if (freeFlag > 0) {
            MemoryManager_TimedFree(self);
        }
    }
    return self;
}
#pragma exceptions reset

#pragma exceptions off
VolumeCalibration *VolumeCalibration_Ctor(void) {
    VolumeCalibration *self;
    int brake;
    int accel;

    self = (VolumeCalibration *)Alloc(0x28);
    if (self != 0) {
        GameMode_BaseInit(self);
        self->vtbl = lbl_803F57CC;
        self->steer = 0x7A40;
        self->posData = 0x1FF;
        self->steerMin = 0x7A3F;
        self->steerMax = 0x7A41;
        self->field_0c = 1;
        brake = g_jvsOperatorBits.brake;
        accel = g_jvsOperatorBits.accel;
        self->accelMin = accel;
        self->accelMax = accel;
        self->brakeMin = brake;
        self->brakeMax = brake;
    }
    return self;
}
#pragma exceptions reset

/* --- manual extab/extabindex emit (approach B, all four fns) ---
 * Source emit order = target section layout order (ascending address):
 *   @etb_80005EA0 DrawOverlay (size 0x8,  saved GPR r27-r31, large frame)
 *   @etb_80005EA8 Tick        (size 0x8,  saved GPR r30-r31, large frame)
 *   @etb_80005EB0 Dtor        (size 0x8,  saved GPR r30-r31, large frame)
 *   @etb_80005EB8 Ctor        (size 0x18, saved GPR r31 + DELETEPOINTER r31
 *                              through PC=0x24 w/ dtor MemoryManager_TimedFree)
 *   @eti_8001FB2C / @eti_8001FB38 / @eti_8001FB44 / @eti_8001FB50 accordingly.
 */
#pragma section R ".extab_user"
__declspec(section ".extab_user") static const struct {
    unsigned int f0;
    unsigned int f1;
} extab_VolumeCalibration_DrawOverlay = {
    0x28080000, 0x00000000
};
__declspec(section ".extab_user") static const struct {
    unsigned int f0;
    unsigned int f1;
} extab_VolumeCalibration_Tick = {
    0x10080000, 0x00000000
};
__declspec(section ".extab_user") static const struct {
    unsigned int f0;
    unsigned int f1;
} extab_VolumeCalibration_Dtor = {
    0x10080000, 0x00000000
};
__declspec(section ".extab_user") static const struct {
    unsigned int f0;
    unsigned int f1;
    unsigned int f2;
    unsigned int f3;
    unsigned int f4;
    void *f5;
} extab_VolumeCalibration_Ctor = {
    0x08080000, 0x00000024, 0x00000010, 0x00000000, 0x8A80001F, (void *)&MemoryManager_TimedFree
};

#pragma section R ".extabindex_user"
__declspec(section ".extabindex_user") static const struct {
    void *fn;
    unsigned int fn_size;
    void *extab;
} extabindex_VolumeCalibration_DrawOverlay = {
    (void *)&VolumeCalibration_DrawOverlay, 0x000000CC, (void *)&extab_VolumeCalibration_DrawOverlay
};
__declspec(section ".extabindex_user") static const struct {
    void *fn;
    unsigned int fn_size;
    void *extab;
} extabindex_VolumeCalibration_Tick = {
    (void *)&VolumeCalibration_Tick, 0x00000130, (void *)&extab_VolumeCalibration_Tick
};
__declspec(section ".extabindex_user") static const struct {
    void *fn;
    unsigned int fn_size;
    void *extab;
} extabindex_VolumeCalibration_Dtor = {
    (void *)&VolumeCalibration_Dtor, 0x000000B8, (void *)&extab_VolumeCalibration_Dtor
};
__declspec(section ".extabindex_user") static const struct {
    void *fn;
    unsigned int fn_size;
    void *extab;
} extabindex_VolumeCalibration_Ctor = {
    (void *)&VolumeCalibration_Ctor, 0x00000090, (void *)&extab_VolumeCalibration_Ctor
};

} /* extern "C" */
