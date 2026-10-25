typedef struct Vec3 { float x, y, z; } Vec3;

extern unsigned char *ItemObject_SpawnWithAlias(int kind, int alias);
extern void ItemObject_SetByte18c(void *obj, int v);
extern void ItemObject_WriteVec3At0x190To(void *obj, Vec3 v);
extern void ItemObject_SetField168(void *obj, int v);
extern void SpriteSlot_Container_Free(void *self);

void fn_8011297C(unsigned char *self)
{
    switch ((signed char)self[0xC8]) {
    case 0:
        self[0xC8]++;
    case 1:
        self[0xEC] = 0;
        *(unsigned char **)(self + 0x148) = 0;
        switch (*(int *)(self + 0x8)) {
        case 0x7B:
            *(unsigned char **)(self + 0x148) = ItemObject_SpawnWithAlias(0x3D, 0xFF);
            break;
        case 0x7C:
            *(unsigned char **)(self + 0x148) = ItemObject_SpawnWithAlias(0x32, 0xFF);
            break;
        case 0x7D:
            *(unsigned char **)(self + 0x148) = ItemObject_SpawnWithAlias(0x17, 0xFF);
            break;
        case 0x7E:
            *(unsigned char **)(self + 0x148) = ItemObject_SpawnWithAlias(0x50, 0xFF);
            break;
        case 0x7F:
            *(unsigned char **)(self + 0x148) = ItemObject_SpawnWithAlias(0x39, 0xFF);
            break;
        case 0x80:
            *(unsigned char **)(self + 0x148) = ItemObject_SpawnWithAlias(0x40, 0xFF);
            break;
        case 0x81:
            *(unsigned char **)(self + 0x148) = ItemObject_SpawnWithAlias(0x2B, 0xFF);
            break;
        case 0x82:
            *(unsigned char **)(self + 0x148) = ItemObject_SpawnWithAlias(0x46, 0xFF);
            break;
        case 0x83:
            *(unsigned char **)(self + 0x148) = ItemObject_SpawnWithAlias(0x5D, 0xFF);
            break;
        case 0x84:
            *(unsigned char **)(self + 0x148) = ItemObject_SpawnWithAlias(0x2D, 0xFF);
            break;
        case 0x85:
            *(unsigned char **)(self + 0x148) = ItemObject_SpawnWithAlias(0x55, 0xFF);
            break;
        case 0x86:
            *(unsigned char **)(self + 0x148) = ItemObject_SpawnWithAlias(0x4E, 0xFF);
            break;
        case 0x87:
            *(unsigned char **)(self + 0x148) = ItemObject_SpawnWithAlias(0x3E, 0xFF);
            break;
        }
        if (*(unsigned char **)(self + 0x148)) {
            *(int *)(*(unsigned char **)(self + 0x148) + 0x180) = *(int *)(self + 0x180);
            *(int *)(*(unsigned char **)(self + 0x148) + 0x184) = *(int *)(self + 0x184);
        }
        self[0xC8]++;
    case 2:
        if (self[0xEC] || *(char *)(self + 0x18C) == 1) {
            if (*(unsigned char **)(self + 0x148)) {
                ItemObject_SetByte18c(*(unsigned char **)(self + 0x148), 1);
                ItemObject_WriteVec3At0x190To(*(unsigned char **)(self + 0x148), *(Vec3 *)(self + 0x190));
                ItemObject_SetField168(*(unsigned char **)(self + 0x148), *(int *)(self + 0x168));
                *(unsigned char **)(self + 0x148) = 0;
            }
            if (!*(signed char *)(self + 0x18C)) {
                self[0xC8] = 1;
                break;
            }
        }
        if (*(signed char *)(self + 0x18C)) {
            if (*(unsigned char **)(self + 0x148)) {
                ItemObject_SetByte18c(*(unsigned char **)(self + 0x148), 2);
                *(unsigned char **)(self + 0x148) = 0;
            }
            SpriteSlot_Container_Free(self);
        }
        break;
    }
}
