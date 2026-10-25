typedef struct ItemPoolObject {
    unsigned char pad[0x10];
    int index;
} ItemPoolObject;

extern ItemPoolObject *ItemObject_AllocFromPool(void (*update)(ItemPoolObject *));
extern void CharaPop12_Update(ItemPoolObject *);
extern void DrawEffect_Free(void *);

void CharaPop12_SpawnAll(void *effect)
{
    int i;

    for (i = 0; i < 12; i++) {
        ItemPoolObject *obj = ItemObject_AllocFromPool(CharaPop12_Update);
        if (obj != 0) {
            obj->index = i;
            CharaPop12_Update(obj);
        }
    }
    DrawEffect_Free(effect);
}
