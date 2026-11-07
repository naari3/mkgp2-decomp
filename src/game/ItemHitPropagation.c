typedef struct HitVec3 { float x, y, z; } HitVec3;
typedef struct HitMtx44 { float m[16]; } HitMtx44;
typedef struct HitEffectBus {
    unsigned char pad_00[0x10];
    unsigned long long flags;
} HitEffectBus;
typedef struct HitDriver {
    unsigned char pad_00[0x304];
    HitEffectBus *effects;
} HitDriver;
typedef struct HitRaceSlot {
    int kind;
    unsigned char pad_04[0xB0];
    HitDriver *driver;
} HitRaceSlot;
typedef struct HitItem {
    unsigned char pad_00[0x1C];
    unsigned char kind;
    unsigned char pad_1D[0x83];
    HitVec3 position;
    unsigned char pad_AC[0x18];
    float radiusScale;
} HitItem;
typedef struct HitDescriptor {
    unsigned char pad_00[8];
    float radius;
    unsigned char pad_0C[8];
} HitDescriptor;

extern void *GetRaceContextPtr(void);
extern HitRaceSlot *RaceContextSlot_GetIfAlive(void *context, int index);
extern void ItemHit_Dispatch(HitItem *item, signed char mode,
                             const HitVec3 *position, HitDriver *driver);
extern void ItemEffectBus_OrMask(HitEffectBus *effects, unsigned long long mask);
extern const void *KartDriver_GetKartRootMtx(HitDriver *driver);
extern void Mtx_TransposeToMtx44(HitMtx44 *dest, const void *source);
extern void Mtx44_TransformVec3(HitVec3 *dest, const HitMtx44 *matrix,
                              const HitVec3 *source);
extern float fn_800D3184(const HitVec3 *a, const HitVec3 *b);
extern HitDescriptor lbl_8041AC24[];
extern const HitVec3 lbl_8032DDF4;
extern const float lbl_806D5B24;

/* Private layout views expose only fields read here and by the callees.
 * The slot kind predicate is an unsigned 0..3 range plus kind 6, as in
 * the target. The classifier mirrors KartItem_QueryEffectStateFromIse.
 * Classification uses a const view; this preserves the target effect-bus
 * reload and classifier register lifetimes. The TU remains NonMatching
 * because each dispatch switch omits the target's duplicate exit branch.
 */
static inline unsigned char HitEffect_HasProtected(const HitEffectBus *effects)
{
    unsigned char result;
    if ((effects->flags & 0x0080000000000000ULL) == 0) {
        result = 0;
    } else {
        result = 1;
    }
    return result;
}

static inline int HitDriver_Classify(const HitDriver *driver)
{
    const HitEffectBus *effects = driver->effects;
    if (HitEffect_HasProtected(effects)) {
        return 2;
    }
    if ((effects->flags & 0x0100000000000000ULL) != 0) {
        return 2;
    }
    if ((effects->flags & 0x40ULL) != 0) {
        return 2;
    }
    if ((effects->flags & 0x400ULL) != 0) {
        return 3;
    }
    if ((effects->flags & 0x80ULL) != 0) {
        return 5;
    }
    return 1;
}

void Item_PropagateHitToAllDrivers(HitItem *item, HitDriver *excluded)
{
    int i;
    for (i = 0; i < 128; i++) {
        HitRaceSlot *slot = RaceContextSlot_GetIfAlive(GetRaceContextPtr(), i);
        HitDriver *driver;
        int classification;
        if (slot == 0) {
            continue;
        }
        if ((unsigned int)slot->kind <= 3 || slot->kind == 6) {
            driver = slot->driver;
            if (excluded != 0 && excluded == driver) {
                continue;
            }
            classification = HitDriver_Classify(driver);
            switch (classification) {
            case 1:
                ItemHit_Dispatch(item, 0, &item->position, driver);
                break;
            case 2:
                if (driver->effects != 0) {
                    ItemEffectBus_OrMask(driver->effects, 0x8000000000000000ULL);
                }
                break;
            default:
                break;
            }
        }
    }
}

void Item_PropagateHitToDriversInRadius(HitItem *item, HitDriver *excluded)
{
    int i;
    HitDriver *driver;
    HitMtx44 matrix;
    HitVec3 position;
    HitVec3 origin;
    float radius;
    if (item == 0) {
        return;
    }
    radius = item->radiusScale * lbl_8041AC24[item->kind].radius;
    radius = lbl_806D5B24 + radius;
    for (i = 0; i < 128; i++) {
        HitRaceSlot *slot = RaceContextSlot_GetIfAlive(GetRaceContextPtr(), i);
        int classification;
        if (slot == 0) {
            continue;
        }
        if ((unsigned int)slot->kind <= 3 || slot->kind == 6) {
            driver = slot->driver;
            if (excluded != 0 && excluded == driver) {
                continue;
            }
            Mtx_TransposeToMtx44(&matrix, KartDriver_GetKartRootMtx(driver));
            position = lbl_8032DDF4;
            origin = position;
            Mtx44_TransformVec3(&position, &matrix, &origin);
            if (fn_800D3184(&item->position, &position) < radius) {
                classification = HitDriver_Classify(driver);
                switch (classification) {
                case 1:
                    ItemHit_Dispatch(item, 0, &position, driver);
                    break;
                case 2:
                    if (driver->effects != 0) {
                        ItemEffectBus_OrMask(driver->effects, 0x8000000000000000ULL);
                    }
                    break;
                default:
                    break;
                }
            }
        }
    }
}
