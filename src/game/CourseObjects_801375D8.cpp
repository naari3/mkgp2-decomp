/*
 * 0x801375D8..0x80139898: course object culling, activation and the per-frame update.
 */
#pragma cplusplus on

struct FreeNode {
    FreeNode *next;
};
struct CourseObj {
    char pad0[4];
    float x, y, z;
    char pad10[8];
    int state;
    float f1C;
    float px, py, pz;
    char pad2C[4];
    float f30;
    float f34;
    char pad38[0xc0 - 0x38];
};

/* TOP-END */

extern "C" {
extern unsigned int lbl_806D1518;
extern unsigned int lbl_806D151C;
extern unsigned int lbl_80677CB8[];
extern int lbl_806D1524;
extern struct FreeNode *lbl_806D1520;
extern void PSMTXMultVec();
extern void PSVECCrossProduct();
extern void Vec3_Normalize();
extern unsigned int lbl_806D73E0;
void MemoryManager_TimedFree(void *p);
extern void Alloc();
extern void HSD_JObjGetDObj();
extern void HSD_JObjGetFlags();
extern void fn_80185FE8();
extern void tan();
extern unsigned int lbl_806D73E4;
extern void Vec3_Magnitude();
extern void Vec3_Subtract();
extern struct CourseObj *lbl_806D1534;
extern int lbl_806D1538;
extern const float lbl_806D73E8;
extern const float lbl_806D73EC;
extern void Archive_GetRootJObj();
extern void GXChannel_Init();
extern void GXChannel_PushTransform();
extern void LinkedNode_GetField10_OrFallback();
extern void Mtx4x4_TransposeTo4x3();
extern void Object_SetColorAlphaOnly();
extern void PSVECAdd();
extern void cos();
extern void dtor_8007D9C4();
extern void sin();
extern unsigned int lbl_806D1528;
extern unsigned int lbl_806D152C;
extern unsigned int lbl_806D1530;
extern unsigned int lbl_806D73F0;
extern unsigned int lbl_806D73F4;
extern unsigned int lbl_806D73F8;
extern unsigned int lbl_806D73FC;
extern unsigned int lbl_806D7400;
unsigned long OSGetTick(void);
void Profiler_RecordFrame(int id, float ms);
extern const float lbl_806D7404;
extern unsigned int lbl_806D7408;
extern void __dt__11ScopedTimerFv();
asm void fn_801375D8(void);
asm void fn_80137718(void);
asm void fn_801379F0(void);
asm void fn_80137C8C(void);
asm void fn_80137E50(void);
void fn_80138578(void);
asm void fn_801385CC(void);
asm void fn_8013879C(void);
asm void fn_80138A50(void);
void CourseObjects_Activate(void);
void fn_80138D48(void);
asm void fn_80138DB8(void);
void fn_80139810(void);

#pragma section R ".extab_user"
__declspec(section ".extab_user") static const unsigned char extab_fn_80137C8C[8] = {
    0x10, 0x0A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

__declspec(section ".extab_user") static const unsigned char extab_fn_80137E50[8] = {
    0x08, 0x0A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};


__declspec(section ".extab_user") static const struct { unsigned int f0; unsigned int f1; unsigned int f2; unsigned int f3; unsigned int f4; void *f5; } extab_fn_801385CC = { 0x40080000, 0x000000A4, 0x00000010, 0x00000000, 0x8A800018, (void *)&MemoryManager_TimedFree };

__declspec(section ".extab_user") static const unsigned char extab_fn_8013879C[8] = {
    0x08, 0x8A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

__declspec(section ".extab_user") static const unsigned char extab_fn_80138A50[8] = {
    0x08, 0x0A, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

__declspec(section ".extab_user") static const struct { unsigned int f0; unsigned int f1; unsigned int f2; unsigned int f3; unsigned int f4; unsigned int f5; unsigned int f6; unsigned int f7; unsigned int f8; unsigned int f9; unsigned int f10; void *f11; unsigned int f12; void *f13; unsigned int f14; void *f15; unsigned int f16; void *f17; } extab_fn_80138DB8 = { 0x408A0000, 0x000004B8, 0x00030028, 0x00000554, 0x00030030, 0x00000614, 0x00030038, 0x000006CC, 0x00CC0040, 0x00000000, 0x8200005C, (void *)&dtor_8007D9C4, 0x82000048, (void *)&dtor_8007D9C4, 0x82000034, (void *)&dtor_8007D9C4, 0x82000020, (void *)&dtor_8007D9C4 };


#pragma section R ".extabindex_user"
__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_fn_80137C8C = {
    (void *)&fn_80137C8C, 0x000001C4, (void *)extab_fn_80137C8C
};

__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_fn_80137E50 = {
    (void *)&fn_80137E50, 0x00000728, (void *)extab_fn_80137E50
};


__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_fn_801385CC = {
    (void *)&fn_801385CC, 0x000001D0, (void *)&extab_fn_801385CC
};

__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_fn_8013879C = {
    (void *)&fn_8013879C, 0x000002B4, (void *)extab_fn_8013879C
};

__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_fn_80138A50 = {
    (void *)&fn_80138A50, 0x00000294, (void *)extab_fn_80138A50
};

__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_fn_80138DB8 = {
    (void *)&fn_80138DB8, 0x00000A58, (void *)&extab_fn_80138DB8
};


}

class ScopedTimer {
public:
    inline ScopedTimer(int slot) {
        m_slot = slot;
        m_startTick = OSGetTick();
    }
    inline ~ScopedTimer() {
        Profiler_RecordFrame(m_slot,
            (float)(((OSGetTick() - m_startTick) * 8) /
                ((*(unsigned int *)0x800000F8 / 4) / 125000)) / lbl_806D7404);
    }

private:
    unsigned int m_startTick;
    volatile int m_slot;
};




extern "C" asm void fn_801375D8(void) { /* 0x801375D8 size:0x140 */
    nofralloc
    lwz r5, lbl_806D1518(r13)
    lis r4, lbl_80677CB8@ha
    lfs f7, 0x4(r3)
    addi r4, r4, lbl_80677CB8@l
    lfs f0, 0x24(r5)
    lfs f3, 0x20(r5)
    fmuls f0, f0, f7
    lfs f8, 0x0(r3)
    lfs f4, 0x28(r5)
    lfs f2, 0x8(r3)
    fmadds f0, f3, f8, f0
    lfs f3, 0x2c(r5)
    lwz r3, lbl_806D151C(r13)
    fmadds f0, f4, f2, f0
    fadds f0, f3, f0
    stfs f0, 0x8(r4)
    fsubs f4, f0, f1
    lfs f3, 0x40(r3)
    fcmpo cr0, f4, f3
    ble fn_801375D8_L_80137630
    li r3, 0x0
    blr
    fn_801375D8_L_80137630:
    fadds f4, f0, f1
    lfs f3, 0x44(r3)
    fcmpo cr0, f4, f3
    bge fn_801375D8_L_80137648
    li r3, 0x0
    blr
    fn_801375D8_L_80137648:
    lfs f3, 0x4(r5)
    lfs f4, 0x0(r5)
    fmuls f3, f3, f7
    lfs f5, 0x8(r5)
    lfs f6, 0xc(r5)
    fmadds f3, f4, f8, f3
    fmadds f3, f5, f2, f3
    fadds f5, f6, f3
    stfs f5, 0x0(r4)
    lfs f3, 0x8(r3)
    lfs f4, 0x0(r3)
    fmuls f3, f0, f3
    fmadds f3, f5, f4, f3
    fcmpo cr0, f3, f1
    ble fn_801375D8_L_8013768C
    li r3, 0x0
    blr
    fn_801375D8_L_8013768C:
    lfs f3, 0x18(r3)
    lfs f4, 0x10(r3)
    fmuls f3, f0, f3
    fmadds f3, f5, f4, f3
    fcmpo cr0, f3, f1
    ble fn_801375D8_L_801376AC
    li r3, 0x0
    blr
    fn_801375D8_L_801376AC:
    lfs f3, 0x14(r5)
    lfs f4, 0x10(r5)
    fmuls f3, f3, f7
    lfs f5, 0x18(r5)
    lfs f6, 0x1c(r5)
    fmadds f3, f4, f8, f3
    fmadds f2, f5, f2, f3
    fadds f4, f6, f2
    stfs f4, 0x4(r4)
    lfs f2, 0x28(r3)
    lfs f3, 0x24(r3)
    fmuls f2, f0, f2
    fmadds f2, f4, f3, f2
    fcmpo cr0, f2, f1
    ble fn_801375D8_L_801376F0
    li r3, 0x0
    blr
    fn_801375D8_L_801376F0:
    lfs f2, 0x38(r3)
    lfs f3, 0x34(r3)
    fmuls f0, f0, f2
    fmadds f0, f4, f3, f0
    fcmpo cr0, f0, f1
    ble fn_801375D8_L_80137710
    li r3, 0x0
    blr
    fn_801375D8_L_80137710:
    li r3, 0x1
    blr
}

extern "C" asm void fn_80137718(void) { /* 0x80137718 size:0x2D8 */
    nofralloc
    cmplwi r4, 0x0
    bne fn_80137718_L_80137728
    lis r4, lbl_80677CB8@ha
    addi r4, r4, lbl_80677CB8@l
    fn_80137718_L_80137728:
    lwz r5, lbl_806D1518(r13)
    lfs f0, 0x4(r3)
    lfs f2, 0x24(r5)
    lfs f3, 0x20(r5)
    fmuls f0, f2, f0
    lfs f2, 0x0(r3)
    lfs f5, 0x28(r5)
    lfs f4, 0x8(r3)
    fmadds f0, f3, f2, f0
    lfs f2, 0x2c(r5)
    fmadds f0, f5, f4, f0
    fadds f0, f2, f0
    stfs f0, 0x8(r4)
    lfs f3, 0x8(r4)
    lwz r5, lbl_806D151C(r13)
    fsubs f2, f3, f1
    lfs f0, 0x40(r5)
    fcmpo cr0, f2, f0
    ble fn_80137718_L_8013777C
    li r0, 0x0
    b fn_80137718_L_80137898
    fn_80137718_L_8013777C:
    fadds f2, f3, f1
    lfs f0, 0x44(r5)
    fcmpo cr0, f2, f0
    bge fn_80137718_L_80137794
    li r0, 0x0
    b fn_80137718_L_80137898
    fn_80137718_L_80137794:
    lwz r5, lbl_806D1518(r13)
    lfs f0, 0x4(r3)
    lfs f2, 0x4(r5)
    lfs f3, 0x0(r5)
    fmuls f0, f2, f0
    lfs f2, 0x0(r3)
    lfs f5, 0x8(r5)
    lfs f4, 0x8(r3)
    fmadds f0, f3, f2, f0
    lfs f2, 0xc(r5)
    fmadds f0, f5, f4, f0
    fadds f0, f2, f0
    stfs f0, 0x0(r4)
    lwz r5, lbl_806D151C(r13)
    lfs f3, 0x8(r4)
    lfs f0, 0x8(r5)
    lfs f4, 0x0(r4)
    fmuls f0, f3, f0
    lfs f2, 0x0(r5)
    fmadds f0, f4, f2, f0
    fcmpo cr0, f0, f1
    ble fn_80137718_L_801377F4
    li r0, 0x0
    b fn_80137718_L_80137898
    fn_80137718_L_801377F4:
    lfs f0, 0x18(r5)
    lfs f2, 0x10(r5)
    fmuls f0, f3, f0
    fmadds f0, f4, f2, f0
    fcmpo cr0, f0, f1
    ble fn_80137718_L_80137814
    li r0, 0x0
    b fn_80137718_L_80137898
    fn_80137718_L_80137814:
    lwz r5, lbl_806D1518(r13)
    lfs f0, 0x4(r3)
    lfs f2, 0x14(r5)
    lfs f3, 0x10(r5)
    fmuls f0, f2, f0
    lfs f2, 0x0(r3)
    lfs f5, 0x18(r5)
    lfs f4, 0x8(r3)
    fmadds f0, f3, f2, f0
    lfs f2, 0x1c(r5)
    fmadds f0, f5, f4, f0
    fadds f0, f2, f0
    stfs f0, 0x4(r4)
    lwz r3, lbl_806D151C(r13)
    lfs f3, 0x8(r4)
    lfs f0, 0x28(r3)
    lfs f4, 0x4(r4)
    fmuls f0, f3, f0
    lfs f2, 0x24(r3)
    fmadds f0, f4, f2, f0
    fcmpo cr0, f0, f1
    ble fn_80137718_L_80137874
    li r0, 0x0
    b fn_80137718_L_80137898
    fn_80137718_L_80137874:
    lfs f0, 0x38(r3)
    lfs f2, 0x34(r3)
    fmuls f0, f3, f0
    fmadds f0, f4, f2, f0
    fcmpo cr0, f0, f1
    ble fn_80137718_L_80137894
    li r0, 0x0
    b fn_80137718_L_80137898
    fn_80137718_L_80137894:
    li r0, 0x1
    fn_80137718_L_80137898:
    clrlwi. r0, r0, 24
    bne fn_80137718_L_801378A8
    li r3, 0x0
    blr
    fn_80137718_L_801378A8:
    fneg f0, f1
    lwz r3, lbl_806D1524(r13)
    b fn_80137718_L_801379E0
    fn_80137718_L_801378B4:
    lfs f2, 0x8(r4)
    lfs f4, 0x38(r3)
    fadds f3, f2, f1
    fcmpo cr0, f4, f3
    bge fn_80137718_L_801378D0
    li r0, 0x1
    b fn_80137718_L_801379CC
    fn_80137718_L_801378D0:
    lfs f3, 0x4(r4)
    lfs f5, 0x40(r3)
    lfs f4, 0x0(r4)
    fmuls f5, f3, f5
    lfs f6, 0x3c(r3)
    lfs f7, 0x44(r3)
    lfs f8, 0x48(r3)
    fmadds f5, f4, f6, f5
    fmadds f5, f2, f7, f5
    fadds f5, f8, f5
    fcmpo cr0, f5, f0
    ble fn_80137718_L_80137908
    li r0, 0x1
    b fn_80137718_L_801379CC
    fn_80137718_L_80137908:
    lfs f5, 0x50(r3)
    lfs f6, 0x4c(r3)
    fmuls f5, f3, f5
    lfs f7, 0x54(r3)
    lfs f8, 0x58(r3)
    fmadds f5, f4, f6, f5
    fmadds f5, f2, f7, f5
    fadds f5, f8, f5
    fcmpo cr0, f5, f0
    ble fn_80137718_L_80137938
    li r0, 0x1
    b fn_80137718_L_801379CC
    fn_80137718_L_80137938:
    lfs f5, 0x60(r3)
    lfs f6, 0x5c(r3)
    fmuls f5, f3, f5
    lfs f7, 0x64(r3)
    lfs f8, 0x68(r3)
    fmadds f5, f4, f6, f5
    fmadds f5, f2, f7, f5
    fadds f5, f8, f5
    fcmpo cr0, f5, f0
    ble fn_80137718_L_80137968
    li r0, 0x1
    b fn_80137718_L_801379CC
    fn_80137718_L_80137968:
    lfs f5, 0x70(r3)
    lfs f6, 0x6c(r3)
    fmuls f5, f3, f5
    lfs f7, 0x74(r3)
    lfs f8, 0x78(r3)
    fmadds f5, f4, f6, f5
    fmadds f5, f2, f7, f5
    fadds f5, f8, f5
    fcmpo cr0, f5, f0
    ble fn_80137718_L_80137998
    li r0, 0x1
    b fn_80137718_L_801379CC
    fn_80137718_L_80137998:
    lfs f5, 0x80(r3)
    lfs f6, 0x7c(r3)
    fmuls f3, f3, f5
    lfs f5, 0x84(r3)
    lfs f7, 0x88(r3)
    fmadds f3, f4, f6, f3
    fmadds f2, f2, f5, f3
    fadds f2, f7, f2
    fcmpo cr0, f2, f0
    ble fn_80137718_L_801379C8
    li r0, 0x1
    b fn_80137718_L_801379CC
    fn_80137718_L_801379C8:
    li r0, 0x0
    fn_80137718_L_801379CC:
    clrlwi. r0, r0, 24
    bne fn_80137718_L_801379DC
    li r3, 0x0
    blr
    fn_80137718_L_801379DC:
    lwz r3, 0x4(r3)
    fn_80137718_L_801379E0:
    cmplwi r3, 0x0
    bne fn_80137718_L_801378B4
    li r3, 0x1
    blr
}

extern "C" asm void fn_801379F0(void) { /* 0x801379F0 size:0x29C */
    nofralloc
    lwz r5, lbl_806D1518(r13)
    lis r4, lbl_80677CB8@ha
    lfs f7, 0x4(r3)
    addi r4, r4, lbl_80677CB8@l
    lfs f0, 0x24(r5)
    lfs f3, 0x20(r5)
    fmuls f0, f0, f7
    lfs f8, 0x0(r3)
    lfs f4, 0x28(r5)
    lfs f2, 0x8(r3)
    fmadds f0, f3, f8, f0
    lfs f3, 0x2c(r5)
    lwz r3, lbl_806D151C(r13)
    fmadds f0, f4, f2, f0
    fadds f0, f3, f0
    stfs f0, 0x8(r4)
    fsubs f4, f0, f1
    lfs f3, 0x40(r3)
    fcmpo cr0, f4, f3
    ble fn_801379F0_L_80137A48
    li r0, 0x0
    b fn_801379F0_L_80137B2C
    fn_801379F0_L_80137A48:
    fadds f4, f0, f1
    lfs f3, 0x44(r3)
    fcmpo cr0, f4, f3
    bge fn_801379F0_L_80137A60
    li r0, 0x0
    b fn_801379F0_L_80137B2C
    fn_801379F0_L_80137A60:
    lfs f3, 0x4(r5)
    lfs f4, 0x0(r5)
    fmuls f3, f3, f7
    lfs f5, 0x8(r5)
    lfs f6, 0xc(r5)
    fmadds f3, f4, f8, f3
    fmadds f3, f5, f2, f3
    fadds f5, f6, f3
    stfs f5, 0x0(r4)
    lfs f3, 0x8(r3)
    lfs f4, 0x0(r3)
    fmuls f3, f0, f3
    fmadds f3, f5, f4, f3
    fcmpo cr0, f3, f1
    ble fn_801379F0_L_80137AA4
    li r0, 0x0
    b fn_801379F0_L_80137B2C
    fn_801379F0_L_80137AA4:
    lfs f3, 0x18(r3)
    lfs f4, 0x10(r3)
    fmuls f3, f0, f3
    fmadds f3, f5, f4, f3
    fcmpo cr0, f3, f1
    ble fn_801379F0_L_80137AC4
    li r0, 0x0
    b fn_801379F0_L_80137B2C
    fn_801379F0_L_80137AC4:
    lfs f3, 0x14(r5)
    lfs f4, 0x10(r5)
    fmuls f3, f3, f7
    lfs f5, 0x18(r5)
    lfs f6, 0x1c(r5)
    fmadds f3, f4, f8, f3
    fmadds f2, f5, f2, f3
    fadds f4, f6, f2
    stfs f4, 0x4(r4)
    lfs f2, 0x28(r3)
    lfs f3, 0x24(r3)
    fmuls f2, f0, f2
    fmadds f2, f4, f3, f2
    fcmpo cr0, f2, f1
    ble fn_801379F0_L_80137B08
    li r0, 0x0
    b fn_801379F0_L_80137B2C
    fn_801379F0_L_80137B08:
    lfs f2, 0x38(r3)
    lfs f3, 0x34(r3)
    fmuls f0, f0, f2
    fmadds f0, f4, f3, f0
    fcmpo cr0, f0, f1
    ble fn_801379F0_L_80137B28
    li r0, 0x0
    b fn_801379F0_L_80137B2C
    fn_801379F0_L_80137B28:
    li r0, 0x1
    fn_801379F0_L_80137B2C:
    clrlwi. r0, r0, 24
    bne fn_801379F0_L_80137B3C
    li r3, 0x0
    blr
    fn_801379F0_L_80137B3C:
    lfs f4, 0x8(r4)
    lis r3, lbl_80677CB8@ha
    addi r3, r3, lbl_80677CB8@l
    fneg f3, f1
    fadds f0, f4, f1
    lwz r4, lbl_806D1524(r13)
    lfs f1, 0x4(r3)
    lfs f2, 0x0(r3)
    b fn_801379F0_L_80137C7C
    fn_801379F0_L_80137B60:
    lfs f5, 0x38(r4)
    fcmpo cr0, f5, f0
    bge fn_801379F0_L_80137B74
    li r0, 0x1
    b fn_801379F0_L_80137C68
    fn_801379F0_L_80137B74:
    lfs f5, 0x40(r4)
    lfs f6, 0x3c(r4)
    fmuls f5, f1, f5
    lfs f7, 0x44(r4)
    lfs f8, 0x48(r4)
    fmadds f5, f2, f6, f5
    fmadds f5, f4, f7, f5
    fadds f5, f8, f5
    fcmpo cr0, f5, f3
    ble fn_801379F0_L_80137BA4
    li r0, 0x1
    b fn_801379F0_L_80137C68
    fn_801379F0_L_80137BA4:
    lfs f5, 0x50(r4)
    lfs f6, 0x4c(r4)
    fmuls f5, f1, f5
    lfs f7, 0x54(r4)
    lfs f8, 0x58(r4)
    fmadds f5, f2, f6, f5
    fmadds f5, f4, f7, f5
    fadds f5, f8, f5
    fcmpo cr0, f5, f3
    ble fn_801379F0_L_80137BD4
    li r0, 0x1
    b fn_801379F0_L_80137C68
    fn_801379F0_L_80137BD4:
    lfs f5, 0x60(r4)
    lfs f6, 0x5c(r4)
    fmuls f5, f1, f5
    lfs f7, 0x64(r4)
    lfs f8, 0x68(r4)
    fmadds f5, f2, f6, f5
    fmadds f5, f4, f7, f5
    fadds f5, f8, f5
    fcmpo cr0, f5, f3
    ble fn_801379F0_L_80137C04
    li r0, 0x1
    b fn_801379F0_L_80137C68
    fn_801379F0_L_80137C04:
    lfs f5, 0x70(r4)
    lfs f6, 0x6c(r4)
    fmuls f5, f1, f5
    lfs f7, 0x74(r4)
    lfs f8, 0x78(r4)
    fmadds f5, f2, f6, f5
    fmadds f5, f4, f7, f5
    fadds f5, f8, f5
    fcmpo cr0, f5, f3
    ble fn_801379F0_L_80137C34
    li r0, 0x1
    b fn_801379F0_L_80137C68
    fn_801379F0_L_80137C34:
    lfs f5, 0x80(r4)
    lfs f6, 0x7c(r4)
    fmuls f5, f1, f5
    lfs f7, 0x84(r4)
    lfs f8, 0x88(r4)
    fmadds f5, f2, f6, f5
    fmadds f5, f4, f7, f5
    fadds f5, f8, f5
    fcmpo cr0, f5, f3
    ble fn_801379F0_L_80137C64
    li r0, 0x1
    b fn_801379F0_L_80137C68
    fn_801379F0_L_80137C64:
    li r0, 0x0
    fn_801379F0_L_80137C68:
    clrlwi. r0, r0, 24
    bne fn_801379F0_L_80137C78
    li r3, 0x0
    blr
    fn_801379F0_L_80137C78:
    lwz r4, 0x4(r4)
    fn_801379F0_L_80137C7C:
    cmplwi r4, 0x0
    bne fn_801379F0_L_80137B60
    li r3, 0x1
    blr
}

extern "C" asm void fn_80137C8C(void) { /* 0x80137C8C size:0x1C4 */
    nofralloc
    stwu r1, -0x10(r1)
    mflr r0
    stw r0, 0x14(r1)
    li r0, 0x0
    stw r31, 0xc(r1)
    stw r30, 0x8(r1)
    li r30, 0x0
    stw r3, lbl_806D1518(r13)
    lwz r31, lbl_806D1520(r13)
    stw r4, lbl_806D151C(r13)
    stw r0, lbl_806D1524(r13)
    b fn_80137C8C_L_80137E30
    fn_80137C8C_L_80137CBC:
    lwz r3, lbl_806D1518(r13)
    lwz r4, lbl_806D151C(r13)
    lfs f0, 0x24(r3)
    lfs f2, 0x90(r31)
    lfs f1, 0x20(r3)
    fmuls f0, f0, f2
    lfs f3, 0x8c(r31)
    lfs f6, 0x28(r3)
    lfs f4, 0x94(r31)
    fmadds f1, f1, f3, f0
    lfs f7, 0x2c(r3)
    lfs f0, 0x98(r31)
    lfs f5, 0x40(r4)
    fmadds f1, f6, f4, f1
    fadds f1, f7, f1
    fsubs f6, f1, f0
    fcmpo cr0, f6, f5
    ble fn_80137C8C_L_80137D0C
    li r0, 0x0
    b fn_80137C8C_L_80137DE8
    fn_80137C8C_L_80137D0C:
    fadds f6, f1, f0
    lfs f5, 0x44(r4)
    fcmpo cr0, f6, f5
    bge fn_80137C8C_L_80137D24
    li r0, 0x0
    b fn_80137C8C_L_80137DE8
    fn_80137C8C_L_80137D24:
    lfs f6, 0x4(r3)
    lfs f5, 0x8(r4)
    fmuls f6, f6, f2
    lfs f7, 0x0(r3)
    lfs f8, 0x8(r3)
    fmuls f5, f1, f5
    lfs f9, 0xc(r3)
    fmadds f7, f7, f3, f6
    lfs f6, 0x0(r4)
    fmadds f7, f8, f4, f7
    fadds f7, f9, f7
    fmadds f5, f7, f6, f5
    fcmpo cr0, f5, f0
    ble fn_80137C8C_L_80137D64
    li r0, 0x0
    b fn_80137C8C_L_80137DE8
    fn_80137C8C_L_80137D64:
    lfs f5, 0x18(r4)
    lfs f6, 0x10(r4)
    fmuls f5, f1, f5
    fmadds f5, f7, f6, f5
    fcmpo cr0, f5, f0
    ble fn_80137C8C_L_80137D84
    li r0, 0x0
    b fn_80137C8C_L_80137DE8
    fn_80137C8C_L_80137D84:
    lfs f6, 0x14(r3)
    lfs f5, 0x28(r4)
    fmuls f6, f6, f2
    lfs f7, 0x10(r3)
    lfs f8, 0x18(r3)
    fmuls f2, f1, f5
    lfs f9, 0x1c(r3)
    fmadds f5, f7, f3, f6
    lfs f3, 0x24(r4)
    fmadds f4, f8, f4, f5
    fadds f4, f9, f4
    fmadds f2, f4, f3, f2
    fcmpo cr0, f2, f0
    ble fn_80137C8C_L_80137DC4
    li r0, 0x0
    b fn_80137C8C_L_80137DE8
    fn_80137C8C_L_80137DC4:
    lfs f2, 0x38(r4)
    lfs f3, 0x34(r4)
    fmuls f1, f1, f2
    fmadds f1, f4, f3, f1
    fcmpo cr0, f1, f0
    ble fn_80137C8C_L_80137DE4
    li r0, 0x0
    b fn_80137C8C_L_80137DE8
    fn_80137C8C_L_80137DE4:
    li r0, 0x1
    fn_80137C8C_L_80137DE8:
    clrlwi. r0, r0, 24
    beq fn_80137C8C_L_80137E2C
    addi r3, r31, 0x8
    bl fn_80137E50
    clrlwi. r0, r3, 24
    beq fn_80137C8C_L_80137E2C
    cmplwi r30, 0x0
    bne fn_80137C8C_L_80137E1C
    stw r31, lbl_806D1524(r13)
    li r0, 0x0
    mr r30, r31
    stw r0, 0x4(r31)
    b fn_80137C8C_L_80137E2C
    fn_80137C8C_L_80137E1C:
    stw r31, 0x4(r30)
    li r0, 0x0
    mr r30, r31
    stw r0, 0x4(r31)
    fn_80137C8C_L_80137E2C:
    lwz r31, 0x0(r31)
    fn_80137C8C_L_80137E30:
    cmplwi r31, 0x0
    bne fn_80137C8C_L_80137CBC
    lwz r0, 0x14(r1)
    lwz r31, 0xc(r1)
    lwz r30, 0x8(r1)
    mtlr r0
    addi r1, r1, 0x10
    blr
}

extern "C" asm void fn_80137E50(void) { /* 0x80137E50 size:0x728 */
    nofralloc
    stwu r1, -0x1b0(r1)
    mflr r0
    stw r0, 0x1b4(r1)
    stw r31, 0x1ac(r1)
    mr r31, r3
    lwz r0, lbl_806D1518(r13)
    cmplwi r0, 0x0
    beq fn_80137E50_L_80137E78
    cmplwi r31, 0x0
    bne fn_80137E50_L_80137E80
    fn_80137E50_L_80137E78:
    li r3, 0x0
    b fn_80137E50_L_80138564
    fn_80137E50_L_80137E80:
    mr r3, r0
    mr r4, r31
    addi r5, r1, 0x194
    bl PSMTXMultVec
    lwz r3, lbl_806D1518(r13)
    addi r4, r31, 0xc
    addi r5, r1, 0x188
    bl PSMTXMultVec
    lwz r3, lbl_806D1518(r13)
    addi r4, r31, 0x18
    addi r5, r1, 0x17c
    bl PSMTXMultVec
    lwz r3, lbl_806D1518(r13)
    addi r4, r31, 0x24
    addi r5, r1, 0x170
    bl PSMTXMultVec
    lfs f0, 0x19c(r1)
    stfs f0, 0x30(r31)
    lfs f1, 0x190(r1)
    lfs f0, 0x30(r31)
    fcmpo cr0, f1, f0
    ble fn_80137E50_L_80137EDC
    stfs f1, 0x30(r31)
    fn_80137E50_L_80137EDC:
    lfs f1, 0x184(r1)
    lfs f0, 0x30(r31)
    fcmpo cr0, f1, f0
    ble fn_80137E50_L_80137EF0
    stfs f1, 0x30(r31)
    fn_80137E50_L_80137EF0:
    lfs f1, 0x178(r1)
    lfs f0, 0x30(r31)
    fcmpo cr0, f1, f0
    ble fn_80137E50_L_80137F04
    stfs f1, 0x30(r31)
    fn_80137E50_L_80137F04:
    lfs f1, 0x188(r1)
    addi r3, r1, 0x14c
    lfs f2, 0x194(r1)
    addi r4, r1, 0x158
    lfs f0, 0x17c(r1)
    addi r5, r1, 0x164
    fsubs f5, f1, f2
    lfs f1, 0x18c(r1)
    lfs f3, 0x198(r1)
    fsubs f2, f0, f2
    lfs f0, 0x180(r1)
    fsubs f4, f1, f3
    fsubs f1, f0, f3
    lfs f3, 0x190(r1)
    lfs f6, 0x19c(r1)
    lfs f0, 0x184(r1)
    fsubs f3, f3, f6
    stfs f5, 0x14c(r1)
    fsubs f0, f0, f6
    stfs f4, 0x150(r1)
    stfs f3, 0x154(r1)
    stfs f2, 0x158(r1)
    stfs f1, 0x15c(r1)
    stfs f0, 0x160(r1)
    bl PSVECCrossProduct
    addi r3, r1, 0x164
    mr r4, r3
    bl Vec3_Normalize
    lfs f0, 0x164(r1)
    lfs f6, lbl_806D73E0(r2)
    stfs f0, 0x34(r31)
    lfs f0, 0x168(r1)
    stfs f0, 0x38(r31)
    lfs f0, 0x16c(r1)
    stfs f0, 0x3c(r31)
    lfs f1, 0x168(r1)
    lfs f0, 0x198(r1)
    lfs f2, 0x164(r1)
    fmuls f0, f1, f0
    lfs f1, 0x194(r1)
    lfs f4, 0x16c(r1)
    lfs f3, 0x19c(r1)
    fmadds f0, f2, f1, f0
    fnmadds f0, f4, f3, f0
    stfs f0, 0x40(r31)
    lfs f0, 0x40(r31)
    fcmpo cr0, f0, f6
    ble fn_80137E50_L_8013823C
    lfs f2, 0x194(r1)
    addi r3, r1, 0x128
    lfs f1, 0x198(r1)
    addi r4, r1, 0x134
    lfs f0, 0x19c(r1)
    fsubs f5, f2, f6
    lfs f2, 0x188(r1)
    fsubs f4, f1, f6
    lfs f1, 0x18c(r1)
    fsubs f3, f0, f6
    lfs f0, 0x190(r1)
    fsubs f2, f2, f6
    stfs f5, 0x128(r1)
    fsubs f1, f1, f6
    addi r5, r1, 0x140
    fsubs f0, f0, f6
    stfs f4, 0x12c(r1)
    stfs f3, 0x130(r1)
    stfs f2, 0x134(r1)
    stfs f1, 0x138(r1)
    stfs f0, 0x13c(r1)
    bl PSVECCrossProduct
    addi r3, r1, 0x140
    mr r4, r3
    bl Vec3_Normalize
    lfs f0, 0x140(r1)
    addi r3, r1, 0x104
    lfs f6, lbl_806D73E0(r2)
    addi r4, r1, 0x110
    stfs f0, 0x44(r31)
    addi r5, r1, 0x11c
    lfs f0, 0x144(r1)
    stfs f0, 0x48(r31)
    lfs f0, 0x148(r1)
    stfs f0, 0x4c(r31)
    lfs f0, 0x144(r1)
    lfs f1, 0x140(r1)
    fmuls f0, f0, f6
    lfs f2, 0x148(r1)
    fmadds f0, f1, f6, f0
    fnmadds f0, f2, f6, f0
    stfs f0, 0x50(r31)
    lfs f2, 0x188(r1)
    lfs f1, 0x18c(r1)
    lfs f0, 0x190(r1)
    fsubs f5, f2, f6
    lfs f2, 0x17c(r1)
    fsubs f4, f1, f6
    lfs f1, 0x180(r1)
    fsubs f3, f0, f6
    lfs f0, 0x184(r1)
    fsubs f2, f2, f6
    stfs f5, 0x104(r1)
    fsubs f1, f1, f6
    fsubs f0, f0, f6
    stfs f4, 0x108(r1)
    stfs f3, 0x10c(r1)
    stfs f2, 0x110(r1)
    stfs f1, 0x114(r1)
    stfs f0, 0x118(r1)
    bl PSVECCrossProduct
    addi r3, r1, 0x11c
    mr r4, r3
    bl Vec3_Normalize
    lfs f0, 0x11c(r1)
    addi r3, r1, 0xe0
    lfs f6, lbl_806D73E0(r2)
    addi r4, r1, 0xec
    stfs f0, 0x54(r31)
    addi r5, r1, 0xf8
    lfs f0, 0x120(r1)
    stfs f0, 0x58(r31)
    lfs f0, 0x124(r1)
    stfs f0, 0x5c(r31)
    lfs f0, 0x120(r1)
    lfs f1, 0x11c(r1)
    fmuls f0, f0, f6
    lfs f2, 0x124(r1)
    fmadds f0, f1, f6, f0
    fnmadds f0, f2, f6, f0
    stfs f0, 0x60(r31)
    lfs f2, 0x17c(r1)
    lfs f1, 0x180(r1)
    lfs f0, 0x184(r1)
    fsubs f5, f2, f6
    lfs f2, 0x170(r1)
    fsubs f4, f1, f6
    lfs f1, 0x174(r1)
    fsubs f3, f0, f6
    lfs f0, 0x178(r1)
    fsubs f2, f2, f6
    stfs f5, 0xe0(r1)
    fsubs f1, f1, f6
    fsubs f0, f0, f6
    stfs f4, 0xe4(r1)
    stfs f3, 0xe8(r1)
    stfs f2, 0xec(r1)
    stfs f1, 0xf0(r1)
    stfs f0, 0xf4(r1)
    bl PSVECCrossProduct
    addi r3, r1, 0xf8
    mr r4, r3
    bl Vec3_Normalize
    lfs f0, 0xf8(r1)
    addi r3, r1, 0xbc
    lfs f6, lbl_806D73E0(r2)
    addi r4, r1, 0xc8
    stfs f0, 0x64(r31)
    addi r5, r1, 0xd4
    lfs f0, 0xfc(r1)
    stfs f0, 0x68(r31)
    lfs f0, 0x100(r1)
    stfs f0, 0x6c(r31)
    lfs f0, 0xfc(r1)
    lfs f1, 0xf8(r1)
    fmuls f0, f0, f6
    lfs f2, 0x100(r1)
    fmadds f0, f1, f6, f0
    fnmadds f0, f2, f6, f0
    stfs f0, 0x70(r31)
    lfs f2, 0x170(r1)
    lfs f1, 0x174(r1)
    lfs f0, 0x178(r1)
    fsubs f5, f2, f6
    lfs f2, 0x194(r1)
    fsubs f4, f1, f6
    lfs f1, 0x198(r1)
    fsubs f3, f0, f6
    lfs f0, 0x19c(r1)
    fsubs f2, f2, f6
    stfs f5, 0xbc(r1)
    fsubs f1, f1, f6
    fsubs f0, f0, f6
    stfs f4, 0xc0(r1)
    stfs f3, 0xc4(r1)
    stfs f2, 0xc8(r1)
    stfs f1, 0xcc(r1)
    stfs f0, 0xd0(r1)
    bl PSVECCrossProduct
    addi r3, r1, 0xd4
    mr r4, r3
    bl Vec3_Normalize
    lfs f0, 0xd4(r1)
    li r3, 0x0
    lfs f2, lbl_806D73E0(r2)
    stfs f0, 0x74(r31)
    lfs f0, 0xd8(r1)
    stfs f0, 0x78(r31)
    lfs f0, 0xdc(r1)
    stfs f0, 0x7c(r31)
    lfs f0, 0xd8(r1)
    lfs f1, 0xd4(r1)
    fmuls f0, f0, f2
    lfs f3, 0xdc(r1)
    fmadds f0, f1, f2, f0
    fnmadds f0, f3, f2, f0
    stfs f0, 0x80(r31)
    b fn_80137E50_L_80138564
    fn_80137E50_L_8013823C:
    lfs f1, 0x188(r1)
    addi r3, r1, 0x98
    lfs f2, 0x17c(r1)
    addi r4, r1, 0xa4
    lfs f0, 0x194(r1)
    addi r5, r1, 0xb0
    fsubs f5, f1, f2
    lfs f1, 0x18c(r1)
    lfs f3, 0x180(r1)
    fsubs f2, f0, f2
    lfs f0, 0x198(r1)
    fsubs f4, f1, f3
    fsubs f1, f0, f3
    lfs f3, 0x190(r1)
    lfs f6, 0x184(r1)
    lfs f0, 0x19c(r1)
    fsubs f3, f3, f6
    stfs f5, 0x98(r1)
    fsubs f0, f0, f6
    stfs f4, 0x9c(r1)
    stfs f3, 0xa0(r1)
    stfs f2, 0xa4(r1)
    stfs f1, 0xa8(r1)
    stfs f0, 0xac(r1)
    bl PSVECCrossProduct
    addi r3, r1, 0xb0
    mr r4, r3
    bl Vec3_Normalize
    lfs f0, 0xb0(r1)
    addi r3, r1, 0x74
    lfs f6, lbl_806D73E0(r2)
    addi r4, r1, 0x80
    stfs f0, 0x34(r31)
    addi r5, r1, 0x8c
    lfs f0, 0xb4(r1)
    stfs f0, 0x38(r31)
    lfs f0, 0xb8(r1)
    stfs f0, 0x3c(r31)
    lfs f1, 0xb4(r1)
    lfs f0, 0x180(r1)
    lfs f2, 0xb0(r1)
    fmuls f0, f1, f0
    lfs f1, 0x17c(r1)
    lfs f4, 0xb8(r1)
    lfs f3, 0x184(r1)
    fmadds f0, f2, f1, f0
    fnmadds f0, f4, f3, f0
    stfs f0, 0x40(r31)
    lfs f2, 0x188(r1)
    lfs f1, 0x18c(r1)
    lfs f0, 0x190(r1)
    fsubs f5, f2, f6
    lfs f2, 0x194(r1)
    fsubs f4, f1, f6
    lfs f1, 0x198(r1)
    fsubs f3, f0, f6
    lfs f0, 0x19c(r1)
    fsubs f2, f2, f6
    stfs f5, 0x74(r1)
    fsubs f1, f1, f6
    fsubs f0, f0, f6
    stfs f4, 0x78(r1)
    stfs f3, 0x7c(r1)
    stfs f2, 0x80(r1)
    stfs f1, 0x84(r1)
    stfs f0, 0x88(r1)
    bl PSVECCrossProduct
    addi r3, r1, 0x8c
    mr r4, r3
    bl Vec3_Normalize
    lfs f0, 0x8c(r1)
    addi r3, r1, 0x50
    lfs f6, lbl_806D73E0(r2)
    addi r4, r1, 0x5c
    stfs f0, 0x44(r31)
    addi r5, r1, 0x68
    lfs f0, 0x90(r1)
    stfs f0, 0x48(r31)
    lfs f0, 0x94(r1)
    stfs f0, 0x4c(r31)
    lfs f0, 0x90(r1)
    lfs f1, 0x8c(r1)
    fmuls f0, f0, f6
    lfs f2, 0x94(r1)
    fmadds f0, f1, f6, f0
    fnmadds f0, f2, f6, f0
    stfs f0, 0x50(r31)
    lfs f2, 0x17c(r1)
    lfs f1, 0x180(r1)
    lfs f0, 0x184(r1)
    fsubs f5, f2, f6
    lfs f2, 0x188(r1)
    fsubs f4, f1, f6
    lfs f1, 0x18c(r1)
    fsubs f3, f0, f6
    lfs f0, 0x190(r1)
    fsubs f2, f2, f6
    stfs f5, 0x50(r1)
    fsubs f1, f1, f6
    fsubs f0, f0, f6
    stfs f4, 0x54(r1)
    stfs f3, 0x58(r1)
    stfs f2, 0x5c(r1)
    stfs f1, 0x60(r1)
    stfs f0, 0x64(r1)
    bl PSVECCrossProduct
    addi r3, r1, 0x68
    mr r4, r3
    bl Vec3_Normalize
    lfs f0, 0x68(r1)
    addi r3, r1, 0x2c
    lfs f6, lbl_806D73E0(r2)
    addi r4, r1, 0x38
    stfs f0, 0x54(r31)
    addi r5, r1, 0x44
    lfs f0, 0x6c(r1)
    stfs f0, 0x58(r31)
    lfs f0, 0x70(r1)
    stfs f0, 0x5c(r31)
    lfs f0, 0x6c(r1)
    lfs f1, 0x68(r1)
    fmuls f0, f0, f6
    lfs f2, 0x70(r1)
    fmadds f0, f1, f6, f0
    fnmadds f0, f2, f6, f0
    stfs f0, 0x60(r31)
    lfs f2, 0x170(r1)
    lfs f1, 0x174(r1)
    lfs f0, 0x178(r1)
    fsubs f5, f2, f6
    lfs f2, 0x17c(r1)
    fsubs f4, f1, f6
    lfs f1, 0x180(r1)
    fsubs f3, f0, f6
    lfs f0, 0x184(r1)
    fsubs f2, f2, f6
    stfs f5, 0x2c(r1)
    fsubs f1, f1, f6
    fsubs f0, f0, f6
    stfs f4, 0x30(r1)
    stfs f3, 0x34(r1)
    stfs f2, 0x38(r1)
    stfs f1, 0x3c(r1)
    stfs f0, 0x40(r1)
    bl PSVECCrossProduct
    addi r3, r1, 0x44
    mr r4, r3
    bl Vec3_Normalize
    lfs f0, 0x44(r1)
    addi r3, r1, 0x8
    lfs f6, lbl_806D73E0(r2)
    addi r4, r1, 0x14
    stfs f0, 0x64(r31)
    addi r5, r1, 0x20
    lfs f0, 0x48(r1)
    stfs f0, 0x68(r31)
    lfs f0, 0x4c(r1)
    stfs f0, 0x6c(r31)
    lfs f0, 0x48(r1)
    lfs f1, 0x44(r1)
    fmuls f0, f0, f6
    lfs f2, 0x4c(r1)
    fmadds f0, f1, f6, f0
    fnmadds f0, f2, f6, f0
    stfs f0, 0x70(r31)
    lfs f2, 0x194(r1)
    lfs f1, 0x198(r1)
    lfs f0, 0x19c(r1)
    fsubs f5, f2, f6
    lfs f2, 0x170(r1)
    fsubs f4, f1, f6
    lfs f1, 0x174(r1)
    fsubs f3, f0, f6
    lfs f0, 0x178(r1)
    fsubs f2, f2, f6
    stfs f5, 0x8(r1)
    fsubs f1, f1, f6
    fsubs f0, f0, f6
    stfs f4, 0xc(r1)
    stfs f3, 0x10(r1)
    stfs f2, 0x14(r1)
    stfs f1, 0x18(r1)
    stfs f0, 0x1c(r1)
    bl PSVECCrossProduct
    addi r3, r1, 0x20
    mr r4, r3
    bl Vec3_Normalize
    lfs f0, 0x20(r1)
    li r3, 0x1
    lfs f2, lbl_806D73E0(r2)
    stfs f0, 0x74(r31)
    lfs f0, 0x24(r1)
    stfs f0, 0x78(r31)
    lfs f0, 0x28(r1)
    stfs f0, 0x7c(r31)
    lfs f0, 0x24(r1)
    lfs f1, 0x20(r1)
    fmuls f0, f0, f2
    lfs f3, 0x28(r1)
    fmadds f0, f1, f2, f0
    fnmadds f0, f3, f2, f0
    stfs f0, 0x80(r31)
    fn_80137E50_L_80138564:
    lwz r0, 0x1b4(r1)
    lwz r31, 0x1ac(r1)
    mtlr r0
    addi r1, r1, 0x1b0
    blr
}

extern "C" void fn_80138578(void)
{
    FreeNode *p = lbl_806D1520;
    while (p) {
        FreeNode *next = p->next;
        if (p) {
            MemoryManager_TimedFree(p);
        }
        p = next;
    }
    lbl_806D1520 = 0;
    lbl_806D1524 = 0;
}

extern "C" asm void fn_801385CC(void) { /* 0x801385CC size:0x1D0 */
    nofralloc
    stwu r1, -0x60(r1)
    mflr r0
    cmplwi r3, 0x0
    stw r0, 0x64(r1)
    stmw r24, 0x40(r1)
    beq fn_801385CC_L_80138788
    addi r31, r1, 0x2c
    addi r30, r1, 0x20
    addi r29, r1, 0x14
    mr r28, r3
    li r27, 0x0
    b fn_801385CC_L_80138780
    fn_801385CC_L_801385FC:
    mr r3, r28
    bl HSD_JObjGetDObj
    mr r26, r3
    b fn_801385CC_L_801386D4
    fn_801385CC_L_8013860C:
    cmplwi r26, 0x0
    beq fn_801385CC_L_8013861C
    lwz r0, 0xc(r26)
    b fn_801385CC_L_80138620
    fn_801385CC_L_8013861C:
    li r0, 0x0
    fn_801385CC_L_80138620:
    mr r25, r0
    b fn_801385CC_L_801386B4
    fn_801385CC_L_80138628:
    mr r3, r28
    mr r4, r25
    mr r6, r29
    mr r7, r30
    mr r8, r31
    addi r5, r1, 0x8
    bl fn_80185FE8
    clrlwi. r0, r3, 24
    beq fn_801385CC_L_8013869C
    li r3, 0x9c
    bl Alloc
    mr. r24, r3
    beq fn_801385CC_L_80138670
    mr r5, r29
    mr r6, r30
    mr r7, r31
    addi r4, r1, 0x8
    bl fn_80138A50
    fn_801385CC_L_80138670:
    lwz r3, lbl_806D1520(r13)
    cmplwi r3, 0x0
    bne fn_801385CC_L_8013868C
    stw r24, lbl_806D1520(r13)
    b fn_801385CC_L_8013869C
    b fn_801385CC_L_8013868C
    fn_801385CC_L_80138688:
    mr r3, r0
    fn_801385CC_L_8013868C:
    lwz r0, 0x0(r3)
    cmplwi r0, 0x0
    bne fn_801385CC_L_80138688
    stw r24, 0x0(r3)
    fn_801385CC_L_8013869C:
    cmplwi r25, 0x0
    beq fn_801385CC_L_801386AC
    lwz r0, 0x4(r25)
    b fn_801385CC_L_801386B0
    fn_801385CC_L_801386AC:
    li r0, 0x0
    fn_801385CC_L_801386B0:
    mr r25, r0
    fn_801385CC_L_801386B4:
    cmplwi r25, 0x0
    bne fn_801385CC_L_80138628
    cmplwi r26, 0x0
    beq fn_801385CC_L_801386CC
    lwz r0, 0x4(r26)
    b fn_801385CC_L_801386D0
    fn_801385CC_L_801386CC:
    li r0, 0x0
    fn_801385CC_L_801386D0:
    mr r26, r0
    fn_801385CC_L_801386D4:
    cmplwi r26, 0x0
    bne fn_801385CC_L_8013860C
    mr r3, r28
    bl HSD_JObjGetFlags
    rlwinm. r0, r3, 0, 19, 19
    bne fn_801385CC_L_80138710
    cmplwi r28, 0x0
    bne fn_801385CC_L_801386FC
    li r0, 0x0
    b fn_801385CC_L_80138700
    fn_801385CC_L_801386FC:
    lwz r0, 0x10(r28)
    fn_801385CC_L_80138700:
    cmplwi r0, 0x0
    beq fn_801385CC_L_80138710
    addi r27, r27, 0x1
    b fn_801385CC_L_8013877C
    fn_801385CC_L_80138710:
    cmpwi r27, 0x0
    ble fn_801385CC_L_80138734
    cmplwi r28, 0x0
    bne fn_801385CC_L_80138728
    li r0, 0x0
    b fn_801385CC_L_8013872C
    fn_801385CC_L_80138728:
    lwz r0, 0x8(r28)
    fn_801385CC_L_8013872C:
    cmplwi r0, 0x0
    bne fn_801385CC_L_8013877C
    fn_801385CC_L_80138734:
    cmplwi r28, 0x0
    bne fn_801385CC_L_80138744
    li r3, 0x0
    b fn_801385CC_L_80138748
    fn_801385CC_L_80138744:
    lwz r3, 0xc(r28)
    fn_801385CC_L_80138748:
    cmplwi r3, 0x0
    mr r0, r3
    subi r27, r27, 0x1
    beq fn_801385CC_L_80138774
    mr r28, r3
    bne fn_801385CC_L_80138768
    li r0, 0x0
    b fn_801385CC_L_8013876C
    fn_801385CC_L_80138768:
    lwz r0, 0x8(r3)
    fn_801385CC_L_8013876C:
    cmplwi r0, 0x0
    beq fn_801385CC_L_80138734
    fn_801385CC_L_80138774:
    cmpwi r27, 0x0
    ble fn_801385CC_L_80138788
    fn_801385CC_L_8013877C:
    mr r28, r0
    fn_801385CC_L_80138780:
    cmplwi r28, 0x0
    bne fn_801385CC_L_801385FC
    fn_801385CC_L_80138788:
    lmw r24, 0x40(r1)
    lwz r0, 0x64(r1)
    mtlr r0
    addi r1, r1, 0x60
    blr
}

extern "C" asm void fn_8013879C(void) { /* 0x8013879C size:0x2B4 */
    nofralloc
    stwu r1, -0xc0(r1)
    mflr r0
    stw r0, 0xc4(r1)
    stfd f31, 0xb0(r1)
    psq_st f31, 0xb8(r1), 0, 0
    stfd f30, 0xa0(r1)
    psq_st f30, 0xa8(r1), 0, 0
    stw r31, 0x9c(r1)
    mr. r31, r3
    fmr f30, f2
    beq fn_8013879C_L_80138A2C
    fneg f3, f3
    lfs f0, lbl_806D73E4(r2)
    fneg f2, f4
    fmuls f1, f0, f1
    stfs f3, 0x40(r31)
    stfs f2, 0x44(r31)
    bl tan
    lfs f2, 0x44(r31)
    frsp f31, f1
    lfs f3, lbl_806D73E0(r2)
    addi r3, r1, 0x74
    fneg f0, f2
    addi r4, r1, 0x80
    fsubs f1, f2, f3
    fmuls f30, f31, f30
    addi r5, r1, 0x8c
    fmuls f4, f0, f31
    stfs f1, 0x7c(r1)
    fmuls f2, f2, f30
    fneg f0, f4
    stfs f1, 0x88(r1)
    fsubs f1, f4, f3
    fsubs f2, f2, f3
    fsubs f0, f0, f3
    stfs f1, 0x78(r1)
    stfs f2, 0x74(r1)
    stfs f2, 0x80(r1)
    stfs f0, 0x84(r1)
    bl PSVECCrossProduct
    addi r3, r1, 0x8c
    mr r4, r3
    bl Vec3_Normalize
    lfs f0, 0x8c(r1)
    addi r3, r1, 0x50
    lfs f3, lbl_806D73E0(r2)
    addi r4, r1, 0x5c
    stfs f0, 0x0(r31)
    addi r5, r1, 0x68
    lfs f0, 0x90(r1)
    stfs f0, 0x4(r31)
    lfs f0, 0x94(r1)
    stfs f0, 0x8(r31)
    lfs f0, 0x90(r1)
    lfs f1, 0x8c(r1)
    fmuls f0, f0, f3
    lfs f2, 0x94(r1)
    fmadds f0, f1, f3, f0
    fnmadds f0, f2, f3, f0
    stfs f0, 0xc(r31)
    lfs f0, 0x44(r31)
    fmuls f5, f0, f31
    fneg f2, f0
    fsubs f1, f0, f3
    fneg f0, f5
    fmuls f4, f2, f30
    fsubs f2, f5, f3
    stfs f1, 0x58(r1)
    fsubs f0, f0, f3
    fsubs f3, f4, f3
    stfs f1, 0x64(r1)
    stfs f2, 0x54(r1)
    stfs f3, 0x50(r1)
    stfs f3, 0x5c(r1)
    stfs f0, 0x60(r1)
    bl PSVECCrossProduct
    addi r3, r1, 0x68
    mr r4, r3
    bl Vec3_Normalize
    lfs f0, 0x68(r1)
    addi r3, r1, 0x2c
    lfs f3, lbl_806D73E0(r2)
    addi r4, r1, 0x38
    stfs f0, 0x10(r31)
    addi r5, r1, 0x44
    lfs f0, 0x6c(r1)
    stfs f0, 0x14(r31)
    lfs f0, 0x70(r1)
    stfs f0, 0x18(r31)
    lfs f0, 0x6c(r1)
    lfs f1, 0x68(r1)
    fmuls f0, f0, f3
    lfs f2, 0x70(r1)
    fmadds f0, f1, f3, f0
    fnmadds f0, f2, f3, f0
    stfs f0, 0x1c(r31)
    lfs f1, 0x44(r31)
    fneg f0, f1
    fsubs f1, f1, f3
    fmuls f2, f0, f30
    fmuls f4, f0, f31
    stfs f1, 0x34(r1)
    fneg f0, f2
    stfs f1, 0x40(r1)
    fsubs f1, f4, f3
    fsubs f2, f2, f3
    fsubs f0, f0, f3
    stfs f1, 0x30(r1)
    stfs f2, 0x2c(r1)
    stfs f0, 0x38(r1)
    stfs f1, 0x3c(r1)
    bl PSVECCrossProduct
    addi r3, r1, 0x44
    mr r4, r3
    bl Vec3_Normalize
    lfs f0, 0x44(r1)
    addi r3, r1, 0x8
    lfs f4, lbl_806D73E0(r2)
    addi r4, r1, 0x14
    stfs f0, 0x20(r31)
    addi r5, r1, 0x20
    lfs f0, 0x48(r1)
    stfs f0, 0x24(r31)
    lfs f0, 0x4c(r1)
    stfs f0, 0x28(r31)
    lfs f0, 0x48(r1)
    lfs f1, 0x44(r1)
    fmuls f0, f0, f4
    lfs f2, 0x4c(r1)
    fmadds f0, f1, f4, f0
    fnmadds f0, f2, f4, f0
    stfs f0, 0x2c(r31)
    lfs f0, 0x44(r31)
    fmuls f2, f0, f30
    fsubs f1, f0, f4
    fmuls f5, f0, f31
    fneg f0, f2
    fsubs f3, f2, f4
    stfs f1, 0x10(r1)
    fsubs f2, f5, f4
    fsubs f0, f0, f4
    stfs f1, 0x1c(r1)
    stfs f3, 0x8(r1)
    stfs f2, 0xc(r1)
    stfs f0, 0x14(r1)
    stfs f2, 0x18(r1)
    bl PSVECCrossProduct
    addi r3, r1, 0x20
    mr r4, r3
    bl Vec3_Normalize
    lfs f0, 0x20(r1)
    lfs f2, lbl_806D73E0(r2)
    stfs f0, 0x30(r31)
    lfs f0, 0x24(r1)
    stfs f0, 0x34(r31)
    lfs f0, 0x28(r1)
    stfs f0, 0x38(r31)
    lfs f0, 0x24(r1)
    lfs f1, 0x20(r1)
    fmuls f0, f0, f2
    lfs f3, 0x28(r1)
    fmadds f0, f1, f2, f0
    fnmadds f0, f3, f2, f0
    stfs f0, 0x3c(r31)
    fn_8013879C_L_80138A2C:
    psq_l f31, 0xb8(r1), 0, 0
    lfd f31, 0xb0(r1)
    psq_l f30, 0xa8(r1), 0, 0
    lfd f30, 0xa0(r1)
    lwz r0, 0xc4(r1)
    lwz r31, 0x9c(r1)
    mtlr r0
    addi r1, r1, 0xc0
    blr
}

extern "C" asm void fn_80138A50(void) { /* 0x80138A50 size:0x294 */
    nofralloc
    stwu r1, -0x30(r1)
    mflr r0
    lfs f0, lbl_806D73E0(r2)
    stw r0, 0x34(r1)
    li r0, 0x0
    stw r31, 0x2c(r1)
    mr r31, r3
    stw r0, 0x0(r3)
    stw r0, 0x4(r3)
    stfs f0, 0x8c(r3)
    stfs f0, 0x90(r3)
    stfs f0, 0x94(r3)
    stfs f0, 0x98(r3)
    lfs f0, 0x0(r4)
    stfs f0, 0x8(r3)
    lfs f0, 0x4(r4)
    stfs f0, 0xc(r3)
    lfs f0, 0x8(r4)
    stfs f0, 0x10(r3)
    lfs f0, 0x0(r5)
    stfs f0, 0x14(r3)
    lfs f0, 0x4(r5)
    stfs f0, 0x18(r3)
    lfs f0, 0x8(r5)
    stfs f0, 0x1c(r3)
    lfs f0, 0x0(r6)
    stfs f0, 0x20(r3)
    lfs f0, 0x4(r6)
    stfs f0, 0x24(r3)
    lfs f0, 0x8(r6)
    stfs f0, 0x28(r3)
    lfs f0, 0x0(r7)
    stfs f0, 0x2c(r3)
    lfs f0, 0x4(r7)
    stfs f0, 0x30(r3)
    lfs f0, 0x8(r7)
    stfs f0, 0x34(r3)
    lwz r0, 0x0(r4)
    lwz r3, 0x4(r4)
    stw r0, 0x8(r1)
    stw r0, 0x14(r1)
    stw r3, 0x18(r1)
    lfs f0, 0x14(r1)
    lwz r0, 0x8(r4)
    stw r3, 0xc(r1)
    stw r0, 0x1c(r1)
    lfs f1, 0x0(r5)
    stw r0, 0x10(r1)
    fcmpo cr0, f1, f0
    ble fn_80138A50_L_80138B1C
    stfs f1, 0x14(r1)
    fn_80138A50_L_80138B1C:
    lfs f1, 0x4(r5)
    lfs f0, 0x18(r1)
    fcmpo cr0, f1, f0
    ble fn_80138A50_L_80138B30
    stfs f1, 0x18(r1)
    fn_80138A50_L_80138B30:
    lfs f1, 0x8(r5)
    lfs f0, 0x1c(r1)
    fcmpo cr0, f1, f0
    ble fn_80138A50_L_80138B44
    stfs f1, 0x1c(r1)
    fn_80138A50_L_80138B44:
    lfs f1, 0x0(r5)
    lfs f0, 0x8(r1)
    fcmpo cr0, f1, f0
    bge fn_80138A50_L_80138B58
    stfs f1, 0x8(r1)
    fn_80138A50_L_80138B58:
    lfs f1, 0x4(r5)
    lfs f0, 0xc(r1)
    fcmpo cr0, f1, f0
    bge fn_80138A50_L_80138B6C
    stfs f1, 0xc(r1)
    fn_80138A50_L_80138B6C:
    lfs f1, 0x8(r5)
    lfs f0, 0x10(r1)
    fcmpo cr0, f1, f0
    bge fn_80138A50_L_80138B80
    stfs f1, 0x10(r1)
    fn_80138A50_L_80138B80:
    lfs f1, 0x0(r6)
    lfs f0, 0x14(r1)
    fcmpo cr0, f1, f0
    ble fn_80138A50_L_80138B94
    stfs f1, 0x14(r1)
    fn_80138A50_L_80138B94:
    lfs f1, 0x4(r6)
    lfs f0, 0x18(r1)
    fcmpo cr0, f1, f0
    ble fn_80138A50_L_80138BA8
    stfs f1, 0x18(r1)
    fn_80138A50_L_80138BA8:
    lfs f1, 0x8(r6)
    lfs f0, 0x1c(r1)
    fcmpo cr0, f1, f0
    ble fn_80138A50_L_80138BBC
    stfs f1, 0x1c(r1)
    fn_80138A50_L_80138BBC:
    lfs f1, 0x0(r6)
    lfs f0, 0x8(r1)
    fcmpo cr0, f1, f0
    bge fn_80138A50_L_80138BD0
    stfs f1, 0x8(r1)
    fn_80138A50_L_80138BD0:
    lfs f1, 0x4(r6)
    lfs f0, 0xc(r1)
    fcmpo cr0, f1, f0
    bge fn_80138A50_L_80138BE4
    stfs f1, 0xc(r1)
    fn_80138A50_L_80138BE4:
    lfs f1, 0x8(r6)
    lfs f0, 0x10(r1)
    fcmpo cr0, f1, f0
    bge fn_80138A50_L_80138BF8
    stfs f1, 0x10(r1)
    fn_80138A50_L_80138BF8:
    lfs f1, 0x0(r7)
    lfs f0, 0x14(r1)
    fcmpo cr0, f1, f0
    ble fn_80138A50_L_80138C0C
    stfs f1, 0x14(r1)
    fn_80138A50_L_80138C0C:
    lfs f1, 0x4(r7)
    lfs f0, 0x18(r1)
    fcmpo cr0, f1, f0
    ble fn_80138A50_L_80138C20
    stfs f1, 0x18(r1)
    fn_80138A50_L_80138C20:
    lfs f1, 0x8(r7)
    lfs f0, 0x1c(r1)
    fcmpo cr0, f1, f0
    ble fn_80138A50_L_80138C34
    stfs f1, 0x1c(r1)
    fn_80138A50_L_80138C34:
    lfs f1, 0x0(r7)
    lfs f0, 0x8(r1)
    fcmpo cr0, f1, f0
    bge fn_80138A50_L_80138C48
    stfs f1, 0x8(r1)
    fn_80138A50_L_80138C48:
    lfs f1, 0x4(r7)
    lfs f0, 0xc(r1)
    fcmpo cr0, f1, f0
    bge fn_80138A50_L_80138C5C
    stfs f1, 0xc(r1)
    fn_80138A50_L_80138C5C:
    lfs f1, 0x8(r7)
    lfs f0, 0x10(r1)
    fcmpo cr0, f1, f0
    bge fn_80138A50_L_80138C70
    stfs f1, 0x10(r1)
    fn_80138A50_L_80138C70:
    lfs f1, 0x14(r1)
    addi r3, r1, 0x14
    lfs f0, 0x8(r1)
    mr r5, r3
    lfs f3, lbl_806D73E4(r2)
    addi r4, r31, 0x8c
    fadds f2, f1, f0
    lfs f1, 0xc(r1)
    lfs f0, 0x10(r1)
    fmuls f2, f3, f2
    stfs f2, 0x8c(r31)
    lfs f2, 0x18(r1)
    fadds f1, f2, f1
    fmuls f1, f3, f1
    stfs f1, 0x90(r31)
    lfs f1, 0x1c(r1)
    fadds f0, f1, f0
    fmuls f0, f3, f0
    stfs f0, 0x94(r31)
    bl Vec3_Subtract
    addi r3, r1, 0x14
    bl Vec3_Magnitude
    stfs f1, 0x98(r31)
    mr r3, r31
    lwz r0, 0x34(r1)
    lwz r31, 0x2c(r1)
    mtlr r0
    addi r1, r1, 0x30
    blr
}

extern "C" void CourseObjects_Activate(void)
{
    for (CourseObj *o = lbl_806D1534; o < lbl_806D1534 + lbl_806D1538; o++) {
        if (o->state == 0) {
            o->state = 1;
            o->f34 = lbl_806D73E8;
            o->f1C = lbl_806D73E8;
            o->px = o->x;
            o->py = o->y;
            o->pz = o->z;
            o->f30 = lbl_806D73E8;
        }
    }
}

extern "C" void fn_80138D48(void)
{
    for (CourseObj *o = lbl_806D1534; o < lbl_806D1534 + lbl_806D1538; o++) {
        if (o->state == 0 || o->state == 1) {
            o->state = 2;
            o->f34 = lbl_806D73EC;
            o->f1C = lbl_806D73E8;
            o->px = o->x;
            o->py = o->y;
            o->pz = o->z;
            o->f30 = lbl_806D73E8;
        }
    }
}

extern "C" asm void fn_80138DB8(void) { /* 0x80138DB8 size:0xA58 */
    nofralloc
    stwu r1, -0x260(r1)
    mflr r0
    stw r0, 0x264(r1)
    stfd f31, 0x250(r1)
    psq_st f31, 0x258(r1), 0, 0
    stfd f30, 0x240(r1)
    psq_st f30, 0x248(r1), 0, 0
    stmw r24, 0x220(r1)
    lwz r0, lbl_806D1538(r13)
    cmpwi r0, 0x0
    beq fn_80138DB8_L_801397EC
    lwz r31, lbl_806D1534(r13)
    b fn_80138DB8_L_801391F0
    fn_80138DB8_L_80138DEC:
    li r0, 0x0
    stb r0, 0x38(r31)
    lwz r0, 0x18(r31)
    cmpwi r0, 0x0
    beq fn_80138DB8_L_801391EC
    cmpwi r0, 0x4
    beq fn_80138DB8_L_801391EC
    lfs f1, 0x34(r31)
    lfs f0, lbl_806D73E8(r2)
    fcmpo cr0, f1, f0
    cror eq, lt, eq
    beq fn_80138DB8_L_801391EC
    lfs f1, lbl_806D73F0(r2)
    addi r3, r31, 0x20
    addi r4, r1, 0x14
    bl fn_80137718
    clrlwi. r0, r3, 24
    beq fn_80138DB8_L_801391EC
    lfs f1, 0x1c(r1)
    lfs f0, lbl_806D73F4(r2)
    fcmpo cr0, f1, f0
    ble fn_80138DB8_L_801391EC
    li r0, 0x1
    lfs f2, lbl_806D73E8(r2)
    stb r0, 0x38(r31)
    addi r24, r1, 0xf0
    lfs f0, lbl_806D73EC(r2)
    stfs f2, 0x1e0(r1)
    stfs f2, 0x1f4(r1)
    stfs f2, 0x208(r1)
    stfs f2, 0x21c(r1)
    stfs f2, 0xf0(r1)
    stfs f2, 0x104(r1)
    stfs f2, 0x118(r1)
    stfs f2, 0x12c(r1)
    stfs f2, 0x1e4(r1)
    stfs f2, 0x1e8(r1)
    stfs f2, 0x1ec(r1)
    stfs f2, 0x1f0(r1)
    stfs f2, 0x1f8(r1)
    stfs f2, 0x1fc(r1)
    stfs f2, 0x200(r1)
    stfs f2, 0x204(r1)
    stfs f2, 0x20c(r1)
    stfs f2, 0x210(r1)
    stfs f2, 0x214(r1)
    stfs f2, 0x218(r1)
    stfs f0, 0x21c(r1)
    stfs f0, 0x208(r1)
    stfs f0, 0x1f4(r1)
    stfs f0, 0x1e0(r1)
    lfs f30, 0x30(r31)
    stfs f2, 0xf4(r1)
    fmr f1, f30
    stfs f2, 0xf8(r1)
    stfs f2, 0xfc(r1)
    stfs f2, 0x100(r1)
    stfs f2, 0x108(r1)
    stfs f2, 0x10c(r1)
    stfs f2, 0x110(r1)
    stfs f2, 0x114(r1)
    stfs f2, 0x11c(r1)
    stfs f2, 0x120(r1)
    stfs f2, 0x124(r1)
    stfs f2, 0x128(r1)
    stfs f0, 0x12c(r1)
    stfs f0, 0x118(r1)
    stfs f0, 0x104(r1)
    stfs f0, 0xf0(r1)
    bl cos
    frsp f31, f1
    fmr f1, f30
    bl sin
    frsp f1, f1
    li r5, 0x0
    li r0, 0x2
    stfs f31, 0xf0(r1)
    mr r4, r5
    addi r6, r1, 0x70
    fneg f0, f1
    stfs f1, 0x110(r1)
    stfs f31, 0x118(r1)
    stfs f0, 0xf8(r1)
    mtctr r0
    fn_80138DB8_L_80138F3C:
    lfs f7, 0x0(r24)
    slwi r0, r5, 2
    lfs f6, 0x1e0(r1)
    addi r3, r5, 0x1
    lfs f5, 0x4(r24)
    fmuls f8, f7, f6
    lfs f4, 0x1f0(r1)
    lfs f3, 0x8(r24)
    lfs f2, 0x200(r1)
    fmadds f8, f5, f4, f8
    lfs f1, 0xc(r24)
    lfs f0, 0x210(r1)
    lfs f6, 0x1e4(r1)
    fmadds f8, f3, f2, f8
    lfs f4, 0x1f4(r1)
    lfs f2, 0x204(r1)
    fmadds f8, f1, f0, f8
    lfs f0, 0x214(r1)
    stfsx f8, r6, r0
    fmuls f8, f7, f6
    slwi r0, r3, 2
    lfs f6, 0x1e8(r1)
    addi r3, r5, 0x2
    fmadds f8, f5, f4, f8
    lfs f4, 0x1f8(r1)
    fmadds f8, f3, f2, f8
    lfs f2, 0x208(r1)
    fmadds f8, f1, f0, f8
    lfs f0, 0x218(r1)
    stfsx f8, r6, r0
    fmuls f8, f7, f6
    slwi r0, r3, 2
    addi r3, r5, 0x3
    lfs f6, 0x1ec(r1)
    addi r5, r5, 0x4
    fmadds f8, f5, f4, f8
    lfs f4, 0x1fc(r1)
    fmadds f8, f3, f2, f8
    lfs f2, 0x20c(r1)
    fmadds f8, f1, f0, f8
    lfs f0, 0x21c(r1)
    stfsx f8, r6, r0
    fmuls f8, f7, f6
    slwi r0, r3, 2
    fmadds f8, f5, f4, f8
    fmadds f8, f3, f2, f8
    fmadds f8, f1, f0, f8
    stfsx f8, r6, r0
    lfs f7, 0x10(r24)
    slwi r0, r5, 2
    lfs f6, 0x1e0(r1)
    addi r3, r5, 0x1
    lfs f5, 0x14(r24)
    addi r4, r4, 0x1
    fmuls f8, f7, f6
    lfs f4, 0x1f0(r1)
    lfs f3, 0x18(r24)
    lfs f1, 0x1c(r24)
    addi r24, r24, 0x20
    fmadds f8, f5, f4, f8
    lfs f2, 0x200(r1)
    lfs f0, 0x210(r1)
    fmadds f8, f3, f2, f8
    lfs f6, 0x1e4(r1)
    lfs f4, 0x1f4(r1)
    lfs f2, 0x204(r1)
    fmadds f8, f1, f0, f8
    lfs f0, 0x214(r1)
    stfsx f8, r6, r0
    fmuls f8, f7, f6
    slwi r0, r3, 2
    lfs f6, 0x1e8(r1)
    addi r3, r5, 0x2
    fmadds f8, f5, f4, f8
    lfs f4, 0x1f8(r1)
    fmadds f8, f3, f2, f8
    lfs f2, 0x208(r1)
    fmadds f8, f1, f0, f8
    lfs f0, 0x218(r1)
    stfsx f8, r6, r0
    fmuls f8, f7, f6
    slwi r0, r3, 2
    addi r3, r5, 0x3
    lfs f6, 0x1ec(r1)
    addi r5, r5, 0x4
    fmadds f8, f5, f4, f8
    lfs f4, 0x1fc(r1)
    fmadds f8, f3, f2, f8
    lfs f2, 0x20c(r1)
    fmadds f8, f1, f0, f8
    lfs f0, 0x21c(r1)
    stfsx f8, r6, r0
    fmuls f8, f7, f6
    slwi r0, r3, 2
    fmadds f8, f5, f4, f8
    fmadds f8, f3, f2, f8
    fmadds f8, f1, f0, f8
    stfsx f8, r6, r0
    bdnz fn_80138DB8_L_80138F3C
    lfs f7, 0x70(r1)
    addi r3, r1, 0x1e0
    lfs f6, 0x74(r1)
    addi r4, r31, 0x3c
    stfs f7, 0xf0(r1)
    lfs f5, 0x78(r1)
    stfs f6, 0xf4(r1)
    lfs f4, 0x7c(r1)
    stfs f5, 0xf8(r1)
    lfs f3, 0x80(r1)
    stfs f4, 0xfc(r1)
    lfs f2, 0x84(r1)
    stfs f3, 0x100(r1)
    lfs f1, 0x88(r1)
    stfs f2, 0x104(r1)
    lfs f0, 0x8c(r1)
    stfs f1, 0x108(r1)
    lfs f7, 0x90(r1)
    stfs f0, 0x10c(r1)
    lfs f6, 0x94(r1)
    lfs f5, 0x98(r1)
    lfs f4, 0x9c(r1)
    lfs f3, 0xa0(r1)
    lfs f2, 0xa4(r1)
    lfs f1, 0xa8(r1)
    lfs f0, 0xac(r1)
    stfs f7, 0x110(r1)
    lwz r24, 0xf0(r1)
    stfs f6, 0x114(r1)
    lwz r25, 0xf4(r1)
    stfs f5, 0x118(r1)
    lwz r26, 0xf8(r1)
    stfs f4, 0x11c(r1)
    lwz r27, 0xfc(r1)
    stfs f3, 0x120(r1)
    lwz r28, 0x100(r1)
    stfs f2, 0x124(r1)
    lwz r29, 0x104(r1)
    stfs f1, 0x128(r1)
    lwz r30, 0x108(r1)
    stfs f0, 0x12c(r1)
    lwz r12, 0x10c(r1)
    lwz r11, 0x110(r1)
    lwz r10, 0x114(r1)
    lwz r9, 0x118(r1)
    lwz r8, 0x11c(r1)
    lwz r7, 0x120(r1)
    lwz r6, 0x124(r1)
    lwz r5, 0x128(r1)
    lwz r0, 0x12c(r1)
    stw r24, 0x1e0(r1)
    stw r25, 0x1e4(r1)
    stw r26, 0x1e8(r1)
    stw r27, 0x1ec(r1)
    stw r28, 0x1f0(r1)
    stw r29, 0x1f4(r1)
    stw r30, 0x1f8(r1)
    stw r12, 0x1fc(r1)
    stw r11, 0x200(r1)
    stw r10, 0x204(r1)
    stw r9, 0x208(r1)
    stw r8, 0x20c(r1)
    stw r7, 0x210(r1)
    stw r6, 0x214(r1)
    stw r5, 0x218(r1)
    stw r0, 0x21c(r1)
    lfs f2, 0x28(r31)
    lfs f1, 0x24(r31)
    lfs f0, 0x20(r31)
    stfs f0, 0x210(r1)
    stfs f1, 0x214(r1)
    stfs f2, 0x218(r1)
    bl Mtx4x4_TransposeTo4x3
    fn_80138DB8_L_801391EC:
    addi r31, r31, 0xc0
    fn_80138DB8_L_801391F0:
    lwz r0, lbl_806D1538(r13)
    lwz r3, lbl_806D1534(r13)
    mulli r0, r0, 0xc0
    add r0, r3, r0
    cmplw r31, r0
    blt fn_80138DB8_L_80138DEC
    lwz r3, lbl_806D1528(r13)
    li r4, 0x0
    bl LinkedNode_GetField10_OrFallback
    bl HSD_JObjGetDObj
    mr r31, r3
    lwz r3, lbl_806D1528(r13)
    li r4, 0x0
    bl LinkedNode_GetField10_OrFallback
    mr r4, r3
    mr r5, r31
    addi r3, r1, 0x5c
    lis r6, 0x4000
    li r7, 0x1
    bl GXChannel_Init
    lwz r24, lbl_806D1534(r13)
    b fn_80138DB8_L_80139280
    fn_80138DB8_L_80139248:
    lbz r0, 0x38(r24)
    cmplwi r0, 0x0
    beq fn_80138DB8_L_8013927C
    lwz r0, 0x0(r24)
    cmpwi r0, 0x1
    bne fn_80138DB8_L_8013927C
    lwz r3, lbl_806D1528(r13)
    li r4, 0x0
    lfs f1, 0x34(r24)
    bl Object_SetColorAlphaOnly
    addi r3, r1, 0x5c
    addi r4, r24, 0x3c
    bl GXChannel_PushTransform
    fn_80138DB8_L_8013927C:
    addi r24, r24, 0xc0
    fn_80138DB8_L_80139280:
    lwz r0, lbl_806D1538(r13)
    lwz r3, lbl_806D1534(r13)
    mulli r0, r0, 0xc0
    add r0, r3, r0
    cmplw r24, r0
    blt fn_80138DB8_L_80139248
    addi r3, r1, 0x5c
    li r4, -0x1
    bl dtor_8007D9C4
    lwz r3, lbl_806D152C(r13)
    li r4, 0x0
    bl LinkedNode_GetField10_OrFallback
    bl HSD_JObjGetDObj
    mr r31, r3
    lwz r3, lbl_806D152C(r13)
    li r4, 0x0
    bl LinkedNode_GetField10_OrFallback
    mr r4, r3
    mr r5, r31
    addi r3, r1, 0x48
    lis r6, 0x4000
    li r7, 0x1
    bl GXChannel_Init
    lwz r24, lbl_806D1534(r13)
    b fn_80138DB8_L_8013931C
    fn_80138DB8_L_801392E4:
    lbz r0, 0x38(r24)
    cmplwi r0, 0x0
    beq fn_80138DB8_L_80139318
    lwz r0, 0x0(r24)
    cmpwi r0, 0x2
    bne fn_80138DB8_L_80139318
    lwz r3, lbl_806D152C(r13)
    li r4, 0x0
    lfs f1, 0x34(r24)
    bl Object_SetColorAlphaOnly
    addi r3, r1, 0x48
    addi r4, r24, 0x3c
    bl GXChannel_PushTransform
    fn_80138DB8_L_80139318:
    addi r24, r24, 0xc0
    fn_80138DB8_L_8013931C:
    lwz r0, lbl_806D1538(r13)
    lwz r3, lbl_806D1534(r13)
    mulli r0, r0, 0xc0
    add r0, r3, r0
    cmplw r24, r0
    blt fn_80138DB8_L_801392E4
    addi r3, r1, 0x48
    li r4, -0x1
    bl dtor_8007D9C4
    lwz r3, lbl_806D152C(r13)
    li r4, 0x0
    bl LinkedNode_GetField10_OrFallback
    cmplwi r3, 0x0
    bne fn_80138DB8_L_8013935C
    li r24, 0x0
    b fn_80138DB8_L_80139360
    fn_80138DB8_L_8013935C:
    lwz r24, 0x8(r3)
    fn_80138DB8_L_80139360:
    lwz r3, lbl_806D152C(r13)
    li r4, 0x0
    bl LinkedNode_GetField10_OrFallback
    cmplwi r3, 0x0
    bne fn_80138DB8_L_8013937C
    li r3, 0x0
    b fn_80138DB8_L_80139380
    fn_80138DB8_L_8013937C:
    lwz r3, 0x8(r3)
    fn_80138DB8_L_80139380:
    bl HSD_JObjGetDObj
    mr r5, r3
    mr r4, r24
    addi r3, r1, 0x34
    lis r6, 0x4000
    li r7, 0x1
    bl GXChannel_Init
    lwz r24, lbl_806D1534(r13)
    b fn_80138DB8_L_801393DC
    fn_80138DB8_L_801393A4:
    lbz r0, 0x38(r24)
    cmplwi r0, 0x0
    beq fn_80138DB8_L_801393D8
    lwz r0, 0x0(r24)
    cmpwi r0, 0x2
    bne fn_80138DB8_L_801393D8
    lwz r3, lbl_806D152C(r13)
    li r4, 0x0
    lfs f1, 0x34(r24)
    bl Object_SetColorAlphaOnly
    addi r3, r1, 0x34
    addi r4, r24, 0x3c
    bl GXChannel_PushTransform
    fn_80138DB8_L_801393D8:
    addi r24, r24, 0xc0
    fn_80138DB8_L_801393DC:
    lwz r0, lbl_806D1538(r13)
    lwz r3, lbl_806D1534(r13)
    mulli r0, r0, 0xc0
    add r0, r3, r0
    cmplw r24, r0
    blt fn_80138DB8_L_801393A4
    addi r3, r1, 0x34
    li r4, -0x1
    bl dtor_8007D9C4
    lwz r3, lbl_806D1530(r13)
    bl Archive_GetRootJObj
    bl HSD_JObjGetDObj
    mr r31, r3
    lwz r3, lbl_806D1530(r13)
    bl Archive_GetRootJObj
    mr r4, r3
    mr r5, r31
    addi r3, r1, 0x20
    lis r6, 0x4000
    li r7, 0x1
    bl GXChannel_Init
    lwz r25, lbl_806D1534(r13)
    b fn_80138DB8_L_801397C8
    fn_80138DB8_L_80139438:
    lbz r0, 0x38(r25)
    cmplwi r0, 0x1
    bne fn_80138DB8_L_801397C4
    lwz r0, 0x18(r25)
    cmpwi r0, 0x3
    bne fn_80138DB8_L_801397C4
    lfs f31, lbl_806D73E8(r2)
    mr r24, r25
    li r26, 0x0
    fn_80138DB8_L_8013945C:
    lfs f1, 0x70(r24)
    fcmpo cr0, f1, f31
    cror eq, gt, eq
    bne fn_80138DB8_L_801397B4
    lfs f0, lbl_806D73F8(r2)
    addi r3, r25, 0x20
    addi r4, r24, 0x74
    addi r5, r1, 0x8
    fdivs f30, f1, f0
    bl PSVECAdd
    lfs f0, lbl_806D73E8(r2)
    li r5, 0x0
    lfs f3, lbl_806D73EC(r2)
    li r0, 0x2
    lfs f1, 0x34(r25)
    addi r7, r1, 0x1a0
    stfs f0, 0x160(r1)
    fsubs f2, f3, f30
    lfs f5, lbl_806D7400(r2)
    mr r4, r5
    lfs f4, lbl_806D73FC(r2)
    addi r6, r1, 0xb0
    stfs f0, 0x174(r1)
    fnmsubs f4, f5, f30, f4
    stfs f0, 0x188(r1)
    fmuls f30, f2, f1
    stfs f0, 0x19c(r1)
    stfs f3, 0x188(r1)
    stfs f3, 0x174(r1)
    stfs f3, 0x160(r1)
    stfs f0, 0x1a0(r1)
    stfs f0, 0x1b4(r1)
    stfs f0, 0x1c8(r1)
    stfs f0, 0x1dc(r1)
    stfs f0, 0x164(r1)
    stfs f0, 0x168(r1)
    stfs f0, 0x16c(r1)
    stfs f0, 0x170(r1)
    stfs f0, 0x178(r1)
    stfs f0, 0x17c(r1)
    stfs f0, 0x180(r1)
    stfs f0, 0x184(r1)
    stfs f0, 0x18c(r1)
    stfs f0, 0x190(r1)
    stfs f0, 0x194(r1)
    stfs f0, 0x198(r1)
    stfs f3, 0x19c(r1)
    stfs f4, 0x160(r1)
    stfs f4, 0x174(r1)
    stfs f4, 0x188(r1)
    stfs f0, 0x1a4(r1)
    stfs f0, 0x1a8(r1)
    stfs f0, 0x1ac(r1)
    stfs f0, 0x1b0(r1)
    stfs f0, 0x1b8(r1)
    stfs f0, 0x1bc(r1)
    stfs f0, 0x1c0(r1)
    stfs f0, 0x1c4(r1)
    stfs f0, 0x1cc(r1)
    stfs f0, 0x1d0(r1)
    stfs f0, 0x1d4(r1)
    stfs f0, 0x1d8(r1)
    stfs f3, 0x1dc(r1)
    stfs f3, 0x1c8(r1)
    stfs f3, 0x1b4(r1)
    stfs f3, 0x1a0(r1)
    mtctr r0
    fn_80138DB8_L_80139568:
    lfs f7, 0x0(r7)
    slwi r0, r5, 2
    lfs f6, 0x160(r1)
    addi r3, r5, 0x1
    lfs f5, 0x4(r7)
    fmuls f8, f7, f6
    lfs f4, 0x170(r1)
    lfs f3, 0x8(r7)
    lfs f2, 0x180(r1)
    fmadds f8, f5, f4, f8
    lfs f1, 0xc(r7)
    lfs f0, 0x190(r1)
    lfs f6, 0x164(r1)
    fmadds f8, f3, f2, f8
    lfs f4, 0x174(r1)
    lfs f2, 0x184(r1)
    fmadds f8, f1, f0, f8
    lfs f0, 0x194(r1)
    stfsx f8, r6, r0
    fmuls f8, f7, f6
    slwi r0, r3, 2
    lfs f6, 0x168(r1)
    addi r3, r5, 0x2
    fmadds f8, f5, f4, f8
    lfs f4, 0x178(r1)
    fmadds f8, f3, f2, f8
    lfs f2, 0x188(r1)
    fmadds f8, f1, f0, f8
    lfs f0, 0x198(r1)
    stfsx f8, r6, r0
    fmuls f8, f7, f6
    slwi r0, r3, 2
    addi r3, r5, 0x3
    lfs f6, 0x16c(r1)
    addi r5, r5, 0x4
    fmadds f8, f5, f4, f8
    lfs f4, 0x17c(r1)
    fmadds f8, f3, f2, f8
    lfs f2, 0x18c(r1)
    fmadds f8, f1, f0, f8
    lfs f0, 0x19c(r1)
    stfsx f8, r6, r0
    fmuls f8, f7, f6
    slwi r0, r3, 2
    fmadds f8, f5, f4, f8
    fmadds f8, f3, f2, f8
    fmadds f8, f1, f0, f8
    stfsx f8, r6, r0
    lfs f7, 0x10(r7)
    slwi r0, r5, 2
    lfs f6, 0x160(r1)
    addi r3, r5, 0x1
    lfs f5, 0x14(r7)
    addi r4, r4, 0x1
    fmuls f8, f7, f6
    lfs f4, 0x170(r1)
    lfs f3, 0x18(r7)
    lfs f1, 0x1c(r7)
    addi r7, r7, 0x20
    fmadds f8, f5, f4, f8
    lfs f2, 0x180(r1)
    lfs f0, 0x190(r1)
    fmadds f8, f3, f2, f8
    lfs f6, 0x164(r1)
    lfs f4, 0x174(r1)
    lfs f2, 0x184(r1)
    fmadds f8, f1, f0, f8
    lfs f0, 0x194(r1)
    stfsx f8, r6, r0
    fmuls f8, f7, f6
    slwi r0, r3, 2
    lfs f6, 0x168(r1)
    addi r3, r5, 0x2
    fmadds f8, f5, f4, f8
    lfs f4, 0x178(r1)
    fmadds f8, f3, f2, f8
    lfs f2, 0x188(r1)
    fmadds f8, f1, f0, f8
    lfs f0, 0x198(r1)
    stfsx f8, r6, r0
    fmuls f8, f7, f6
    slwi r0, r3, 2
    addi r3, r5, 0x3
    lfs f6, 0x16c(r1)
    addi r5, r5, 0x4
    fmadds f8, f5, f4, f8
    lfs f4, 0x17c(r1)
    fmadds f8, f3, f2, f8
    lfs f2, 0x18c(r1)
    fmadds f8, f1, f0, f8
    lfs f0, 0x19c(r1)
    stfsx f8, r6, r0
    fmuls f8, f7, f6
    slwi r0, r3, 2
    fmadds f8, f5, f4, f8
    fmadds f8, f3, f2, f8
    fmadds f8, f1, f0, f8
    stfsx f8, r6, r0
    bdnz fn_80138DB8_L_80139568
    lfs f2, 0xc0(r1)
    addi r3, r1, 0x1a0
    lfs f1, 0xc4(r1)
    addi r4, r1, 0x130
    lfs f0, 0xc8(r1)
    stfs f2, 0x1b0(r1)
    lfs f7, 0xb0(r1)
    stfs f1, 0x1b4(r1)
    lfs f6, 0xb4(r1)
    stfs f0, 0x1b8(r1)
    lfs f5, 0xb8(r1)
    lfs f4, 0xbc(r1)
    lfs f3, 0xcc(r1)
    lfs f2, 0xe0(r1)
    lfs f1, 0xe4(r1)
    lfs f0, 0xe8(r1)
    stfs f7, 0x1a0(r1)
    lfs f7, 0xd0(r1)
    stfs f6, 0x1a4(r1)
    lfs f6, 0xd4(r1)
    stfs f5, 0x1a8(r1)
    lfs f5, 0xd8(r1)
    stfs f4, 0x1ac(r1)
    lfs f4, 0xdc(r1)
    stfs f3, 0x1bc(r1)
    lfs f3, 0xec(r1)
    stfs f2, 0x1d0(r1)
    lfs f2, 0x8(r1)
    stfs f1, 0x1d4(r1)
    lfs f1, 0xc(r1)
    stfs f0, 0x1d8(r1)
    lfs f0, 0x10(r1)
    stfs f7, 0x1c0(r1)
    stfs f6, 0x1c4(r1)
    stfs f5, 0x1c8(r1)
    stfs f4, 0x1cc(r1)
    stfs f3, 0x1dc(r1)
    stfs f2, 0x1d0(r1)
    stfs f1, 0x1d4(r1)
    stfs f0, 0x1d8(r1)
    bl Mtx4x4_TransposeTo4x3
    fmr f1, f30
    lwz r3, lbl_806D1530(r13)
    li r4, 0x0
    bl Object_SetColorAlphaOnly
    addi r3, r1, 0x20
    addi r4, r1, 0x130
    bl GXChannel_PushTransform
    fn_80138DB8_L_801397B4:
    addi r26, r26, 0x1
    addi r24, r24, 0x10
    cmpwi r26, 0x5
    blt fn_80138DB8_L_8013945C
    fn_80138DB8_L_801397C4:
    addi r25, r25, 0xc0
    fn_80138DB8_L_801397C8:
    lwz r0, lbl_806D1538(r13)
    lwz r3, lbl_806D1534(r13)
    mulli r0, r0, 0xc0
    add r0, r3, r0
    cmplw r25, r0
    blt fn_80138DB8_L_80139438
    addi r3, r1, 0x20
    li r4, -0x1
    bl dtor_8007D9C4
    fn_80138DB8_L_801397EC:
    psq_l f31, 0x258(r1), 0, 0
    lfd f31, 0x250(r1)
    psq_l f30, 0x248(r1), 0, 0
    lfd f30, 0x240(r1)
    lmw r24, 0x220(r1)
    lwz r0, 0x264(r1)
    mtlr r0
    addi r1, r1, 0x260
    blr
}

extern "C" void fn_80139810(void)
{
    ScopedTimer t(0x25);
    fn_80138DB8();
}

