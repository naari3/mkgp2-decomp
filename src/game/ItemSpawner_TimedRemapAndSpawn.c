/* NonMatching ~97.9%: CW coalesces the item id and the remapped result into
 * r3; the target keeps the id in r0 and seeds r3 with `mr r3, r0`. */
typedef struct ItemSpawner {
    float timer;
    unsigned char pad_04[8];
    int spawnCount;
    int pairA;
    int itemId;
    void *item;
    int pairB;
} ItemSpawner;

extern void *ItemObject_SpawnWithAlias(int id, int alias);
extern void ItemObject_SetPair180(void *item, int a, int b);

static inline int remap_item(int id) {
    int result = id;

    if (id == 0x7B) {
        result = 0x3D;
    } else if (id == 0x7C) {
        result = 0x32;
    } else if (id == 0x7D) {
        result = 0x17;
    } else if (id == 0x7E) {
        result = 0x50;
    } else if (id == 0x7F) {
        result = 0x39;
    } else if (id == 0x80) {
        result = 0x40;
    } else if (id == 0x81) {
        result = 0x2B;
    } else if (id == 0x82) {
        result = 0x46;
    } else if (id == 0x83) {
        result = 0x5D;
    } else if (id == 0x84) {
        result = 0x2D;
    } else if (id == 0x85) {
        result = 0x55;
    } else if (id == 0x86) {
        result = 0x4E;
    } else if (id == 0x87) {
        result = 0x3E;
    }
    return result;
}

#pragma exceptions on
void ItemSpawner_TimedRemapAndSpawn(ItemSpawner *spawner) {
    spawner->timer += 1.0f;
    if (spawner->timer <= 10.0f) {
        return;
    }
    {
        int id = remap_item(spawner->itemId);

        spawner->timer = 0.0f;
        spawner->item = ItemObject_SpawnWithAlias(id, 0xFF);
        ItemObject_SetPair180(spawner->item, spawner->pairA, spawner->pairB);
        spawner->spawnCount++;
    }
}

#pragma exceptions reset
