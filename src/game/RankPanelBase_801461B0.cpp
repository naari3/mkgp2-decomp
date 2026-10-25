/*
 * 0x801461B0..0x8014640C: ranking panel base dtor and draw.
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

/* TOP-END */

extern "C" {
void MemoryManager_TimedFree(void *p);
void fn_8013B87C(void *p, int flag);
extern void *lbl_8048EB44[];
extern void *lbl_8048EE48[];
extern void *lbl_8048EF98[];
extern void Alloc();
extern void PreloadResource();
extern void fn_8013B7A8();
extern void fn_8013B9A0();
extern unsigned int lbl_806D7B50;
extern unsigned int lbl_806D7B54;
extern unsigned int lbl_80361ED0[];
extern void dtor_80143F0C();
TripleObj *fn_801461B0(TripleObj *self, short flag);
asm void fn_80146260(void);

#pragma section R ".extab_user"

__declspec(section ".extab_user") static const struct { unsigned int f0; unsigned int f1; unsigned int f2; unsigned int f3; unsigned int f4; unsigned int f5; unsigned int f6; unsigned int f7; unsigned int f8; unsigned int f9; unsigned int f10; unsigned int f11; unsigned int f12; unsigned int f13; unsigned int f14; unsigned int f15; unsigned int f16; unsigned int f17; unsigned int f18; unsigned int f19; unsigned int f20; void *f21; unsigned int f22; unsigned int f23; void *f24; unsigned int f25; void *f26; unsigned int f27; unsigned int f28; void *f29; unsigned int f30; void *f31; unsigned int f32; unsigned int f33; void *f34; unsigned int f35; void *f36; unsigned int f37; unsigned int f38; void *f39; } extab_fn_80146260 = { 0x180A0000, 0x0000007C, 0x00020058, 0x000000A4, 0x00000050, 0x000000B8, 0x00040058, 0x000000E8, 0x00000064, 0x000000FC, 0x00040058, 0x0000012C, 0x00000078, 0x00000140, 0x00040058, 0x00000170, 0x0000008C, 0x00000184, 0x00000058, 0x00000000, 0x0A80001D, (void *)&MemoryManager_TimedFree, 0x8680001F, 0x00000000, (void *)&dtor_80143F0C, 0x0A80001D, (void *)&MemoryManager_TimedFree, 0x8680001F, 0x00000000, (void *)&dtor_80143F0C, 0x0A80001D, (void *)&MemoryManager_TimedFree, 0x8680001F, 0x00000000, (void *)&dtor_80143F0C, 0x0A80001D, (void *)&MemoryManager_TimedFree, 0x8680001F, 0x00000000, (void *)&dtor_80143F0C };

#pragma section R ".extabindex_user"

__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_fn_80146260 = {
    (void *)&fn_80146260, 0x000001AC, (void *)&extab_fn_80146260
};

}


extern "C" TripleObj *fn_801461B0(TripleObj *self, short flag)
{
    if (self) {
        self->vt14 = lbl_8048EF98;
        if (self->p18) {
            fn_8013B87C(self->p18, 1);
        }
        self->p18 = 0;
        if (self) {
            self->vt14 = lbl_8048EE48;
            if (self->p18) {
                fn_8013B87C(self->p18, 1);
            }
            if (self) {
                self->vt14 = lbl_8048EB44;
            }
        }
        if (flag > 0) MemoryManager_TimedFree(self);
    }
    return self;
}

extern "C" asm void fn_80146260(void) { /* 0x80146260 size:0x1AC */
    nofralloc
    stwu r1, -0x20(r1)
    mflr r0
    lis r4, lbl_8048EE48@ha
    lfs f1, lbl_806D7B50(r2)
    stw r0, 0x24(r1)
    addi r4, r4, lbl_8048EE48@l
    lfs f0, lbl_806D7B54(r2)
    lis r6, lbl_80361ED0@ha
    stw r31, 0x1c(r1)
    mr r31, r3
    lis r3, lbl_8048EB44@ha
    stw r30, 0x18(r1)
    addi r0, r3, lbl_8048EB44@l
    mr r5, r31
    lis r3, lbl_8048EF98@ha
    stw r29, 0x14(r1)
    mr r7, r5
    li r5, 0x0
    addi r30, r6, lbl_80361ED0@l
    stw r0, 0x14(r31)
    addi r0, r3, lbl_8048EF98@l
    li r3, 0x8cd
    stw r5, 0x0(r7)
    stb r5, 0x4(r7)
    stfs f1, 0x8(r7)
    stfs f1, 0xc(r7)
    stfs f0, 0x10(r7)
    stw r4, 0x14(r7)
    stw r5, 0x18(r7)
    stw r0, 0x14(r31)
    bl PreloadResource
    li r3, 0x70
    bl Alloc
    mr. r29, r3
    beq fn_80146260_L_80146304
    addi r7, r30, 0x3fc
    li r4, 0x8cd
    li r5, 0x0
    li r6, 0x0
    li r8, 0x1
    bl fn_8013B9A0
    fn_80146260_L_80146304:
    lwz r3, 0x18(r31)
    cmplwi r3, 0x0
    beq fn_80146260_L_8014631C
    mr r4, r29
    bl fn_8013B7A8
    b fn_80146260_L_80146320
    fn_80146260_L_8014631C:
    stw r29, 0x18(r31)
    fn_80146260_L_80146320:
    li r3, 0x70
    bl Alloc
    mr. r29, r3
    beq fn_80146260_L_80146348
    addi r7, r30, 0x4ac
    li r4, 0x8cd
    li r5, 0x0
    li r6, 0x0
    li r8, 0x1
    bl fn_8013B9A0
    fn_80146260_L_80146348:
    lwz r3, 0x18(r31)
    cmplwi r3, 0x0
    beq fn_80146260_L_80146360
    mr r4, r29
    bl fn_8013B7A8
    b fn_80146260_L_80146364
    fn_80146260_L_80146360:
    stw r29, 0x18(r31)
    fn_80146260_L_80146364:
    li r3, 0x70
    bl Alloc
    mr. r29, r3
    beq fn_80146260_L_8014638C
    addi r7, r30, 0x588
    li r4, 0x8cd
    li r5, 0x0
    li r6, 0x0
    li r8, 0x0
    bl fn_8013B9A0
    fn_80146260_L_8014638C:
    lwz r3, 0x18(r31)
    cmplwi r3, 0x0
    beq fn_80146260_L_801463A4
    mr r4, r29
    bl fn_8013B7A8
    b fn_80146260_L_801463A8
    fn_80146260_L_801463A4:
    stw r29, 0x18(r31)
    fn_80146260_L_801463A8:
    li r3, 0x70
    bl Alloc
    mr. r29, r3
    beq fn_80146260_L_801463D0
    addi r7, r30, 0x638
    li r4, 0x8cd
    li r5, 0x0
    li r6, 0x0
    li r8, 0x0
    bl fn_8013B9A0
    fn_80146260_L_801463D0:
    lwz r3, 0x18(r31)
    cmplwi r3, 0x0
    beq fn_80146260_L_801463E8
    mr r4, r29
    bl fn_8013B7A8
    b fn_80146260_L_801463EC
    fn_80146260_L_801463E8:
    stw r29, 0x18(r31)
    fn_80146260_L_801463EC:
    lwz r0, 0x24(r1)
    mr r3, r31
    lwz r31, 0x1c(r1)
    lwz r30, 0x18(r1)
    lwz r29, 0x14(r1)
    mtlr r0
    addi r1, r1, 0x20
    blr
}

