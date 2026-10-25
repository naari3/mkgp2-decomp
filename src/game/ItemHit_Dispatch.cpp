/* ItemHit_Dispatch (0x800DCA70): deliver an item hit to the kart it touched
 * (explicit kart, or the one in the item's hit-registry slot), show the hit
 * message, work out the impact point and spawn the hit effect there.
 * C++ for the virtual-call sequence on the kart's hit sink (vtable +0x8). */
typedef struct Vec { float x, y, z; } Vec;

typedef struct ItemClassEntry {
    unsigned char pad0[8];
    float radius;
    signed char hasJoint;
    unsigned char padD[3];
    const char *joint;
} ItemClassEntry;

typedef struct ItemKindEntry {
    unsigned char pad0[0x10];
    unsigned char effect;
    unsigned char pad11[3];
} ItemKindEntry;

typedef struct ItemObjectCopy {
    unsigned char b[0x1EC];
} ItemObjectCopy;

struct KartHitSink {
    virtual unsigned char onHit(void *item, int arg); /* vtable +0x8 */
};

extern "C" {
extern ItemClassEntry lbl_8041AC24[];
extern ItemKindEntry lbl_8041CBA8[];
extern unsigned char lbl_805DF3D0[];
extern unsigned char g_finalLapCoinJumpEnabled;

extern void *GetRaceContextPtr(void);
extern unsigned char *RaceContextSlot_GetIfAlive(void *ctx, int idx);
extern short ItemAlias_HitRemapLookup(int id);
extern int ItemAlias_SourceToDest(unsigned char id);
extern void *memcpy(void *dst, const void *src, unsigned long n);
extern void HitMessageOverlay_Show(void *owner, void *kart, int flag);
extern void fn_8023D21C(void *kart, int kind, unsigned char cls);
extern void *KartDriver_GetKartRootMtx(void *kart);
extern void *KartDriver_GetJointByIdx(void *kart, int idx);
extern void Mtx44_GetTranslation_RowMajor(Vec *dst, void *mtx);
extern int JointByName_GetWorldPosition(Vec *out, void *slot, const char *name);
extern void Vec3_Copy(void *dst, const void *src);
extern void Vec3_Subtract_DestFirst(Vec *dst, const Vec *a, const Vec *b);
extern void Vec3_Add_DestFirst(Vec *dst, const Vec *a, const Vec *b);
extern float Vec3_Magnitude_Wrapper(const Vec *v);
extern float Vec3_HorizontalMagnitude(const Vec *v);
extern void Vec3_Scale(Vec *dst, const Vec *src, float s);
extern void Vec3_ScaleXZ(Vec *dst, const Vec *src, float s);
extern unsigned char *DrawEffect_SpawnByType(int type);
}

#define F(o) (*(float *)(self + (o)))
#define S8(o) (*(signed char *)(self + (o)))
#define P(o) (*(unsigned char **)(self + (o)))
#define KIND (*(int *)(self + 0x8))

static inline unsigned char *ItemHit_GetContactKart(unsigned char *self)
{
    int slot;

    if (self == 0) {
        return 0;
    }
    if (S8(0x174) == 0) {
        return 0;
    }
    slot = *(int *)(self + 0x170);
    if (slot == -1) {
        return 0;
    }
    return *(unsigned char **)(RaceContextSlot_GetIfAlive(GetRaceContextPtr(), slot) + 0xB8);
}

static inline int Kart_HasCoinJumpSlot(unsigned char *kart)
{
    if (kart == 0) {
        return 0;
    }
    if (*(int *)(kart + 0x238) != 0) {
        return 1;
    }
    return 0;
}

static inline unsigned char Kart_IsFinalLapCoinJump(unsigned char *kart)
{
    if (kart == 0) {
        return 0;
    }
    if (Kart_HasCoinJumpSlot(kart)) {
        if (g_finalLapCoinJumpEnabled) {
            return 1;
        }
        return 0;
    }
    return 0;
}

extern "C" void ItemHit_Dispatch(unsigned char *self, signed char kind, Vec *pos, unsigned char *kart)
{
    ItemObjectCopy copy;
    Vec out;
    Vec kp;
    Vec jp;
    Vec d;
    Vec kp2;
    Vec d2;
    unsigned char *target;
    int hit;
    unsigned char alias;
    int flag;
    float r;
    float m;
    float s;
    float scale;
    unsigned char *e;

    if (self == 0) {
        return;
    }
    target = 0;
    if (kart != 0) {
        target = kart;
    } else if (*(int *)(self + 0x170) != -1) {
        target = ItemHit_GetContactKart(self);
    }
    if (target == 0) {
        return;
    }
    if (S8(0x1DC) == 0) {
        hit = (*(KartHitSink **)(target + 0x308))->onHit(self, -1);
    } else {
        alias = ItemAlias_SourceToDest(ItemAlias_HitRemapLookup(KIND));
        if (KIND == 0x63) {
            alias = 0x14;
        }
        memcpy(&copy, self, 0x1EC);
        *(int *)(copy.b + 0x8) = alias;
        if (*(int *)(self + 0x1E0) != 0 && *(int *)(self + 0x1E0) != 0xFF) {
            *(int *)(copy.b + 0x8) = *(int *)(self + 0x1E0);
            copy.b[0x1DC] = 1;
        }
        hit = (*(KartHitSink **)(target + 0x308))->onHit(&copy, -1);
    }
    if (hit) {
        flag = 1;
        if (KIND == 0x52 || KIND == 0x53) {
            flag = 0;
        }
        HitMessageOverlay_Show(P(0x184), target, flag);
        fn_8023D21C(target, KIND, self[0x1C]);
    }
    if (pos == 0) {
        Mtx44_GetTranslation_RowMajor(&kp, KartDriver_GetKartRootMtx(target));
        if (lbl_8041AC24[self[0x1C]].hasJoint) {
            if (!JointByName_GetWorldPosition(&jp, self + 0x14, lbl_8041AC24[self[0x1C]].joint)) {
                Vec3_Copy(&jp, self + 0xA0);
            }
        } else {
            Vec3_Copy(&jp, self + 0xA0);
        }
        r = F(0xC4) * lbl_8041AC24[self[0x1C]].radius;
        if (r < 0.0f) {
            r = 1.0f;
        }
        Vec3_Subtract_DestFirst(&d, &kp, &jp);
        m = Vec3_Magnitude_Wrapper(&d);
        if (m < r) {
            Vec3_Scale(&d, &d, (1.0f / m) * r);
            Vec3_Add_DestFirst(&out, &jp, &d);
        } else {
            Vec3_Scale(&d, &d, (1.0f / m) * r);
            Vec3_Add_DestFirst(&out, &jp, &d);
        }
    } else {
        Vec3_Copy(&out, pos);
    }
    if (target != 0) {
        Mtx44_GetTranslation_RowMajor(&kp2, KartDriver_GetKartRootMtx(target));
        kp2.y += 5.0f;
        Vec3_Subtract_DestFirst(&d2, &out, &kp2);
        m = Vec3_HorizontalMagnitude(&d2);
        switch (*(unsigned int *)(target + 0x1F8)) {
        case 0:
            s = 1.0f;
            break;
        case 1:
            s = 1.0f;
            break;
        case 2:
            s = 1.1f;
            break;
        case 3:
            s = 1.0f;
            break;
        case 4:
            s = 1.2f;
            break;
        case 5:
            s = 1.0f;
            break;
        case 6:
            s = 1.2f;
            break;
        case 7:
            s = 1.0f;
            break;
        case 8:
            s = 1.0f;
            break;
        case 9:
            s = 1.0f;
            break;
        case 10:
            s = 1.0f;
            break;
        case 11:
            s = 1.0f;
            break;
        case 12:
            s = 1.0f;
            break;
        default:
            s = 1.0f;
            break;
        }
        scale = 10.0f * s;
        Vec3_ScaleXZ(&d2, &d2, (1.0f / m) * scale);
        Vec3_Add_DestFirst(&out, &kp2, &d2);
        Mtx44_GetTranslation_RowMajor(&kp2, KartDriver_GetJointByIdx(target, 0xD));
        Vec3_Subtract_DestFirst(&d2, (Vec *)(lbl_805DF3D0 + 0x80), &kp2);
        m = Vec3_Magnitude_Wrapper(&d2);
        Vec3_Scale(&d2, &d2, scale * (1.0f / m));
        Vec3_Add_DestFirst(&out, &kp2, &d2);
    }
    if (Kart_IsFinalLapCoinJump(target)) {
        return;
    }
    if (kind != 0) {
        return;
    }
    e = 0;
    switch (lbl_8041CBA8[KIND].effect) {
    case 2:
        e = DrawEffect_SpawnByType(2);
        break;
    case 3:
        e = DrawEffect_SpawnByType(3);
        break;
    case 4:
        e = DrawEffect_SpawnByType(4);
        break;
    }
    if (e != 0) {
        Vec3_Copy(e + 0x8C, &out);
        *(unsigned char **)(e + 0x11C) = target;
    }
}
