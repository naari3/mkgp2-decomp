/* ItemObjectManager_TickActiveItems (0x800D85B8): per-frame update of the
 * 256 item objects: run each live item's tick callbacks and sprite anim,
 * refresh its world position (optionally from a named joint) and collision
 * radius, then test every live pair once for item/item or item/kart hits. */

typedef struct ItemVec3 {
    float x, y, z;
} ItemVec3;

typedef struct ItemDescriptor {
    unsigned char pad00[0x8];
    float radius;           /* 0x08 */
    signed char hasJoint;   /* 0x0C */
    unsigned char pad0D[0x3];
    void *joint;            /* 0x10 */
} ItemDescriptor;

typedef struct ItemObject ItemObject;
typedef void (*ItemObjectFn)(ItemObject *item);

struct ItemObject {
    signed char active;     /* 0x000 */
    unsigned char pad001[0x3];
    ItemObjectFn tick;      /* 0x004 */
    int type;               /* 0x008 */
    unsigned char pad00C[0x8];
    unsigned char sprite;   /* 0x014: SpriteSlot (flags byte first) */
    unsigned char pad015[0x7];
    unsigned char kind;     /* 0x01C */
    unsigned char pad01D[0x6F];
    signed char category;   /* 0x08C */
    signed char hitState;   /* 0x08D */
    unsigned char pad08E[0x12];
    ItemVec3 basePos;       /* 0x0A0 */
    unsigned char pad0AC[0x18];
    float radiusScale;      /* 0x0C4 */
    unsigned char pad0C8[0x4];
    ItemVec3 pos;           /* 0x0CC */
    float radius;           /* 0x0D8 */
    unsigned char pad0DC[0x4];
    ItemObjectFn postTick;  /* 0x0E0 */
    ItemObject *owner;      /* 0x0E4 */
    unsigned char pad0E8[0x1EC - 0xE8];
};

typedef struct ItemObjectManager {
    ItemObject items[256];
    unsigned char pad1EC00[0x4];
    int frame;              /* 0x1EC04 */
} ItemObjectManager;

extern void ItemHitRegistry_PruneStale(void);
extern void ItemObject_CheckKartCollision(ItemObject *kart, ItemObject *other);
extern void ItemObject_CheckPairCollision(ItemObject *a, ItemObject *b);
extern int JointByName_GetWorldPosition(ItemVec3 *out, void *sprite, void *joint);
extern void SpriteSlot_TickAnim(void *sprite);
extern void Vec3_Copy(ItemVec3 *dst, const ItemVec3 *src);

extern ItemDescriptor g_itemDescriptorTable[];

#pragma use_lmw_stmw on
void ItemObjectManager_TickActiveItems(ItemObjectManager *m)
{
    ItemObject *a;
    ItemObject *b;
    int i;
    int j;

    for (i = 0; i < 256; i++) {
        a = &m->items[i];
        if (a->active) {
            if (a->tick) {
                a->tick(a);
            }
            if (!(a->sprite & 4)) {
                SpriteSlot_TickAnim(&a->sprite);
            }
            if (a->postTick) {
                a->postTick(a);
            }
        }
    }

    for (i = 0; i < 256; i++) {
        a = &m->items[i];
        if (a->active) {
            ItemDescriptor *desc = &g_itemDescriptorTable[a->kind];
            if (desc->hasJoint) {
                if (JointByName_GetWorldPosition(&a->pos, &a->sprite, desc->joint) == 0) {
                    Vec3_Copy(&a->pos, &a->basePos);
                }
            } else {
                Vec3_Copy(&a->pos, &a->basePos);
            }
            a->radius = a->radiusScale * g_itemDescriptorTable[a->kind].radius;
            if (a->radius < 0.0f) {
                a->radius = 1.0f;
            }
        }
    }

    for (i = 0; i < 255; i++) {
        a = &m->items[i];
        if (!a->active || !a->category || !a->hitState) {
            continue;
        }
        for (j = i + 1; j < 256; j++) {
            b = &m->items[j];
            if (!b->active || !b->category || !b->hitState) {
                continue;
            }
            if (a->owner == b || b->owner == a) {
                continue;
            }
            if (a->owner != 0 && a->owner == b->owner) {
                continue;
            }
            if (a->category == 5 && b->category == 5) {
                continue;
            }
            if (a->type == 0x69 && b->type == 0x69) {
                continue;
            }
            if (a->type == 0x46 && b->type == 0x46) {
                continue;
            }
            if (a->category == 5) {
                ItemObject_CheckKartCollision(a, b);
            } else if (b->category == 5) {
                ItemObject_CheckKartCollision(b, a);
            } else {
                ItemObject_CheckPairCollision(a, b);
            }
        }
    }

    m->frame++;
    ItemHitRegistry_PruneStale();
}
#pragma use_lmw_stmw reset
