/*
 * Mini-game helpers: the per-cup timer lookup and the trigger-zone lists
 * (box and quad zones chained through `next`, vtable at +4) plus a small
 * game-mode wrapper. Each class declares a virtual that is not defined
 * here first, so the vtables (in data) are not emitted by this unit.
 *
 * Still asm: the timer lookup (callee-saved register order), the colour
 * table init, and the two zone ctors (load scheduling).
 */
#pragma cplusplus on

typedef struct Vec3 {
    float x, y, z;
} Vec3;

extern "C" {
extern int g_cupId;
extern int g_roundIndex;
extern int g_ccClass;
extern int lbl_80355078[][3][2];
extern int lbl_803554E0[][3][2];
extern char lbl_8048E184[];
extern char lbl_8048E1A0[];
extern char lbl_8048E1B0[];
extern char lbl_8048E1CC[];
extern const float lbl_806D6E50;
extern unsigned char IsCardValid(void);
extern float Vec3_Magnitude(const Vec3 *v);
extern void Vec3_Normalize(const Vec3 *in, Vec3 *out);
extern void Vec3_Subtract(const Vec3 *a, const Vec3 *b, Vec3 *out);
extern float Vec3_Dot(const Vec3 *a, const Vec3 *b);
extern void *fn_8014F6A4(void);
}

struct Zone;
extern "C" Zone *dtor_80123870(Zone *z, short flag);

extern "C" {
extern unsigned int lbl_806D6E18;
extern unsigned int lbl_806D6E1C;
extern unsigned int lbl_806D6E20;
extern unsigned int lbl_806D6E24;
extern unsigned int lbl_806D6E28;
extern unsigned int lbl_806D6E2C;
extern unsigned int lbl_806D6E30;
extern unsigned int lbl_806D6E34;
extern unsigned int lbl_8048DAA8[];
asm void MiniGame_GetTimerValue(void);
asm void fn_801232E0(void);
asm void fn_80123674(void);
asm void fn_801238EC(void);

#pragma section R ".extab_user"
__declspec(section ".extab_user") static const unsigned char extab_MiniGame_GetTimerValue[8] = {
    0x18, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

__declspec(section ".extab_user") static const unsigned char extab_fn_801232E0[8] = {
    0x90, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

__declspec(section ".extab_user") static const struct { unsigned int f0; unsigned int f1; unsigned int f2; unsigned int f3; unsigned int f4; unsigned int f5; void *f6; } extab_fn_80123674 = { 0x100A0000, 0x000000B0, 0x000A0010, 0x00000000, 0x8680001E, 0x00000000, (void *)&dtor_80123870 };

__declspec(section ".extab_user") static const struct { unsigned int f0; unsigned int f1; unsigned int f2; unsigned int f3; unsigned int f4; unsigned int f5; void *f6; } extab_fn_801238EC = { 0x180A0000, 0x0000016C, 0x000D0010, 0x00000000, 0x8680001F, 0x00000000, (void *)&dtor_80123870 };

#pragma section R ".extabindex_user"
__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_MiniGame_GetTimerValue = {
    (void *)&MiniGame_GetTimerValue, 0x000000DC, (void *)extab_MiniGame_GetTimerValue
};

__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_fn_801232E0 = {
    (void *)&fn_801232E0, 0x0000019C, (void *)extab_fn_801232E0
};

__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_fn_80123674 = {
    (void *)&fn_80123674, 0x000001FC, (void *)&extab_fn_80123674
};

__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_fn_801238EC = {
    (void *)&fn_801238EC, 0x0000025C, (void *)&extab_fn_801238EC
};

}


void *operator new(unsigned long size);

void operator delete(void *p);

extern "C" int IsUraCourseFromSubMode(void) {
    return g_roundIndex > 3;
}

static inline int CupIndex(void) {
    int cup = g_cupId;
    if (cup >= 9) {
        cup -= 9;
    } else {
        cup -= 1;
    }
    return cup;
}

extern "C" int fn_801231AC(void) {
    int cup = CupIndex();
    if (cup < 0 || IsUraCourseFromSubMode() < 0) {
        return 0;
    }
    return 0;
}

extern "C" asm void MiniGame_GetTimerValue(void) { /* 0x801231FC size:0xDC */
    nofralloc
    stwu r1, -0x20(r1)
    mflr r0
    stw r0, 0x24(r1)
    stw r31, 0x1c(r1)
    stw r30, 0x18(r1)
    stw r29, 0x14(r1)
    lwz r3, g_cupId(r13)
    cmpwi r3, 0x9
    blt MiniGame_GetTimerValue_L_80123228
    subi r31, r3, 0x9
    b MiniGame_GetTimerValue_L_8012322C
    MiniGame_GetTimerValue_L_80123228:
    subi r31, r3, 0x1
    MiniGame_GetTimerValue_L_8012322C:
    lwz r4, g_roundIndex(r13)
    li r0, 0x3
    cmpwi r31, 0x0
    lwz r29, g_ccClass(r13)
    xor r0, r4, r0
    srawi r3, r0, 1
    and r0, r0, r4
    subf r0, r0, r3
    srwi r30, r0, 31
    blt MiniGame_GetTimerValue_L_80123264
    cmpwi r30, 0x0
    blt MiniGame_GetTimerValue_L_80123264
    cmpwi r29, 0x0
    bge MiniGame_GetTimerValue_L_8012326C
    MiniGame_GetTimerValue_L_80123264:
    li r3, 0x0
    b MiniGame_GetTimerValue_L_801232BC
    MiniGame_GetTimerValue_L_8012326C:
    bl IsCardValid
    clrlwi. r0, r3, 24
    bne MiniGame_GetTimerValue_L_8012329C
    mulli r5, r31, 0x18
    lis r4, lbl_803554E0@ha
    slwi r3, r29, 3
    addi r0, r4, lbl_803554E0@l
    add r4, r0, r5
    slwi r0, r30, 2
    add r3, r4, r3
    lwzx r3, r3, r0
    b MiniGame_GetTimerValue_L_801232BC
    MiniGame_GetTimerValue_L_8012329C:
    mulli r5, r31, 0x18
    lis r4, lbl_80355078@ha
    slwi r3, r29, 3
    addi r0, r4, lbl_80355078@l
    add r4, r0, r5
    slwi r0, r30, 2
    add r3, r4, r3
    lwzx r3, r3, r0
    MiniGame_GetTimerValue_L_801232BC:
    lwz r0, 0x24(r1)
    lwz r31, 0x1c(r1)
    lwz r30, 0x18(r1)
    lwz r29, 0x14(r1)
    mtlr r0
    addi r1, r1, 0x20
    blr
}

extern "C" void fn_801232D8(void) {
}

extern "C" void fn_801232DC(void) {
}

extern "C" asm void fn_801232E0(void) { /* 0x801232E0 size:0x19C */
    nofralloc
    stwu r1, -0x80(r1)
    lis r3, lbl_8048DAA8@ha
    lwz r11, lbl_806D6E20(r2)
    stmw r14, 0x38(r1)
    addi r16, r3, lbl_8048DAA8@l
    addi r15, r16, 0x3f8
    lwz r10, lbl_806D6E24(r2)
    addi r4, r16, 0x398
    addi r9, r16, 0x2d0
    addi r8, r16, 0x2f8
    addi r7, r16, 0x320
    addi r6, r16, 0x348
    addi r5, r16, 0x370
    stw r15, 0x34(r1)
    addi r15, r16, 0x430
    lwz r3, lbl_806D6E30(r2)
    addi r14, r16, 0x3c0
    lwz r0, lbl_806D6E34(r2)
    addi r19, r16, 0xc0
    lwz r17, lbl_806D6E18(r2)
    addi r20, r16, 0xf0
    lwz r18, lbl_806D6E1C(r2)
    addi r21, r16, 0x120
    stw r15, 0x28(r1)
    addi r22, r16, 0x150
    addi r15, r16, 0x468
    addi r23, r16, 0x180
    stw r15, 0x2c(r1)
    addi r24, r16, 0x1b0
    addi r15, r16, 0x4a0
    lwz r25, lbl_806D6E28(r2)
    stw r15, 0x30(r1)
    addi r15, r16, 0x4d8
    lwz r26, lbl_806D6E2C(r2)
    addi r27, r16, 0x1e0
    stw r11, 0x20(r4)
    addi r28, r16, 0x208
    addi r29, r16, 0x230
    addi r30, r16, 0x258
    addi r31, r16, 0x280
    addi r12, r16, 0x2a8
    stw r10, 0x24(r4)
    lwz r4, 0x34(r1)
    stw r17, 0x20(r1)
    stw r3, 0x30(r4)
    stw r0, 0x34(r4)
    lwz r4, 0x28(r1)
    stw r18, 0x24(r1)
    stw r3, 0x30(r4)
    stw r0, 0x34(r4)
    lwz r4, 0x2c(r1)
    stw r17, 0x28(r19)
    stw r3, 0x30(r4)
    stw r0, 0x34(r4)
    lwz r4, 0x30(r1)
    stw r18, 0x2c(r19)
    stw r17, 0x28(r20)
    stw r18, 0x2c(r20)
    stw r17, 0x28(r21)
    stw r18, 0x2c(r21)
    stw r17, 0x28(r22)
    stw r18, 0x2c(r22)
    stw r17, 0x28(r23)
    stw r18, 0x2c(r23)
    stw r17, 0x28(r24)
    stw r18, 0x2c(r24)
    stw r25, 0x18(r1)
    stw r26, 0x1c(r1)
    stw r25, 0x20(r27)
    stw r26, 0x24(r27)
    stw r25, 0x20(r28)
    stw r26, 0x24(r28)
    stw r25, 0x20(r29)
    stw r26, 0x24(r29)
    stw r25, 0x20(r30)
    stw r26, 0x24(r30)
    stw r25, 0x20(r31)
    stw r26, 0x24(r31)
    stw r25, 0x20(r12)
    stw r26, 0x24(r12)
    stw r11, 0x10(r1)
    stw r10, 0x14(r1)
    stw r11, 0x20(r9)
    stw r10, 0x24(r9)
    stw r11, 0x20(r8)
    stw r10, 0x24(r8)
    stw r11, 0x20(r7)
    stw r10, 0x24(r7)
    stw r11, 0x20(r6)
    stw r10, 0x24(r6)
    stw r11, 0x20(r5)
    stw r10, 0x24(r5)
    stw r3, 0x8(r1)
    stw r0, 0xc(r1)
    stw r3, 0x30(r14)
    stw r0, 0x34(r14)
    stw r3, 0x30(r4)
    stw r0, 0x34(r4)
    stw r3, 0x30(r15)
    stw r0, 0x34(r15)
    lmw r14, 0x38(r1)
    addi r1, r1, 0x80
    blr
}

extern "C" void fn_8012347C(void) {
}

struct ZoneSrc {
    Vec3 p[4];
    unsigned int flags;
    float top;
    float bottom;
};

struct Zone {
    Zone *next;
    Zone() { next = 0; }
    virtual ~Zone() {
        if (next) {
            delete next;
        }
    }
    virtual unsigned char Contains(const Vec3 *pos);
};

struct BoxZone : Zone {
    unsigned int flags;
    float top;
    float bottom;
    Vec3 origin;
    Vec3 u;
    Vec3 v;
    float lenU;
    float lenV;
    float maxX, maxZ;
    float minX, minZ;
    virtual unsigned char Contains(const Vec3 *pos);
    BoxZone(const ZoneSrc *src);
    virtual ~BoxZone();
};

struct QuadZone : Zone {
    unsigned int flags;
    float top;
    float bottom;
    Vec3 p[4];
    Vec3 n[4];
    float maxX, maxZ;
    float minX, minZ;
    virtual unsigned char Contains(const Vec3 *pos);
    QuadZone(const ZoneSrc *src);
    virtual ~QuadZone();
};

struct ZoneList {
    Zone *head;
    ZoneList(const ZoneSrc *src, int count);
    ~ZoneList();
};

extern "C" int fn_80123480(ZoneList *l, const Vec3 *pos) {
    Zone *z;
    for (z = l->head; z; z = z->next) {
        if (z->Contains(pos)) {
            return 1;
        }
    }
    return 0;
}

extern "C" int fn_801234F0(void) {
    return 0;
}

extern "C" void fn_801235A0(Zone *z, Zone *add);

extern "C" void fn_801234F8(ZoneList *l, const ZoneSrc *src, int count) {
    int i;
    for (i = 0; i < count; i++) {
        Zone *z;
        if (src[i].flags & 4) {
            z = new QuadZone(&src[i]);
        } else {
            z = new BoxZone(&src[i]);
        }
        if (l->head == 0) {
            l->head = z;
        } else {
            fn_801235A0(l->head, z);
        }
    }
}

extern "C" void fn_801235A0(Zone *z, Zone *add) {
    if (z->next) {
        fn_801235A0(z->next, add);
    } else {
        z->next = add;
    }
}

extern "C" asm void fn_80123674(void) { /* 0x80123674 size:0x1FC */
    nofralloc
    stwu r1, -0x10(r1)
    mflr r0
    lis r5, lbl_8048E1B0@ha
    lfs f3, lbl_806D6E50(r2)
    stw r0, 0x14(r1)
    addi r0, r5, lbl_8048E1B0@l
    li r5, 0x0
    stw r31, 0xc(r1)
    mr r31, r4
    lfs f0, 0x34(r31)
    stw r30, 0x8(r1)
    mr r30, r3
    lis r3, lbl_8048E1A0@ha
    lfs f1, 0x38(r31)
    stw r0, 0x4(r30)
    addi r4, r3, lbl_8048E1A0@l
    lwz r0, 0x30(r31)
    addi r3, r30, 0x20
    stw r5, 0x0(r30)
    lfs f5, 0x0(r31)
    stw r4, 0x4(r30)
    lfs f2, 0x4(r31)
    stw r0, 0x8(r30)
    lfs f4, 0x8(r31)
    stfs f0, 0xc(r30)
    lfs f0, 0xc(r31)
    stfs f1, 0x10(r30)
    fsubs f1, f0, f5
    lfs f0, 0x14(r31)
    stfs f5, 0x14(r30)
    stfs f2, 0x18(r30)
    fsubs f2, f0, f4
    lfs f0, 0x24(r31)
    stfs f4, 0x1c(r30)
    stfs f1, 0x20(r30)
    fsubs f1, f0, f5
    lfs f0, 0x2c(r31)
    stfs f3, 0x24(r30)
    fsubs f0, f0, f4
    stfs f2, 0x28(r30)
    stfs f1, 0x2c(r30)
    stfs f3, 0x30(r30)
    stfs f0, 0x34(r30)
    bl Vec3_Magnitude
    stfs f1, 0x38(r30)
    addi r3, r30, 0x2c
    bl Vec3_Magnitude
    addi r3, r30, 0x20
    stfs f1, 0x3c(r30)
    mr r4, r3
    bl Vec3_Normalize
    addi r3, r30, 0x2c
    mr r4, r3
    bl Vec3_Normalize
    lfs f1, 0x0(r31)
    lfs f0, 0x8(r31)
    stfs f1, 0x40(r30)
    lfs f2, 0xc(r31)
    stfs f1, 0x48(r30)
    stfs f0, 0x44(r30)
    stfs f0, 0x4c(r30)
    lfs f0, 0x48(r30)
    fcmpo cr0, f2, f0
    bge fn_80123674_L_80123778
    stfs f2, 0x48(r30)
    fn_80123674_L_80123778:
    lfs f1, 0xc(r31)
    lfs f0, 0x40(r30)
    fcmpo cr0, f1, f0
    ble fn_80123674_L_8012378C
    stfs f1, 0x40(r30)
    fn_80123674_L_8012378C:
    lfs f1, 0x14(r31)
    lfs f0, 0x4c(r30)
    fcmpo cr0, f1, f0
    bge fn_80123674_L_801237A0
    stfs f1, 0x4c(r30)
    fn_80123674_L_801237A0:
    lfs f1, 0x14(r31)
    lfs f0, 0x44(r30)
    fcmpo cr0, f1, f0
    ble fn_80123674_L_801237B4
    stfs f1, 0x44(r30)
    fn_80123674_L_801237B4:
    lfs f1, 0x18(r31)
    lfs f0, 0x48(r30)
    fcmpo cr0, f1, f0
    bge fn_80123674_L_801237C8
    stfs f1, 0x48(r30)
    fn_80123674_L_801237C8:
    lfs f1, 0x18(r31)
    lfs f0, 0x40(r30)
    fcmpo cr0, f1, f0
    ble fn_80123674_L_801237DC
    stfs f1, 0x40(r30)
    fn_80123674_L_801237DC:
    lfs f1, 0x20(r31)
    lfs f0, 0x4c(r30)
    fcmpo cr0, f1, f0
    bge fn_80123674_L_801237F0
    stfs f1, 0x4c(r30)
    fn_80123674_L_801237F0:
    lfs f1, 0x20(r31)
    lfs f0, 0x44(r30)
    fcmpo cr0, f1, f0
    ble fn_80123674_L_80123804
    stfs f1, 0x44(r30)
    fn_80123674_L_80123804:
    lfs f1, 0x24(r31)
    lfs f0, 0x48(r30)
    fcmpo cr0, f1, f0
    bge fn_80123674_L_80123818
    stfs f1, 0x48(r30)
    fn_80123674_L_80123818:
    lfs f1, 0x24(r31)
    lfs f0, 0x40(r30)
    fcmpo cr0, f1, f0
    ble fn_80123674_L_8012382C
    stfs f1, 0x40(r30)
    fn_80123674_L_8012382C:
    lfs f1, 0x2c(r31)
    lfs f0, 0x4c(r30)
    fcmpo cr0, f1, f0
    bge fn_80123674_L_80123840
    stfs f1, 0x4c(r30)
    fn_80123674_L_80123840:
    lfs f1, 0x2c(r31)
    lfs f0, 0x44(r30)
    fcmpo cr0, f1, f0
    ble fn_80123674_L_80123854
    stfs f1, 0x44(r30)
    fn_80123674_L_80123854:
    lwz r0, 0x14(r1)
    mr r3, r30
    lwz r31, 0xc(r1)
    lwz r30, 0x8(r1)
    mtlr r0
    addi r1, r1, 0x10
    blr
}


extern "C" Zone *dtor_80123870(Zone *z, short flag) {
    if (z) {
        *(void **)((char *)z + 4) = lbl_8048E1B0;
        if (z->next) {
            delete z->next;
        }
        if (flag > 0) {
            operator delete(z);
        }
    }
    return z;
}

extern "C" asm void fn_801238EC(void) { /* 0x801238EC size:0x25C */
    nofralloc
    stwu r1, -0x30(r1)
    mflr r0
    lis r7, lbl_8048E1B0@ha
    li r6, 0x0
    stw r0, 0x34(r1)
    addi r0, r7, lbl_8048E1B0@l
    lis r5, lbl_8048E184@ha
    lfs f1, 0x34(r4)
    stw r31, 0x2c(r1)
    mr r31, r3
    addi r3, r5, lbl_8048E184@l
    lfs f0, 0x38(r4)
    stw r30, 0x28(r1)
    stw r29, 0x24(r1)
    stw r0, 0x4(r31)
    lwz r0, 0x30(r4)
    stw r6, 0x0(r31)
    stw r3, 0x4(r31)
    stw r0, 0x8(r31)
    stfs f1, 0xc(r31)
    stfs f0, 0x10(r31)
    lwz r0, 0x8(r31)
    rlwinm. r0, r0, 0, 28, 28
    beq fn_801238EC_L_801239B0
    lfs f1, 0x24(r4)
    lfs f0, 0x28(r4)
    stfs f1, 0x14(r31)
    lfs f1, 0x2c(r4)
    stfs f0, 0x18(r31)
    lfs f0, 0x18(r4)
    stfs f1, 0x1c(r31)
    lfs f1, 0x1c(r4)
    stfs f0, 0x20(r31)
    lfs f0, 0x20(r4)
    stfs f1, 0x24(r31)
    lfs f1, 0xc(r4)
    stfs f0, 0x28(r31)
    lfs f0, 0x10(r4)
    stfs f1, 0x2c(r31)
    lfs f1, 0x14(r4)
    stfs f0, 0x30(r31)
    lfs f0, 0x0(r4)
    stfs f1, 0x34(r31)
    lfs f1, 0x4(r4)
    stfs f0, 0x38(r31)
    lfs f0, 0x8(r4)
    stfs f1, 0x3c(r31)
    stfs f0, 0x40(r31)
    b fn_801238EC_L_80123A10
    fn_801238EC_L_801239B0:
    lfs f1, 0x0(r4)
    lfs f0, 0x4(r4)
    stfs f1, 0x14(r31)
    lfs f1, 0x8(r4)
    stfs f0, 0x18(r31)
    lfs f0, 0xc(r4)
    stfs f1, 0x1c(r31)
    lfs f1, 0x10(r4)
    stfs f0, 0x20(r31)
    lfs f0, 0x14(r4)
    stfs f1, 0x24(r31)
    lfs f1, 0x18(r4)
    stfs f0, 0x28(r31)
    lfs f0, 0x1c(r4)
    stfs f1, 0x2c(r31)
    lfs f1, 0x20(r4)
    stfs f0, 0x30(r31)
    lfs f0, 0x24(r4)
    stfs f1, 0x34(r31)
    lfs f1, 0x28(r4)
    stfs f0, 0x38(r31)
    lfs f0, 0x2c(r4)
    stfs f1, 0x3c(r31)
    stfs f0, 0x40(r31)
    fn_801238EC_L_80123A10:
    lfs f0, lbl_806D6E50(r2)
    li r29, 0x0
    li r30, 0x0
    stfs f0, 0x18(r31)
    stfs f0, 0x24(r31)
    stfs f0, 0x30(r31)
    stfs f0, 0x3c(r31)
    fn_801238EC_L_80123A2C:
    addi r3, r29, 0x1
    cmpwi r3, 0x4
    blt fn_801238EC_L_80123A3C
    subi r3, r3, 0x4
    fn_801238EC_L_80123A3C:
    mulli r3, r3, 0xc
    addi r4, r30, 0x14
    addi r5, r1, 0x8
    add r4, r31, r4
    addi r3, r3, 0x14
    add r3, r31, r3
    bl Vec3_Subtract
    lfs f0, 0x10(r1)
    addi r6, r30, 0x44
    add r3, r31, r6
    addi r5, r30, 0x48
    fneg f0, f0
    addi r0, r30, 0x4c
    mr r4, r3
    stfsx f0, r31, r6
    lfs f0, 0xc(r1)
    stfsx f0, r31, r5
    lfs f0, 0x8(r1)
    stfsx f0, r31, r0
    bl Vec3_Normalize
    cmpwi r29, 0x0
    bne fn_801238EC_L_80123AB8
    addi r3, r30, 0x14
    addi r0, r30, 0x1c
    lfsx f0, r31, r3
    stfs f0, 0x74(r31)
    stfs f0, 0x7c(r31)
    lfsx f0, r31, r0
    stfs f0, 0x78(r31)
    stfs f0, 0x80(r31)
    b fn_801238EC_L_80123B18
    fn_801238EC_L_80123AB8:
    addi r0, r30, 0x14
    lfs f0, 0x7c(r31)
    lfsx f1, r31, r0
    fcmpo cr0, f1, f0
    bge fn_801238EC_L_80123AD0
    stfs f1, 0x7c(r31)
    fn_801238EC_L_80123AD0:
    addi r0, r30, 0x14
    lfs f0, 0x74(r31)
    lfsx f1, r31, r0
    fcmpo cr0, f1, f0
    ble fn_801238EC_L_80123AE8
    stfs f1, 0x74(r31)
    fn_801238EC_L_80123AE8:
    addi r0, r30, 0x1c
    lfs f0, 0x80(r31)
    lfsx f1, r31, r0
    fcmpo cr0, f1, f0
    bge fn_801238EC_L_80123B00
    stfs f1, 0x80(r31)
    fn_801238EC_L_80123B00:
    addi r0, r30, 0x1c
    lfs f0, 0x78(r31)
    lfsx f1, r31, r0
    fcmpo cr0, f1, f0
    ble fn_801238EC_L_80123B18
    stfs f1, 0x78(r31)
    fn_801238EC_L_80123B18:
    addi r29, r29, 0x1
    addi r30, r30, 0xc
    cmpwi r29, 0x4
    blt fn_801238EC_L_80123A2C
    lwz r0, 0x34(r1)
    mr r3, r31
    lwz r31, 0x2c(r1)
    lwz r30, 0x28(r1)
    lwz r29, 0x24(r1)
    mtlr r0
    addi r1, r1, 0x30
    blr
}

ZoneList::~ZoneList() {
    delete head;
}

ZoneList::ZoneList(const ZoneSrc *src, int count) {
    head = 0;
    fn_801234F8(this, src, count);
}

QuadZone::~QuadZone() {
}

extern "C" int fn_80123C78(QuadZone *q, const Vec3 *pos) {
    Vec3 d;
    int i;
    if (pos->x < q->minX || pos->x > q->maxX || pos->z < q->minZ || pos->z > q->maxZ) {
        return 0;
    }
    if ((q->flags & 1) && pos->y > q->top) {
        return 0;
    }
    if ((q->flags & 2) && pos->y < q->bottom) {
        return 0;
    }
    for (i = 0; i < 4; i++) {
        Vec3_Subtract(pos, &q->p[i], &d);
        if (Vec3_Dot(&q->n[i], &d) < lbl_806D6E50) {
            return 0;
        }
    }
    return 1;
}

BoxZone::~BoxZone() {
}

extern "C" int fn_80123E1C(BoxZone *b, const Vec3 *pos) {
    Vec3 d;
    float t;
    if (pos->x < b->minX || pos->x > b->maxX || pos->z < b->minZ || pos->z > b->maxZ) {
        return 0;
    }
    if ((b->flags & 1) && pos->y > b->top) {
        return 0;
    }
    if ((b->flags & 2) && pos->y < b->bottom) {
        return 0;
    }
    Vec3_Subtract(pos, &b->origin, &d);
    t = Vec3_Dot(&b->u, &d);
    if (t < lbl_806D6E50 || t > b->lenU) {
        return 0;
    }
    t = Vec3_Dot(&b->v, &d);
    if (t < lbl_806D6E50 || t > b->lenV) {
        return 0;
    }
    return 1;
}

struct ModeTaskBase {
    virtual ~ModeTaskBase();
    virtual void Finish();
    virtual void Update();
    virtual void Draw();
};

struct ModeTask : ModeTaskBase {
    unsigned char done;
};

struct GameModeBase {
    GameModeBase();
    virtual ~GameModeBase();
};

struct TaskMode : GameModeBase {
    ModeTask *task;
    virtual void key();
    TaskMode() { task = (ModeTask *)fn_8014F6A4(); }
    ~TaskMode();
};

extern "C" void fn_80123F34(TaskMode *m) {
    if (m->task) {
        m->task->Draw();
    }
}

extern "C" int fn_80123F6C(TaskMode *m) {
    if (m->task) {
        if (m->task->done) {
            m->task->Finish();
            m->task = 0;
        } else {
            m->task->Update();
        }
    }
    return -2;
}

TaskMode::~TaskMode() {
    if (task) {
        task->Finish();
        task = 0;
    }
}

extern "C" TaskMode *fn_80124064(void) {
    return new TaskMode;
}

__declspec(section ".ctors") static void *const fn_801232E0_ctor_ref = (void *)fn_801232E0;
