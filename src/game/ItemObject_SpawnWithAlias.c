/* ItemObject_SpawnWithAlias (0x800D7D08): allocates an item object for an
 * item id, resolving alias ids to their source item first. Id 0x10E (or
 * 0x45 spawned with arg 0x10E) is forced to the plain 0x45 item. */

typedef struct ItemAliasEntry {
    int source;
    int dest;
    int flags;
} ItemAliasEntry;

typedef struct ItemClassEntry {
    int def;
    unsigned char pad4[0x14 - 4];
} ItemClassEntry;

typedef struct ItemObject {
    signed char active;
    unsigned char pad1[3];
    int def;
    int kind;
    int unkC;
    unsigned char pad10[0x1DC - 0x10];
    signed char aliased;
    unsigned char pad1DD[3];
    int arg;
    unsigned char pad1E4[0x1EC - 0x1E4];
} ItemObject;

extern ItemAliasEntry g_itemAliasTable[155];
extern ItemClassEntry lbl_8041CBA8[];
extern ItemObject lbl_80638300[256];
extern int lbl_806D14D0;
extern void *memset(void *dst, int c, unsigned long n);

static inline ItemObject *ItemPool_Alloc(void)
{
    int cur = lbl_806D14D0;
    int i;

    for (i = 0; i < 256; i++) {
        int idx = (cur + 1) % 256;
        ItemObject *obj = &lbl_80638300[idx];
        if (obj->active == 0) {
            memset(obj, 0, sizeof(ItemObject));
            lbl_806D14D0 = idx;
            obj->active = 1;
            return obj;
        }
        cur++;
    }
    return 0;
}

static inline ItemObject *ItemObject_Create(int def)
{
    ItemObject *obj = ItemPool_Alloc();
    if (obj == 0) {
        return 0;
    }
    obj->def = def;
    return obj;
}

static inline int ItemAlias_FindSource(int id, signed char *found)
{
    int i;

    for (i = 0; i < 155; i++) {
        if (id == g_itemAliasTable[i].flags) {
            if (found) {
                *found = 1;
            }
            return g_itemAliasTable[i].source;
        }
    }
    if (found) {
        *found = 0;
    }
    return id;
}

ItemObject *ItemObject_SpawnWithAlias(int id, int arg)
{
    ItemObject *obj = 0;
    signed char found;

    if (id == 0x10E || (id == 0x45 && arg == 0x10E)) {
        obj = ItemObject_Create(lbl_8041CBA8[0x45].def);
        obj->kind = 0x45;
        obj->aliased = 1;
    }
    if (obj) {
        return obj;
    }
    found = 0;
    id = ItemAlias_FindSource(id, &found);
    obj = ItemObject_Create(lbl_8041CBA8[id].def);
    if (obj) {
        obj->unkC = 0;
        obj->kind = id;
        if (arg != 0 && arg != 0xFF) {
            obj->aliased = 1;
        } else {
            obj->aliased = found;
        }
        obj->arg = arg;
    }
    return obj;
}
