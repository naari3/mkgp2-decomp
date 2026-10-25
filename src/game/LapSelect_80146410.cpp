/*
 * 0x80146410..0x80147468: lap select controller.
 */
#pragma cplusplus on

class InputPlayer {
public:
    virtual void v8();
    virtual void vC();
    virtual void v10();
    virtual void v14();
    virtual void v18();
    virtual void v1C();
    virtual unsigned char Pressed(int mask);
};
class VObjC {
public:
    virtual void v8();
    virtual void vC();
    virtual void v10();
    virtual void v14();
};
struct Countdown {
    void *vt;
    int f4;
    int delay;
    int state;
};
struct SelSlot {
    char pad0[0x24];
    float t;
};
struct LapSel {
    char pad0[0x18];
    int mode;
    float f1C;
    int cur;
    SelSlot slots[2];
    int timer;
    Countdown *cd;
    void *p7c;
};
struct TripleObj {
    char pad0[0x14];
    void **vt14;
    void *p18;
};

struct XfSlot {
    float ox, oy, scx, scy;
    float m0, m1, m2, m3;
    char pad20[8];
};
struct XfPanel {
    int ctx;
    char pad4[0x20];
    XfSlot slots[2];
};

/* TOP-END */

extern "C" {
void **GetInputManager(void);
class InputPlayer *InputMgr_GetPlayer(void **mgr, int idx);
void fn_801FE27C(int n);
void fn_801FE390(void);
extern const float lbl_806D7B58;
extern const float lbl_806D7B5C;
void fn_801674AC(void *p);
extern void fn_801675A4();
void fn_8016918C(int ctx, int a, int b, float x, float y, float sx, float sy, float c0, float c1, float c2, float c3);
extern void fn_801FEF18();
extern unsigned int lbl_806D7B60;
extern unsigned int lbl_806D7B64;
extern unsigned int lbl_806D7B68;
extern unsigned int lbl_806D7B6C;
extern unsigned int lbl_806D7B70;
extern unsigned int lbl_806D7B74;
extern unsigned int lbl_806D7B78;
extern unsigned int lbl_806D7B7C;
extern unsigned int lbl_806D7B80;
extern unsigned int lbl_806D7B84;
extern unsigned int lbl_806D7B88;
extern unsigned int lbl_806D7B8C;
extern unsigned int lbl_806D7B90;
extern unsigned int lbl_806D7B94;
extern unsigned int lbl_806D7B98;
extern unsigned int lbl_806D7B9C;
extern unsigned int lbl_806D7BA0;
extern unsigned int lbl_806D7BA4;
extern unsigned int lbl_806D7BA8;
extern unsigned int lbl_806D7BAC;
extern unsigned int lbl_806D7BB0;
extern unsigned int lbl_806D7BB4;
extern unsigned int lbl_806D7BB8;
extern void fn_80146160();
extern void fn_80146188();
extern void fn_80167310();
extern void fn_8016733C();
extern void fn_801673A8();
extern void fn_801673D4();
extern void fn_801FE348();
extern void fn_801FEF34();
extern void fn_801FF00C();
extern unsigned int lbl_806D7BBC;
extern unsigned int lbl_806D7BC0;
extern unsigned int lbl_806D7BC4;
extern unsigned int lbl_806D7BC8;
extern unsigned int lbl_806D7BCC;
extern unsigned int lbl_806D7BD0;
extern unsigned int lbl_806D7BD4;
extern unsigned int lbl_806D7BD8;
extern unsigned int lbl_806D7BDC;
extern unsigned int lbl_806D7BE0;
extern unsigned int lbl_806D7BE4;
extern unsigned int lbl_806D7BE8;
extern unsigned int lbl_806D7BEC;
extern unsigned int lbl_806D7BF0;
extern unsigned int lbl_806D7BF4;
extern unsigned int lbl_806D7BF8;
extern unsigned int lbl_806D7BFC;
extern unsigned int lbl_806D7C00;
extern unsigned int lbl_806D7C04;
extern unsigned int lbl_806D7C08;
extern unsigned int lbl_80362620[];
extern unsigned int lbl_80362630[];
extern unsigned int lbl_8048EFB8[];
extern void fn_801681E8();
extern void vsprintf();
extern unsigned int lbl_80362650[];
int fn_80146410(LapSel *self);
void fn_80146574(LapSel *self);
asm void fn_8014660C(void);
asm void fn_80146960(void);
asm void fn_80147200(void);
void fn_801473DC(XfPanel *self, int idx, int a, int b, float x, float y, float sx, float sy, float c0, float c1, float c2, float c3);

#pragma section R ".extab_user"


__declspec(section ".extab_user") static const unsigned char extab_fn_8014660C[8] = {
    0x18, 0x4A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

__declspec(section ".extab_user") static const unsigned char extab_fn_80146960[8] = {
    0x18, 0x8A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

__declspec(section ".extab_user") static const unsigned char extab_fn_80147200[8] = {
    0x12, 0x0A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};


#pragma section R ".extabindex_user"


__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_fn_8014660C = {
    (void *)&fn_8014660C, 0x00000354, (void *)extab_fn_8014660C
};

__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_fn_80146960 = {
    (void *)&fn_80146960, 0x000008A0, (void *)extab_fn_80146960
};

__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_fn_80147200 = {
    (void *)&fn_80147200, 0x000001DC, (void *)extab_fn_80147200
};


}

inline bool Countdown_Tick(Countdown *c) {
    if (c->delay > 0) {
        c->delay--;
        return 0;
    }
    if (c->state == 1) {
        c->state = 2;
    }
    return c->state <= 0;
}
inline bool TickTimer(LapSel *self) {
    if (self->timer > 0) {
        self->timer--;
        fn_801FE27C(self->timer);
        return 1;
    }
    return 0;
}
inline void Select(LapSel *self, int idx) {
    if (self->mode == 1 && self->cur != idx) {
        if (self->slots[self->cur].t >= lbl_806D7B58) {
            self->slots[self->cur].t = lbl_806D7B5C;
        }
        self->cur = idx;
        self->f1C = lbl_806D7B58;
        fn_801FE390();
    }
}





extern "C" int fn_80146410(LapSel *self)
{
    if (!TickTimer(self)) {
        return 1;
    }
    if (self->cur == 0) {
        if (InputMgr_GetPlayer(GetInputManager(), 0)->Pressed(0x20)) {
            Select(self, 1);
        }
    } else {
        if (InputMgr_GetPlayer(GetInputManager(), 0)->Pressed(0x10)) {
            Select(self, 0);
        }
    }
    return 0;
}

extern "C" void fn_80146574(LapSel *self)
{
    fn_801674AC(self->p7c);
    if (self->cd) {
        if (Countdown_Tick(self->cd)) {
            ((VObjC *)self->cd)->v14();
        }
    }
}

extern "C" asm void fn_8014660C(void) { /* 0x8014660C size:0x354 */
    nofralloc
    stwu r1, -0x30(r1)
    mflr r0
    stw r0, 0x34(r1)
    stfd f31, 0x20(r1)
    psq_st f31, 0x28(r1), 0, 0
    stw r31, 0x1c(r1)
    stw r30, 0x18(r1)
    stw r29, 0x14(r1)
    mr r29, r3
    lwz r0, 0x18(r3)
    cmpwi r0, 0x5
    beq fn_8014660C_L_8014693C
    lfs f31, lbl_806D7B58(r2)
    mr r31, r29
    li r30, 0x0
    fn_8014660C_L_80146648:
    lwz r3, 0x0(r29)
    li r4, 0x8cc
    lfs f1, 0x24(r31)
    li r5, 0x0
    lfs f2, 0x28(r31)
    lfs f3, 0x2c(r31)
    lfs f4, 0x30(r31)
    lfs f5, 0x34(r31)
    lfs f6, 0x38(r31)
    lfs f7, 0x3c(r31)
    lfs f8, 0x40(r31)
    bl fn_8016918C
    lfs f0, 0x48(r31)
    fcmpo cr0, f0, f31
    cror eq, gt, eq
    bne fn_8014660C_L_80146814
    lfs f2, lbl_806D7B60(r2)
    fcmpo cr0, f0, f2
    cror eq, lt, eq
    bne fn_8014660C_L_801466B8
    lfs f1, lbl_806D7B64(r2)
    lfs f3, lbl_806D7B6C(r2)
    fmuls f4, f1, f0
    lfs f2, lbl_806D7B68(r2)
    lfs f1, lbl_806D7B70(r2)
    fmadds f3, f3, f4, f2
    fmadds f4, f1, f4, f2
    b fn_8014660C_L_80146784
    fn_8014660C_L_801466B8:
    lfs f1, lbl_806D7B74(r2)
    fcmpo cr0, f0, f1
    cror eq, lt, eq
    bne fn_8014660C_L_801466F0
    fsubs f1, f0, f2
    lfs f2, lbl_806D7B80(r2)
    lfs f3, lbl_806D7B7C(r2)
    lfs f4, lbl_806D7B78(r2)
    fmuls f2, f2, f1
    lfs f1, lbl_806D7B84(r2)
    fmuls f2, f3, f2
    fsubs f3, f4, f2
    fadds f4, f1, f2
    b fn_8014660C_L_80146784
    fn_8014660C_L_801466F0:
    lfs f2, lbl_806D7B88(r2)
    fcmpo cr0, f0, f2
    cror eq, lt, eq
    bne fn_8014660C_L_80146728
    fsubs f1, f0, f1
    lfs f2, lbl_806D7B64(r2)
    lfs f4, lbl_806D7B80(r2)
    lfs f3, lbl_806D7B84(r2)
    fmuls f5, f2, f1
    lfs f2, lbl_806D7B8C(r2)
    lfs f1, lbl_806D7B78(r2)
    fnmsubs f3, f4, f5, f3
    fnmsubs f4, f2, f5, f1
    b fn_8014660C_L_80146784
    fn_8014660C_L_80146728:
    lfs f1, lbl_806D7B90(r2)
    fcmpo cr0, f0, f1
    cror eq, lt, eq
    bne fn_8014660C_L_80146760
    fsubs f1, f0, f2
    lfs f2, lbl_806D7B80(r2)
    lfs f3, lbl_806D7B7C(r2)
    lfs f4, lbl_806D7B94(r2)
    fmuls f2, f2, f1
    lfs f1, lbl_806D7B98(r2)
    fmuls f2, f3, f2
    fsubs f3, f4, f2
    fadds f4, f1, f2
    b fn_8014660C_L_80146784
    fn_8014660C_L_80146760:
    fsubs f1, f0, f1
    lfs f2, lbl_806D7B70(r2)
    lfs f4, lbl_806D7B9C(r2)
    lfs f3, lbl_806D7B98(r2)
    fmuls f5, f2, f1
    lfs f2, lbl_806D7BA0(r2)
    lfs f1, lbl_806D7B94(r2)
    fmadds f3, f4, f5, f3
    fmadds f4, f2, f5, f1
    fn_8014660C_L_80146784:
    lfs f1, lbl_806D7B74(r2)
    fcmpo cr0, f0, f1
    cror eq, lt, eq
    bne fn_8014660C_L_801467A0
    lfs f1, lbl_806D7B7C(r2)
    fmuls f2, f1, f0
    b fn_8014660C_L_801467C8
    fn_8014660C_L_801467A0:
    lfs f1, lbl_806D7B88(r2)
    fcmpo cr0, f0, f1
    cror eq, lt, eq
    bne fn_8014660C_L_801467B8
    lfs f2, lbl_806D7BA4(r2)
    b fn_8014660C_L_801467C8
    fn_8014660C_L_801467B8:
    lfs f1, lbl_806D7BA8(r2)
    lfs f2, lbl_806D7B64(r2)
    fsubs f0, f1, f0
    fmuls f2, f2, f0
    fn_8014660C_L_801467C8:
    lfs f6, 0x30(r31)
    li r4, 0x730
    lfs f7, 0x2c(r31)
    li r5, 0x1
    lfs f0, 0x40(r31)
    fmuls f4, f6, f4
    lfs f5, lbl_806D7BAC(r2)
    fmuls f3, f7, f3
    lfs f1, 0x24(r31)
    fmuls f8, f0, f2
    lfs f2, lbl_806D7BB0(r2)
    lfs f0, 0x28(r31)
    fnmsubs f1, f5, f7, f1
    lwz r3, 0x0(r29)
    fmadds f2, f2, f6, f0
    lfs f5, 0x34(r31)
    lfs f6, 0x38(r31)
    lfs f7, 0x3c(r31)
    bl fn_8016918C
    fn_8014660C_L_80146814:
    addi r30, r30, 0x1
    addi r31, r31, 0x28
    cmpwi r30, 0x2
    blt fn_8014660C_L_80146648
    mr r3, r29
    lwz r12, 0x14(r29)
    lwz r12, 0x24(r12)
    mtctr r12
    bctrl
    lfs f4, 0x30(r29)
    li r4, 0x8ca
    lfs f3, 0x2c(r29)
    li r5, 0x0
    lfs f5, lbl_806D7BB4(r2)
    lfs f1, 0x24(r29)
    lfs f2, lbl_806D7BB8(r2)
    lfs f0, 0x28(r29)
    fnmsubs f1, f5, f3, f1
    lwz r3, 0x0(r29)
    fnmsubs f2, f2, f4, f0
    lfs f5, 0x34(r29)
    lfs f6, 0x38(r29)
    lfs f7, 0x3c(r29)
    lfs f8, 0x40(r29)
    bl fn_8016918C
    lfs f4, 0x58(r29)
    li r4, 0x8cb
    lfs f3, 0x54(r29)
    li r5, 0x0
    lfs f5, lbl_806D7BB4(r2)
    lfs f1, 0x4c(r29)
    lfs f2, lbl_806D7BB8(r2)
    lfs f0, 0x50(r29)
    fnmsubs f1, f5, f3, f1
    lwz r3, 0x0(r29)
    fnmsubs f2, f2, f4, f0
    lfs f5, 0x5c(r29)
    lfs f6, 0x60(r29)
    lfs f7, 0x64(r29)
    lfs f8, 0x68(r29)
    bl fn_8016918C
    lwz r3, 0x78(r29)
    cmplwi r3, 0x0
    beq fn_8014660C_L_8014690C
    lwz r0, 0x8(r3)
    cmpwi r0, 0x0
    ble fn_8014660C_L_801468D8
    li r0, 0x0
    b fn_8014660C_L_801468E8
    fn_8014660C_L_801468D8:
    lwz r0, 0xc(r3)
    li r4, 0x1
    cntlzw r0, r0
    rlwnm r0, r4, r0, 31, 31
    fn_8014660C_L_801468E8:
    clrlwi. r0, r0, 24
    beq fn_8014660C_L_8014690C
    lwz r4, 0x74(r29)
    bl fn_801FEF18
    lwz r3, 0x78(r29)
    lwz r12, 0x0(r3)
    lwz r12, 0x10(r12)
    mtctr r12
    bctrl
    fn_8014660C_L_8014690C:
    lwz r3, 0x7c(r29)
    bl fn_801675A4
    lwz r3, 0x80(r29)
    lwz r12, 0x14(r3)
    lwz r12, 0x14(r12)
    mtctr r12
    bctrl
    lwz r3, 0x80(r29)
    lwz r12, 0x14(r3)
    lwz r12, 0x18(r12)
    mtctr r12
    bctrl
    fn_8014660C_L_8014693C:
    psq_l f31, 0x28(r1), 0, 0
    lwz r0, 0x34(r1)
    lfd f31, 0x20(r1)
    lwz r31, 0x1c(r1)
    lwz r30, 0x18(r1)
    lwz r29, 0x14(r1)
    mtlr r0
    addi r1, r1, 0x30
    blr
}

extern "C" asm void fn_80146960(void) { /* 0x80146960 size:0x8A0 */
    nofralloc
    stwu r1, -0x40(r1)
    mflr r0
    stw r0, 0x44(r1)
    stfd f31, 0x30(r1)
    psq_st f31, 0x38(r1), 0, 0
    stfd f30, 0x20(r1)
    psq_st f30, 0x28(r1), 0, 0
    stw r31, 0x1c(r1)
    stw r30, 0x18(r1)
    stw r29, 0x14(r1)
    mr r31, r3
    lwz r0, 0x18(r3)
    cmpwi r0, 0x5
    beq fn_80146960_L_801471D4
    cmpwi r0, 0x2
    beq fn_80146960_L_80146C8C
    bge fn_80146960_L_801469B4
    cmpwi r0, 0x0
    beq fn_80146960_L_801469C4
    bge fn_80146960_L_80146AA0
    b fn_80146960_L_80146FB0
    fn_80146960_L_801469B4:
    cmpwi r0, 0x4
    beq fn_80146960_L_80146DCC
    bge fn_80146960_L_80146FB0
    b fn_80146960_L_80146D3C
    fn_80146960_L_801469C4:
    lfs f0, 0x1c(r31)
    lfs f3, lbl_806D7B58(r2)
    lfs f1, lbl_806D7B64(r2)
    stfs f3, 0x24(r31)
    fmuls f1, f1, f0
    lfs f2, lbl_806D7BA4(r2)
    stfs f3, 0x28(r31)
    lfs f0, lbl_806D7B60(r2)
    stfs f1, 0x2c(r31)
    stfs f1, 0x30(r31)
    stfs f2, 0x34(r31)
    stfs f2, 0x38(r31)
    stfs f2, 0x3c(r31)
    stfs f2, 0x40(r31)
    stfs f3, 0x4c(r31)
    stfs f3, 0x50(r31)
    stfs f1, 0x54(r31)
    stfs f1, 0x58(r31)
    stfs f2, 0x5c(r31)
    stfs f2, 0x60(r31)
    stfs f2, 0x64(r31)
    stfs f2, 0x68(r31)
    lfs f1, 0x1c(r31)
    fadds f1, f1, f2
    fcmpo cr0, f1, f0
    stfs f1, 0x1c(r31)
    cror eq, gt, eq
    bne fn_80146960_L_80146FB0
    li r0, 0x1
    stw r0, 0x18(r31)
    stfs f3, 0x1c(r31)
    lwz r3, 0x7c(r31)
    bl fn_801673D4
    lwz r3, 0x7c(r31)
    bl fn_8016733C
    lwz r0, 0x78(r31)
    cmplwi r0, 0x0
    bne fn_80146960_L_80146A7C
    li r3, 0x0
    li r4, 0x0
    bl fn_801FF00C
    stw r3, 0x78(r31)
    lfs f1, lbl_806D7BBC(r2)
    lwz r3, 0x78(r31)
    lfs f2, lbl_806D7BC0(r2)
    bl fn_801FEF34
    fn_80146960_L_80146A7C:
    lwz r0, 0x20(r31)
    cmpwi r0, 0x0
    bne fn_80146960_L_80146A94
    lwz r3, 0x80(r31)
    bl fn_80146160
    b fn_80146960_L_80146FB0
    fn_80146960_L_80146A94:
    lwz r3, 0x80(r31)
    bl fn_80146188
    b fn_80146960_L_80146FB0
    fn_80146960_L_80146AA0:
    lfs f31, lbl_806D7B58(r2)
    mr r30, r31
    lfs f30, lbl_806D7BA4(r2)
    li r29, 0x0
    fn_80146960_L_80146AB0:
    stfs f31, 0x24(r30)
    stfs f31, 0x28(r30)
    lwz r0, 0x20(r31)
    cmpw r29, r0
    bne fn_80146960_L_80146C30
    lfs f1, lbl_806D7B60(r2)
    lfs f0, 0x44(r30)
    fcmpu cr0, f1, f0
    bne fn_80146960_L_80146C30
    lfs f2, 0x1c(r31)
    fcmpo cr0, f2, f1
    bge fn_80146960_L_80146B08
    lfs f0, lbl_806D7B64(r2)
    lfs f1, lbl_806D7BC4(r2)
    fmuls f3, f0, f2
    lfs f2, lbl_806D7BA4(r2)
    lfs f0, lbl_806D7BC8(r2)
    fmadds f1, f1, f3, f2
    fmadds f0, f0, f3, f2
    stfs f1, 0x2c(r30)
    stfs f0, 0x30(r30)
    b fn_80146960_L_80146BE8
    fn_80146960_L_80146B08:
    lfs f0, lbl_806D7B74(r2)
    fcmpo cr0, f2, f0
    bge fn_80146960_L_80146B44
    fsubs f0, f2, f1
    lfs f1, lbl_806D7B80(r2)
    lfs f2, lbl_806D7BD0(r2)
    lfs f3, lbl_806D7BCC(r2)
    fmuls f1, f1, f0
    lfs f0, lbl_806D7BD4(r2)
    fmuls f2, f2, f1
    fsubs f1, f3, f2
    fadds f0, f0, f2
    stfs f1, 0x2c(r30)
    stfs f0, 0x30(r30)
    b fn_80146960_L_80146BE8
    fn_80146960_L_80146B44:
    lfs f1, lbl_806D7B88(r2)
    fcmpo cr0, f2, f1
    bge fn_80146960_L_80146B80
    fsubs f0, f2, f0
    lfs f1, lbl_806D7B64(r2)
    lfs f3, lbl_806D7BD8(r2)
    lfs f2, lbl_806D7BD4(r2)
    fmuls f4, f1, f0
    lfs f1, lbl_806D7B9C(r2)
    lfs f0, lbl_806D7BCC(r2)
    fnmsubs f2, f3, f4, f2
    fnmsubs f0, f1, f4, f0
    stfs f2, 0x2c(r30)
    stfs f0, 0x30(r30)
    b fn_80146960_L_80146BE8
    fn_80146960_L_80146B80:
    lfs f0, lbl_806D7B90(r2)
    fcmpo cr0, f2, f0
    bge fn_80146960_L_80146BBC
    fsubs f0, f2, f1
    lfs f1, lbl_806D7B80(r2)
    lfs f2, lbl_806D7BD0(r2)
    lfs f3, lbl_806D7BDC(r2)
    fmuls f1, f1, f0
    lfs f0, lbl_806D7BE0(r2)
    fmuls f2, f2, f1
    fsubs f1, f3, f2
    fadds f0, f0, f2
    stfs f1, 0x2c(r30)
    stfs f0, 0x30(r30)
    b fn_80146960_L_80146BE8
    fn_80146960_L_80146BBC:
    fsubs f0, f2, f0
    lfs f1, lbl_806D7B70(r2)
    lfs f3, lbl_806D7BC4(r2)
    lfs f2, lbl_806D7BE0(r2)
    fmuls f4, f1, f0
    lfs f1, lbl_806D7BC8(r2)
    lfs f0, lbl_806D7BDC(r2)
    fmadds f2, f3, f4, f2
    fmadds f0, f1, f4, f0
    stfs f2, 0x2c(r30)
    stfs f0, 0x30(r30)
    fn_80146960_L_80146BE8:
    lfs f2, 0x1c(r31)
    lfs f1, lbl_806D7BA4(r2)
    lfs f0, lbl_806D7BA8(r2)
    fadds f1, f2, f1
    fcmpo cr0, f1, f0
    stfs f1, 0x1c(r31)
    cror eq, gt, eq
    bne fn_80146960_L_80146C10
    lfs f0, lbl_806D7B58(r2)
    stfs f0, 0x1c(r31)
    fn_80146960_L_80146C10:
    cmpwi r29, 0x0
    bne fn_80146960_L_80146C24
    lwz r3, 0x80(r31)
    bl fn_80146160
    b fn_80146960_L_80146C3C
    fn_80146960_L_80146C24:
    lwz r3, 0x80(r31)
    bl fn_80146188
    b fn_80146960_L_80146C3C
    fn_80146960_L_80146C30:
    lfs f0, lbl_806D7BA4(r2)
    stfs f0, 0x2c(r30)
    stfs f0, 0x30(r30)
    fn_80146960_L_80146C3C:
    stfs f30, 0x34(r30)
    addi r29, r29, 0x1
    cmpwi r29, 0x2
    stfs f30, 0x38(r30)
    stfs f30, 0x3c(r30)
    stfs f30, 0x40(r30)
    addi r30, r30, 0x28
    blt fn_80146960_L_80146AB0
    mr r3, r31
    lwz r12, 0x14(r31)
    lwz r12, 0x20(r12)
    mtctr r12
    bctrl
    clrlwi. r0, r3, 24
    beq fn_80146960_L_80146FB0
    li r0, 0x2
    lfs f0, lbl_806D7B58(r2)
    stw r0, 0x18(r31)
    stfs f0, 0x1c(r31)
    b fn_80146960_L_80146FB0
    fn_80146960_L_80146C8C:
    lfs f2, lbl_806D7B58(r2)
    lfs f0, lbl_806D7BA4(r2)
    stfs f2, 0x24(r31)
    lfs f1, lbl_806D7B60(r2)
    stfs f2, 0x28(r31)
    stfs f0, 0x2c(r31)
    stfs f0, 0x30(r31)
    stfs f0, 0x34(r31)
    stfs f0, 0x38(r31)
    stfs f0, 0x3c(r31)
    stfs f0, 0x40(r31)
    stfs f2, 0x4c(r31)
    stfs f2, 0x50(r31)
    stfs f0, 0x54(r31)
    stfs f0, 0x58(r31)
    stfs f0, 0x5c(r31)
    stfs f0, 0x60(r31)
    stfs f0, 0x64(r31)
    stfs f0, 0x68(r31)
    lwz r4, 0x20(r31)
    mulli r0, r4, 0x28
    add r3, r31, r0
    lfs f0, 0x44(r3)
    fcmpu cr0, f1, f0
    bne fn_80146960_L_80146FB0
    cmpwi r4, 0x0
    bne fn_80146960_L_80146D14
    li r0, 0x3
    stw r0, 0x18(r31)
    lfs f0, 0x48(r31)
    fcmpo cr0, f0, f2
    bge fn_80146960_L_80146D1C
    stfs f2, 0x48(r31)
    b fn_80146960_L_80146D1C
    fn_80146960_L_80146D14:
    li r0, 0x4
    stw r0, 0x18(r31)
    fn_80146960_L_80146D1C:
    lfs f0, lbl_806D7B58(r2)
    stfs f0, 0x1c(r31)
    lwz r3, 0x7c(r31)
    bl fn_801673A8
    lwz r3, 0x7c(r31)
    bl fn_80167310
    bl fn_801FE348
    b fn_80146960_L_80146FB0
    fn_80146960_L_80146D3C:
    lfs f2, lbl_806D7B58(r2)
    li r0, 0x1
    lfs f1, lbl_806D7BA4(r2)
    stfs f2, 0x24(r31)
    stfs f2, 0x28(r31)
    stfs f1, 0x2c(r31)
    stfs f1, 0x30(r31)
    stfs f1, 0x34(r31)
    stfs f1, 0x38(r31)
    stfs f1, 0x3c(r31)
    stfs f1, 0x40(r31)
    lfs f0, 0x48(r31)
    fcmpo cr0, f0, f2
    cror eq, gt, eq
    bne fn_80146960_L_80146D7C
    li r0, 0x0
    fn_80146960_L_80146D7C:
    stfs f2, 0x4c(r31)
    stfs f2, 0x50(r31)
    stfs f1, 0x54(r31)
    stfs f1, 0x58(r31)
    stfs f1, 0x5c(r31)
    stfs f1, 0x60(r31)
    stfs f1, 0x64(r31)
    stfs f1, 0x68(r31)
    lfs f0, 0x70(r31)
    fcmpo cr0, f0, f2
    cror eq, gt, eq
    bne fn_80146960_L_80146DB0
    li r0, 0x0
    fn_80146960_L_80146DB0:
    clrlwi. r0, r0, 24
    beq fn_80146960_L_80146FB0
    li r0, 0x4
    lfs f0, lbl_806D7B58(r2)
    stw r0, 0x18(r31)
    stfs f0, 0x1c(r31)
    b fn_80146960_L_80146FB0
    fn_80146960_L_80146DCC:
    lis r3, lbl_8048EFB8@ha
    li r0, 0x2
    addi r4, r3, lbl_8048EFB8@l
    lfs f3, lbl_806D7BA4(r2)
    mr r3, r31
    lfs f2, lbl_806D7BE8(r2)
    li r5, 0x0
    mtctr r0
    fn_80146960_L_80146DEC:
    lwz r0, 0x20(r31)
    cmpw r5, r0
    bne fn_80146960_L_80146ED4
    lfs f4, 0x1c(r31)
    lfs f6, lbl_806D7BE4(r2)
    fcmpo cr0, f4, f6
    cror eq, lt, eq
    bne fn_80146960_L_80146E3C
    lfs f1, lbl_806D7B58(r2)
    lfs f4, lbl_806D7B80(r2)
    stfs f1, 0x24(r3)
    lfs f0, lbl_806D7BA4(r2)
    stfs f1, 0x28(r3)
    lfs f1, 0x1c(r31)
    fmuls f1, f4, f1
    fnmsubs f0, f4, f1, f0
    stfs f0, 0x2c(r3)
    lfs f0, 0x2c(r3)
    stfs f0, 0x30(r3)
    b fn_80146960_L_80146F18
    fn_80146960_L_80146E3C:
    lfs f1, lbl_806D7BE8(r2)
    fcmpo cr0, f4, f1
    cror eq, lt, eq
    bne fn_80146960_L_80146E84
    lfs f0, lbl_806D7B58(r2)
    lfs f4, lbl_806D7B80(r2)
    stfs f0, 0x24(r3)
    lfs f5, lbl_806D7B7C(r2)
    stfs f0, 0x28(r3)
    lfs f0, lbl_806D7BEC(r2)
    lfs f1, 0x1c(r31)
    fsubs f1, f1, f6
    fmuls f1, f4, f1
    fnmsubs f0, f5, f1, f0
    stfs f0, 0x2c(r3)
    lfs f0, 0x2c(r3)
    stfs f0, 0x30(r3)
    b fn_80146960_L_80146F18
    fn_80146960_L_80146E84:
    lfs f0, lbl_806D7BF0(r2)
    fcmpo cr0, f4, f0
    cror eq, lt, eq
    bne fn_80146960_L_80146F18
    fsubs f0, f4, f1
    lfs f1, lbl_806D7B64(r2)
    lfs f5, 0x0(r4)
    lfs f4, 0x4(r4)
    fmuls f6, f1, f0
    lfs f1, lbl_806D7BF8(r2)
    lfs f0, lbl_806D7BF4(r2)
    fmuls f5, f6, f5
    fmuls f4, f6, f4
    fmadds f0, f1, f6, f0
    stfs f5, 0x24(r3)
    stfs f4, 0x28(r3)
    stfs f0, 0x2c(r3)
    lfs f0, 0x2c(r3)
    stfs f0, 0x30(r3)
    b fn_80146960_L_80146F18
    fn_80146960_L_80146ED4:
    lfs f1, lbl_806D7B58(r2)
    lfs f0, lbl_806D7BE8(r2)
    stfs f1, 0x24(r3)
    stfs f1, 0x28(r3)
    lfs f4, 0x1c(r31)
    fcmpo cr0, f4, f0
    cror eq, lt, eq
    bne fn_80146960_L_80146F10
    fsubs f0, f0, f4
    lfs f1, lbl_806D7B70(r2)
    fmuls f0, f1, f0
    stfs f0, 0x2c(r3)
    lfs f0, 0x2c(r3)
    stfs f0, 0x30(r3)
    b fn_80146960_L_80146F18
    fn_80146960_L_80146F10:
    stfs f1, 0x2c(r3)
    stfs f1, 0x30(r3)
    fn_80146960_L_80146F18:
    stfs f3, 0x34(r3)
    stfs f3, 0x38(r3)
    stfs f3, 0x3c(r3)
    lfs f1, 0x1c(r31)
    fcmpo cr0, f1, f2
    cror eq, lt, eq
    bne fn_80146960_L_80146F3C
    stfs f3, 0x40(r3)
    b fn_80146960_L_80146F68
    fn_80146960_L_80146F3C:
    lfs f0, lbl_806D7BF0(r2)
    fcmpo cr0, f1, f0
    cror eq, lt, eq
    bne fn_80146960_L_80146F60
    fsubs f0, f0, f1
    lfs f1, lbl_806D7B64(r2)
    fmuls f0, f1, f0
    stfs f0, 0x40(r3)
    b fn_80146960_L_80146F68
    fn_80146960_L_80146F60:
    lfs f0, lbl_806D7B58(r2)
    stfs f0, 0x40(r3)
    fn_80146960_L_80146F68:
    addi r3, r3, 0x28
    addi r4, r4, 0x8
    addi r5, r5, 0x1
    bdnz fn_80146960_L_80146DEC
    lfs f2, 0x1c(r31)
    lfs f1, lbl_806D7BA4(r2)
    lfs f0, lbl_806D7BFC(r2)
    fadds f1, f2, f1
    fcmpo cr0, f1, f0
    stfs f1, 0x1c(r31)
    cror eq, gt, eq
    bne fn_80146960_L_80146FB0
    li r0, 0x5
    lfs f0, lbl_806D7B58(r2)
    stw r0, 0x18(r31)
    li r0, 0x1
    stfs f0, 0x1c(r31)
    stb r0, 0x4(r31)
    fn_80146960_L_80146FB0:
    lis r4, lbl_80362620@ha
    lis r3, lbl_80362630@ha
    addi r6, r4, lbl_80362620@l
    li r0, 0x2
    mr r5, r31
    addi r4, r3, lbl_80362630@l
    lfs f0, lbl_806D7BE4(r2)
    li r7, 0x0
    lfs f3, lbl_806D7B58(r2)
    mtctr r0
    fn_80146960_L_80146FD8:
    lwz r0, 0x20(r31)
    cmpw r7, r0
    bne fn_80146960_L_80147014
    lfs f4, 0x44(r5)
    lfs f2, lbl_806D7B60(r2)
    fcmpo cr0, f4, f2
    bge fn_80146960_L_80147040
    lfs f1, lbl_806D7BA4(r2)
    fadds f1, f4, f1
    stfs f1, 0x44(r5)
    lfs f1, 0x44(r5)
    fcmpo cr0, f1, f2
    ble fn_80146960_L_80147040
    stfs f2, 0x44(r5)
    b fn_80146960_L_80147040
    fn_80146960_L_80147014:
    lfs f4, 0x44(r5)
    lfs f2, lbl_806D7B58(r2)
    fcmpo cr0, f4, f2
    ble fn_80146960_L_80147040
    lfs f1, lbl_806D7BA4(r2)
    fsubs f1, f4, f1
    stfs f1, 0x44(r5)
    lfs f1, 0x44(r5)
    fcmpo cr0, f1, f2
    bge fn_80146960_L_80147040
    stfs f2, 0x44(r5)
    fn_80146960_L_80147040:
    lfs f4, 0x24(r5)
    lfs f2, 0x0(r6)
    lfs f1, 0x4(r6)
    fadds f2, f4, f2
    stfs f2, 0x24(r5)
    lfs f2, 0x28(r5)
    fadds f1, f2, f1
    stfs f1, 0x28(r5)
    lfs f2, 0x44(r5)
    fcmpo cr0, f2, f0
    bge fn_80146960_L_80147084
    lfs f1, lbl_806D7B80(r2)
    lfs f4, lbl_806D7BD8(r2)
    fmuls f2, f1, f2
    lfs f1, lbl_806D7BF4(r2)
    fnmsubs f2, f4, f2, f1
    b fn_80146960_L_801470C4
    fn_80146960_L_80147084:
    lfs f1, lbl_806D7BE8(r2)
    fcmpo cr0, f2, f1
    bge fn_80146960_L_801470AC
    fsubs f2, f2, f0
    lfs f4, lbl_806D7B80(r2)
    lfs f5, lbl_806D7C04(r2)
    lfs f1, lbl_806D7C00(r2)
    fmuls f2, f4, f2
    fmadds f2, f5, f2, f1
    b fn_80146960_L_801470C4
    fn_80146960_L_801470AC:
    fsubs f2, f2, f1
    lfs f4, lbl_806D7B80(r2)
    lfs f5, lbl_806D7BD8(r2)
    lfs f1, lbl_806D7C08(r2)
    fmuls f2, f4, f2
    fnmsubs f2, f5, f2, f1
    fn_80146960_L_801470C4:
    lfs f1, 0x2c(r5)
    fmuls f1, f1, f2
    stfs f1, 0x2c(r5)
    lfs f1, 0x30(r5)
    fmuls f1, f1, f2
    stfs f1, 0x30(r5)
    lwz r0, 0x20(r31)
    cmpw r7, r0
    bne fn_80146960_L_80147130
    lis r3, lbl_80362630@ha
    lfs f5, 0x34(r5)
    lfs f1, lbl_80362630@l(r3)
    lfs f4, 0x4(r4)
    fmuls f5, f5, f1
    lfs f2, 0x8(r4)
    lfs f1, 0xc(r4)
    stfs f5, 0x34(r5)
    lfs f5, 0x38(r5)
    fmuls f4, f5, f4
    stfs f4, 0x38(r5)
    lfs f4, 0x3c(r5)
    fmuls f2, f4, f2
    stfs f2, 0x3c(r5)
    lfs f2, 0x40(r5)
    fmuls f1, f2, f1
    stfs f1, 0x40(r5)
    b fn_80146960_L_80147170
    fn_80146960_L_80147130:
    lfs f2, 0x34(r5)
    lfs f1, 0x10(r4)
    lfs f4, 0x14(r4)
    fmuls f5, f2, f1
    lfs f2, 0x18(r4)
    lfs f1, 0x1c(r4)
    stfs f5, 0x34(r5)
    lfs f5, 0x38(r5)
    fmuls f4, f5, f4
    stfs f4, 0x38(r5)
    lfs f4, 0x3c(r5)
    fmuls f2, f4, f2
    stfs f2, 0x3c(r5)
    lfs f2, 0x40(r5)
    fmuls f1, f2, f1
    stfs f1, 0x40(r5)
    fn_80146960_L_80147170:
    lfs f4, 0x48(r5)
    fcmpo cr0, f4, f3
    cror eq, gt, eq
    bne fn_80146960_L_801471C4
    lfs f2, lbl_806D7BA4(r2)
    lfs f1, lbl_806D7BA8(r2)
    fadds f2, f4, f2
    stfs f2, 0x48(r5)
    lfs f2, 0x48(r5)
    fcmpo cr0, f2, f1
    ble fn_80146960_L_801471C4
    lwz r0, 0x18(r31)
    cmpwi r0, 0x1
    beq fn_80146960_L_801471B0
    cmpwi r0, 0x2
    bne fn_80146960_L_801471BC
    fn_80146960_L_801471B0:
    lfs f1, lbl_806D7B58(r2)
    stfs f1, 0x48(r5)
    b fn_80146960_L_801471C4
    fn_80146960_L_801471BC:
    lfs f1, lbl_806D7B5C(r2)
    stfs f1, 0x48(r5)
    fn_80146960_L_801471C4:
    addi r5, r5, 0x28
    addi r6, r6, 0x8
    addi r7, r7, 0x1
    bdnz fn_80146960_L_80146FD8
    fn_80146960_L_801471D4:
    psq_l f31, 0x38(r1), 0, 0
    lfd f31, 0x30(r1)
    psq_l f30, 0x28(r1), 0, 0
    lfd f30, 0x20(r1)
    lwz r31, 0x1c(r1)
    lwz r30, 0x18(r1)
    lwz r0, 0x44(r1)
    lwz r29, 0x14(r1)
    mtlr r0
    addi r1, r1, 0x40
    blr
}

extern "C" asm void fn_80147200(void) { /* 0x80147200 size:0x1DC */
    nofralloc
    stwu r1, -0x200(r1)
    mflr r0
    stw r0, 0x204(r1)
    stfd f31, 0x1f0(r1)
    psq_st f31, 0x1f8(r1), 0, 0
    stfd f30, 0x1e0(r1)
    psq_st f30, 0x1e8(r1), 0, 0
    stfd f29, 0x1d0(r1)
    psq_st f29, 0x1d8(r1), 0, 0
    stfd f28, 0x1c0(r1)
    psq_st f28, 0x1c8(r1), 0, 0
    stfd f27, 0x1b0(r1)
    psq_st f27, 0x1b8(r1), 0, 0
    stfd f26, 0x1a0(r1)
    psq_st f26, 0x1a8(r1), 0, 0
    stfd f25, 0x190(r1)
    psq_st f25, 0x198(r1), 0, 0
    stfd f24, 0x180(r1)
    psq_st f24, 0x188(r1), 0, 0
    stw r31, 0x17c(r1)
    stw r30, 0x178(r1)
    fmr f24, f1
    mr r30, r3
    fmr f25, f2
    mr r31, r4
    fmr f26, f3
    fmr f27, f4
    fmr f28, f5
    fmr f29, f6
    fmr f30, f7
    fmr f31, f8
    bne cr1, fn_80147200_L_801472A0
    stfd f1, 0x28(r1)
    stfd f2, 0x30(r1)
    stfd f3, 0x38(r1)
    stfd f4, 0x40(r1)
    stfd f5, 0x48(r1)
    stfd f6, 0x50(r1)
    stfd f7, 0x58(r1)
    stfd f8, 0x60(r1)
    fn_80147200_L_801472A0:
    cmpwi r31, 0x0
    stw r3, 0x8(r1)
    stw r4, 0xc(r1)
    stw r5, 0x10(r1)
    stw r6, 0x14(r1)
    stw r7, 0x18(r1)
    stw r8, 0x1c(r1)
    stw r9, 0x20(r1)
    stw r10, 0x24(r1)
    blt fn_80147200_L_80147384
    cmpwi r31, 0x2
    blt fn_80147200_L_801472D4
    b fn_80147200_L_80147384
    fn_80147200_L_801472D4:
    lis r3, lbl_80362650@ha
    li r0, 0x20
    addi r3, r3, lbl_80362650@l
    addi r6, r1, 0x70
    subi r4, r3, 0x4
    mtctr r0
    fn_80147200_L_801472EC:
    lwz r3, 0x4(r4)
    lwzu r0, 0x8(r4)
    stw r3, 0x4(r6)
    stwu r0, 0x8(r6)
    bdnz fn_80147200_L_801472EC
    addi r6, r1, 0x208
    addi r0, r1, 0x8
    lis r3, 0x308
    addi r7, r1, 0x68
    stw r3, 0x68(r1)
    mr r4, r5
    mr r5, r7
    addi r3, r1, 0x74
    stw r6, 0x6c(r1)
    stw r0, 0x70(r1)
    bl vsprintf
    mulli r0, r31, 0x28
    lwz r3, 0x0(r30)
    addi r4, r1, 0x74
    add r5, r30, r0
    lfs f2, 0x30(r5)
    lfs f6, 0x2c(r5)
    lfs f1, 0x24(r5)
    fmuls f4, f27, f2
    lfs f0, 0x28(r5)
    fmuls f3, f26, f6
    lfs f5, 0x34(r5)
    fmadds f1, f24, f6, f1
    lfs f6, 0x38(r5)
    lfs f7, 0x3c(r5)
    fmadds f2, f25, f2, f0
    lfs f0, 0x40(r5)
    fmuls f5, f28, f5
    fmuls f6, f29, f6
    fmuls f7, f30, f7
    fmuls f8, f31, f0
    creqv 6, 6, 6
    bl fn_801681E8
    fn_80147200_L_80147384:
    psq_l f31, 0x1f8(r1), 0, 0
    lfd f31, 0x1f0(r1)
    psq_l f30, 0x1e8(r1), 0, 0
    lfd f30, 0x1e0(r1)
    psq_l f29, 0x1d8(r1), 0, 0
    lfd f29, 0x1d0(r1)
    psq_l f28, 0x1c8(r1), 0, 0
    lfd f28, 0x1c0(r1)
    psq_l f27, 0x1b8(r1), 0, 0
    lfd f27, 0x1b0(r1)
    psq_l f26, 0x1a8(r1), 0, 0
    lfd f26, 0x1a0(r1)
    psq_l f25, 0x198(r1), 0, 0
    lfd f25, 0x190(r1)
    psq_l f24, 0x188(r1), 0, 0
    lfd f24, 0x180(r1)
    lwz r31, 0x17c(r1)
    lwz r0, 0x204(r1)
    lwz r30, 0x178(r1)
    mtlr r0
    addi r1, r1, 0x200
    blr
}

extern "C" void fn_801473DC(XfPanel *self, int idx, int a, int b, float x, float y, float sx, float sy, float c0, float c1, float c2, float c3)
{
    if (idx < 0 || idx >= 2) {
        return;
    }
    fn_8016918C(self->ctx, a, b, x * self->slots[idx].scx + self->slots[idx].ox, y * self->slots[idx].scy + self->slots[idx].oy, sx * self->slots[idx].scx, sy * self->slots[idx].scy, c0 * self->slots[idx].m0, c1 * self->slots[idx].m1, c2 * self->slots[idx].m2, c3 * self->slots[idx].m3);
}

