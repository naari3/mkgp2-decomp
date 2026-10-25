/*
 * 0x8014CE74..0x8014D540: small helpers of the result-screen 3D parts:
 * a factory, two- and three-model holders (update, colour and release) and
 * two thin virtual forwarders. The holder ctors index this area's pooled
 * .rodata and stay asm.
 */
#pragma cplusplus on

void *operator new(unsigned long);
void operator delete(void *);

struct VObj {
    virtual ~VObj();
};

struct Part3D;

extern "C" {
extern void fn_8013D4B0(Part3D *p, float t);
extern void fn_8013DAC8(Part3D *p, int a);
extern void fn_8013D50C(Part3D *p, float r, float g, float b, float a);
extern void HSD_StateInvalidate(int n);
extern void Frame_PostDrawOverlay(void);
extern void Frame_UpdatePerFrameState(void);
}

struct Scene3DObj {
    char pad[0x74];
    Scene3DObj();
};

struct PairHolder {
    int arg;
    Part3D *parts[2];
    ~PairHolder();
};

struct TripleHolder {
    int arg;
    Part3D *parts[3];
    ~TripleHolder();
};

struct Runner {
    virtual void m08();
    virtual void m0C();
    virtual void m10();
    virtual void m14();
    virtual void m18();
};

struct RunnerOwner {
    int m0;
    int m4;
    Runner *runner;
};

struct ResultScene {
    char pad[0x50];
    ResultScene();
};

extern "C" {
extern void Alloc();
extern void fn_8013D59C();
extern void fn_8013D608();
extern void fn_8013D634();
extern void fn_8013D660();
extern void fn_8013D738();
extern void fn_8013D800();
extern unsigned int lbl_806D7E2C;
extern unsigned int lbl_806D7E30;
extern unsigned int lbl_806D7EF4;
extern unsigned int lbl_80362D90[];
extern void MemoryManager_TimedFree();
extern void ItemRes_LookupByKey_Thunk();
extern unsigned int lbl_806D7EE4;
asm void fn_8014D038(void);
asm void fn_8014D344(void);

#pragma section R ".extab_user"
__declspec(section ".extab_user") static const struct { unsigned int f0; unsigned int f1; unsigned int f2; unsigned int f3; unsigned int f4; unsigned int f5; unsigned int f6; void *f7; unsigned int f8; void *f9; } extab_fn_8014D038 = { 0x21CA0000, 0x0000008C, 0x00000018, 0x000000AC, 0x00000020, 0x00000000, 0x8A80001D, (void *)&MemoryManager_TimedFree, 0x8A80001D, (void *)&MemoryManager_TimedFree };

__declspec(section ".extab_user") static const struct { unsigned int f0; unsigned int f1; unsigned int f2; unsigned int f3; unsigned int f4; void *f5; } extab_fn_8014D344 = { 0x390A0000, 0x0000007C, 0x00040010, 0x00000000, 0x8A800019, (void *)&MemoryManager_TimedFree };

#pragma section R ".extabindex_user"
__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_fn_8014D038 = {
    (void *)&fn_8014D038, 0x000001A8, (void *)&extab_fn_8014D038
};

__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_fn_8014D344 = {
    (void *)&fn_8014D344, 0x00000174, (void *)&extab_fn_8014D344
};

}


extern "C" void fn_8014CE74(VObj *p) {
    delete p;
}

extern "C" Scene3DObj *fn_8014CEAC(void) {
    return new Scene3DObj();
}

extern "C" void fn_8014CEE8(PairHolder *h, float t) {
    int i;

    for (i = 0; i < 2; i++) {
        fn_8013D4B0(h->parts[i], t);
    }
}

extern "C" void fn_8014CF44(PairHolder *h) {
    int i;

    for (i = 0; i < 2; i++) {
        fn_8013DAC8(h->parts[i], h->arg);
    }
}

extern "C" void fn_8014CFA0(void) {
}

PairHolder::~PairHolder() {
    int i;

    for (i = 0; i < 2; i++) {
        delete (VObj *)parts[i];
    }
}

extern "C" asm void fn_8014D038(void) { /* 0x8014D038 size:0x1A8 */
    nofralloc
    stwu r1, -0x90(r1)
    mflr r0
    stw r0, 0x94(r1)
    stfd f31, 0x80(r1)
    psq_st f31, 0x88(r1), 0, 0
    stfd f30, 0x70(r1)
    psq_st f30, 0x78(r1), 0, 0
    stfd f29, 0x60(r1)
    psq_st f29, 0x68(r1), 0, 0
    stfd f28, 0x50(r1)
    psq_st f28, 0x58(r1), 0, 0
    stfd f27, 0x40(r1)
    psq_st f27, 0x48(r1), 0, 0
    stfd f26, 0x30(r1)
    psq_st f26, 0x38(r1), 0, 0
    stfd f25, 0x20(r1)
    psq_st f25, 0x28(r1), 0, 0
    stw r31, 0x1c(r1)
    stw r30, 0x18(r1)
    stw r29, 0x14(r1)
    stw r28, 0x10(r1)
    mr r28, r3
    fmr f25, f1
    lis r3, lbl_80362D90@ha
    fmr f26, f2
    fmr f27, f3
    stw r4, 0x0(r28)
    addi r31, r3, lbl_80362D90@l
    li r3, 0x20
    bl Alloc
    mr. r29, r3
    beq fn_8014D038_L_8014D0C4
    addi r4, r31, 0xf74
    li r5, 0x1
    bl fn_8013D800
    fn_8014D038_L_8014D0C4:
    stw r29, 0x4(r28)
    li r3, 0x20
    bl Alloc
    mr. r29, r3
    beq fn_8014D038_L_8014D0E4
    addi r4, r31, 0xf88
    li r5, 0x1
    bl fn_8013D800
    fn_8014D038_L_8014D0E4:
    addi r3, r31, 0xef4
    stw r29, 0x8(r28)
    lfs f28, lbl_806D7EF4(r2)
    mr r30, r28
    lfs f29, 0xef4(r31)
    addi r31, r31, 0xed0
    lfs f30, 0x4(r3)
    li r29, 0x0
    lfs f31, 0x8(r3)
    fn_8014D038_L_8014D108:
    lwz r3, 0x4(r30)
    lfs f1, lbl_806D7E30(r2)
    lfs f2, lbl_806D7E2C(r2)
    bl fn_8013D738
    fmr f1, f25
    lwz r3, 0x4(r30)
    fmr f2, f26
    bl fn_8013D660
    lfs f1, 0x0(r31)
    lfs f2, 0x4(r31)
    lfs f0, 0x8(r31)
    fmuls f1, f1, f27
    fmuls f2, f2, f27
    lwz r3, 0x4(r30)
    fmuls f3, f0, f27
    bl fn_8013D634
    fmr f1, f27
    lwz r3, 0x4(r30)
    fmr f2, f27
    fmr f3, f27
    bl fn_8013D608
    fmuls f1, f28, f29
    lwz r3, 0x4(r30)
    fmuls f2, f28, f30
    fmuls f3, f28, f31
    bl fn_8013D59C
    addi r29, r29, 0x1
    addi r30, r30, 0x4
    cmpwi r29, 0x2
    addi r31, r31, 0xc
    blt fn_8014D038_L_8014D108
    mr r3, r28
    psq_l f31, 0x88(r1), 0, 0
    lfd f31, 0x80(r1)
    psq_l f30, 0x78(r1), 0, 0
    lfd f30, 0x70(r1)
    psq_l f29, 0x68(r1), 0, 0
    lfd f29, 0x60(r1)
    psq_l f28, 0x58(r1), 0, 0
    lfd f28, 0x50(r1)
    psq_l f27, 0x48(r1), 0, 0
    lfd f27, 0x40(r1)
    psq_l f26, 0x38(r1), 0, 0
    lfd f26, 0x30(r1)
    psq_l f25, 0x28(r1), 0, 0
    lfd f25, 0x20(r1)
    lwz r31, 0x1c(r1)
    lwz r30, 0x18(r1)
    lwz r29, 0x14(r1)
    lwz r0, 0x94(r1)
    lwz r28, 0x10(r1)
    mtlr r0
    addi r1, r1, 0x90
    blr
}

extern "C" void fn_8014D1E0(TripleHolder *h, float a) {
    int i;

    for (i = 0; i < 3; i++) {
        fn_8013D50C(h->parts[i], 2.0f, 2.0f, 2.0f, a);
    }
}

extern "C" void fn_8014D250(TripleHolder *h) {
    int i;

    for (i = 0; i < 3; i++) {
        fn_8013DAC8(h->parts[i], h->arg);
    }
}

extern "C" void fn_8014D2AC(void) {
}

TripleHolder::~TripleHolder() {
    int i;

    for (i = 0; i < 3; i++) {
        delete (VObj *)parts[i];
    }
}

extern "C" asm void fn_8014D344(void) { /* 0x8014D344 size:0x174 */
    nofralloc
    stwu r1, -0x70(r1)
    mflr r0
    stw r0, 0x74(r1)
    stfd f31, 0x60(r1)
    psq_st f31, 0x68(r1), 0, 0
    stfd f30, 0x50(r1)
    psq_st f30, 0x58(r1), 0, 0
    stfd f29, 0x40(r1)
    psq_st f29, 0x48(r1), 0, 0
    stfd f28, 0x30(r1)
    psq_st f28, 0x38(r1), 0, 0
    stmw r25, 0x14(r1)
    mr r26, r3
    lis r3, lbl_80362D90@ha
    addi r3, r3, lbl_80362D90@l
    fmr f28, f1
    fmr f29, f2
    stw r4, 0x0(r26)
    fmr f30, f3
    lfs f31, lbl_806D7EF4(r2)
    mr r28, r26
    addi r31, r3, 0xeb8
    addi r30, r3, 0xe70
    addi r29, r3, 0xe94
    li r27, 0x0
    fn_8014D344_L_8014D3A8:
    li r3, 0x20
    bl Alloc
    mr. r25, r3
    beq fn_8014D344_L_8014D3D0
    li r3, 0x32
    bl ItemRes_LookupByKey_Thunk
    mr r4, r3
    mr r3, r25
    li r5, 0x1
    bl fn_8013D800
    fn_8014D344_L_8014D3D0:
    stw r25, 0x4(r28)
    lfs f1, lbl_806D7E30(r2)
    lwz r3, 0x4(r28)
    lfs f2, lbl_806D7E2C(r2)
    bl fn_8013D738
    fmr f1, f28
    lwz r3, 0x4(r28)
    fmr f2, f29
    bl fn_8013D660
    lfs f1, 0x0(r30)
    lfs f2, 0x4(r30)
    lfs f0, 0x8(r30)
    fmuls f1, f1, f30
    fmuls f2, f2, f30
    lwz r3, 0x4(r28)
    fmuls f3, f0, f30
    bl fn_8013D634
    lfs f0, 0x0(r31)
    lwz r3, 0x4(r28)
    fmuls f1, f0, f30
    fmr f2, f1
    fmr f3, f1
    bl fn_8013D608
    lfs f1, 0x0(r29)
    lfs f2, 0x4(r29)
    lfs f0, 0x8(r29)
    fmuls f1, f31, f1
    fmuls f2, f31, f2
    lwz r3, 0x4(r28)
    fmuls f3, f31, f0
    bl fn_8013D59C
    lfs f1, lbl_806D7EE4(r2)
    lwz r3, 0x4(r28)
    fmr f2, f1
    lfs f4, lbl_806D7E30(r2)
    fmr f3, f1
    bl fn_8013D50C
    addi r27, r27, 0x1
    addi r30, r30, 0xc
    cmpwi r27, 0x3
    addi r29, r29, 0xc
    addi r28, r28, 0x4
    addi r31, r31, 0x4
    blt fn_8014D344_L_8014D3A8
    mr r3, r26
    psq_l f31, 0x68(r1), 0, 0
    lfd f31, 0x60(r1)
    psq_l f30, 0x58(r1), 0, 0
    lfd f30, 0x50(r1)
    psq_l f29, 0x48(r1), 0, 0
    lfd f29, 0x40(r1)
    psq_l f28, 0x38(r1), 0, 0
    lfd f28, 0x30(r1)
    lmw r25, 0x14(r1)
    lwz r0, 0x74(r1)
    mtlr r0
    addi r1, r1, 0x70
    blr
}

extern "C" void fn_8014D4B8(RunnerOwner *o) {
    o->runner->m14();
    HSD_StateInvalidate(-1);
}

extern "C" void fn_8014D4F0(RunnerOwner *o) {
    o->runner->m10();
    o->runner->m18();
}
