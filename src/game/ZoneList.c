#include "game/types/c_region.h"
C_REGION_BEGIN
/*
 * Mini-game helpers: the per-cup timer lookup and the trigger-zone lists
 * (box and quad zones chained through `next`, vtable at +4) plus a small
 * game-mode wrapper clAttract. The zone classes keep undefined key
 * virtuals; clAttract owns its compiler-emitted vtable and RTTI.
 *
 * Built with GC/2.7: the zone ctors schedule src loads across the stores
 * to `this`, which GC/1.3.2 never does.
 *
 * Still asm: the colour table init (dynamic init of tables this unit does
 * not own).
 */
#include "game/types/size_t.h"
C_REGION_END
#pragma cplusplus on

#include "game/types/Vec3.h"

extern "C" {
extern int g_cupId;
extern int g_roundIndex;
extern int g_ccClass;
extern int MiniGame_GetTimerValue_rodata_80355078[][3][2];
extern int MiniGame_GetTimerValue_rodata_803554E0[][3][2];
extern char QuadZone_vtable_8048E184[];
extern char BoxZone_vtable_8048E1A0[];
extern char Zone_vtable_8048E1B0[];
extern const float lbl_806D6E50;
extern unsigned char IsCardValid(void);
extern float Vec3_Magnitude(const Vec3 *v);
extern void Vec3_Normalize(const Vec3 *in, Vec3 *out);
extern void Vec3_Subtract(const Vec3 *a, const Vec3 *b, Vec3 *out);
extern float Vec3_Dot(const Vec3 *a, const Vec3 *b);
extern void *fn_8014F6A4(void);
}


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
#ifdef NON_MATCHING
void fn_801232E0(void);
#else
void fn_801232E0(void);
#endif

#pragma section R ".extab_user"
__declspec(section ".extab_user") static const unsigned char extab_fn_801232E0[8] = {
    0x90, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};



#pragma section R ".extabindex_user"
__declspec(section ".extabindex_user") static const struct { void *fn; unsigned int fn_size; void *extab; } extabindex_fn_801232E0 = {
    (void *)&fn_801232E0, 0x0000019C, (void *)extab_fn_801232E0
};



}


void *operator new(size_t size);

void operator delete(void *p);

extern "C" int IsUraCourseFromSubMode(void) {
    return g_roundIndex > 3 ? 1 : 0;
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

extern "C" int MiniGame_GetTimerValue(void) {
    int cup = CupIndex();
    int ura = IsUraCourseFromSubMode();
    int cc = g_ccClass;
    if (cup < 0 || ura < 0 || cc < 0) {
        return 0;
    }
    if (IsCardValid() == 0) {
        return MiniGame_GetTimerValue_rodata_803554E0[cup][cc][ura];
    }
    return MiniGame_GetTimerValue_rodata_80355078[cup][cc][ura];
}

extern "C" void fn_801232D8(void) {
}

extern "C" void fn_801232DC(void) {
}

#ifdef NON_MATCHING
/*
 * Equivalent C for the PC port (docs/nonmatching_c.md). Dynamic initializer
 * of 24 {int,int} tables that follow the 0xC0-byte pointer table at
 * lbl_8048DAA8: it writes the terminating pair of each table from four
 * constant {-1,-1}-style end markers in .sdata2 (see docs/gave_up.md for the
 * original shape: `Pair tbl[N] = { ..., kEndX };`).
 */
static void ZoneList_SetEnd(unsigned int base, unsigned int pairOff, unsigned int a, unsigned int b) {
    unsigned int *p = (unsigned int *)((char *)lbl_8048DAA8 + base + pairOff);
    p[0] = a;
    p[1] = b;
}

extern "C" void fn_801232E0(void) {
    int i;
    for (i = 0; i < 6; i++) {
        ZoneList_SetEnd(0x0C0 + i * 0x30, 0x28, lbl_806D6E18, lbl_806D6E1C);
        ZoneList_SetEnd(0x1E0 + i * 0x28, 0x20, lbl_806D6E28, lbl_806D6E2C);
        ZoneList_SetEnd(0x2D0 + i * 0x28, 0x20, lbl_806D6E20, lbl_806D6E24);
        ZoneList_SetEnd(0x3C0 + i * 0x38, 0x30, lbl_806D6E30, lbl_806D6E34);
    }
}
#else
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
#endif

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

static inline void BoxZone_Extend(BoxZone *z, const Vec3 *p) {
    if (p->x < z->minX) {
        z->minX = p->x;
    }
    if (p->x > z->maxX) {
        z->maxX = p->x;
    }
    if (p->z < z->minZ) {
        z->minZ = p->z;
    }
    if (p->z > z->maxZ) {
        z->maxZ = p->z;
    }
}

BoxZone::BoxZone(const ZoneSrc *src) {
    flags = src->flags;
    top = src->top;
    bottom = src->bottom;
    origin = src->p[0];
    u.x = src->p[1].x - src->p[0].x;
    u.y = lbl_806D6E50;
    u.z = src->p[1].z - src->p[0].z;
    v.x = src->p[3].x - src->p[0].x;
    v.y = lbl_806D6E50;
    v.z = src->p[3].z - src->p[0].z;
    lenU = Vec3_Magnitude(&u);
    lenV = Vec3_Magnitude(&v);
    Vec3_Normalize(&u, &u);
    Vec3_Normalize(&v, &v);
    minX = maxX = src->p[0].x;
    minZ = maxZ = src->p[0].z;
    BoxZone_Extend(this, &src->p[1]);
    BoxZone_Extend(this, &src->p[2]);
    BoxZone_Extend(this, &src->p[3]);
}


/* dtor_80123870 is Zone::~Zone (emitted here for the ctors' cleanup). */

QuadZone::QuadZone(const ZoneSrc *src) {
    flags = src->flags;
    top = src->top;
    bottom = src->bottom;
    if (flags & 8) {
        p[0] = src->p[3];
        p[1] = src->p[2];
        p[2] = src->p[1];
        p[3] = src->p[0];
    } else {
        p[0] = src->p[0];
        p[1] = src->p[1];
        p[2] = src->p[2];
        p[3] = src->p[3];
    }
    p[0].y = lbl_806D6E50;
    p[1].y = lbl_806D6E50;
    p[2].y = lbl_806D6E50;
    p[3].y = lbl_806D6E50;
    for (int i = 0; i < 4; i++) {
        Vec3 d;
        int j = i + 1;
        if (j >= 4) {
            j -= 4;
        }
        Vec3_Subtract(&p[j], &p[i], &d);
        n[i].x = -d.z;
        n[i].y = d.y;
        n[i].z = d.x;
        Vec3_Normalize(&n[i], &n[i]);
        if (i == 0) {
            minX = maxX = p[i].x;
            minZ = maxZ = p[i].z;
        } else {
            if (p[i].x < minX) {
                minX = p[i].x;
            }
            if (p[i].x > maxX) {
                maxX = p[i].x;
            }
            if (p[i].z < minZ) {
                minZ = p[i].z;
            }
            if (p[i].z > maxZ) {
                maxZ = p[i].z;
            }
        }
    }
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

extern "C" int fn_80123E1C(BoxZone *b, Vec3 *pos) {
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

#include "game/types/clJobRunner.h"

struct clAttract : clJobRunner {
    ModeTask *task;
    clAttract() { task = (ModeTask *)fn_8014F6A4(); }
    virtual int Update();
    virtual void Draw();
    virtual ~clAttract();
};

void clAttract::Draw() {
    if (task) {
        task->Draw();
    }
}

int clAttract::Update() {
    if (task) {
        if (task->done) {
            task->Finish();
            task = 0;
        } else {
            task->Update();
        }
    }
    return -2;
}

clAttract::~clAttract() {
    if (task) {
        task->Finish();
        task = 0;
    }
}

extern "C" clAttract *fn_80124064(void) {
    return new clAttract;
}

__declspec(section ".ctors") static void *const fn_801232E0_ctor_ref = (void *)fn_801232E0;
