typedef struct Vec3 { float x, y, z; } Vec3;

extern void SpriteSlot_InitNonLoop(void *slot, int animId);
extern void fn_8010B664(unsigned char *self, unsigned char *ctx);
extern void Vec3_Subtract_DestFirst(void *dst, void *a, void *b);
extern void Item_PrepareHitRebound(void *self, void *pos, void *vel, void *timer);
extern void ItemHit_Dispatch(void *self, int a, void *pos, void *target);
extern unsigned char *ItemObject_SpawnWithAlias(int id, int alias);
extern void Vec3_Copy(void *dst, void *src);
extern void Vec3_AddNormalizedXZ(void *self, void *a, void *b);
extern void *KartDriver_GetKartRootMtx(void *kart);
extern void Mtx44_GetTranslation_RowMajor(void *out, void *mtx);
extern void Vec3_Add_DestFirst(void *dst, void *a, void *b);
extern void GetSpawnPosition(void *out, float x, float y, float z);
extern int Item_AdvanceTetherToJoint13(unsigned char *self, void *a, float b, float c, float d);
extern void DrawEffect_Free(void *e);
extern void SpriteSlot_Container_Free(void *self);
extern void SpriteSlot_SetTransform(void *slot, float *pos, float *rot, float scale);
extern void SpriteSlot_TickAnim(void *slot);
extern void JointByName_GetLocalMatrix4x3(void *out, void *slot, const char *name);
extern void VfxEffect_UpdateChildSpinMatrix_Helper(void *e, void *m);
extern char lbl_80331680[];

static inline void ItemObject_TickTimer(unsigned int *t)
{
    if (*t != 0) {
        (*t)--;
    }
}

void fn_8010BA74(unsigned char *self)
{
    unsigned char *sub = self + 0xEC;
    float m[3][4];
    Vec3 pos;
    Vec3 rot;
    Vec3 hitVel;
    Vec3 kartPos;
    unsigned char *o;

    switch ((signed char)self[0xC8]) {
    case 0:
        *(int *)(self + 0x8) = 0x70;
        SpriteSlot_InitNonLoop(self + 0x14, 0x6B);
        self[0x14] = 4;
        self[0x8C] = 4;
        self[0x8D] = 0;
        self[0xC8] = 1;
        self[0xC9] = 0;
    case 1:
        fn_8010B664(self, sub);
        break;
    case 2:
        switch ((signed char)self[0xCB]) {
        case 0:
            switch ((signed char)self[0xC9]) {
            case 0:
                Vec3_Subtract_DestFirst(self + 0xA0, self + 0xA0, self + 0xB8);
                Item_PrepareHitRebound(self, sub + 0x40, sub + 0x34, sub + 0x4);
                self[0xC9]++;
            case 1:
                break;
            }
            if (*(unsigned int *)(sub + 0x4) == 0) {
                if (sub[0] != 0) {
                    ItemHit_Dispatch(self, 0, self + 0xA0, *(void **)(sub + 0x9C));
                }
                o = ItemObject_SpawnWithAlias(0x64, 0xFF);
                if (o) {
                    Vec3_Copy(o + 0xA0, self + 0xA0);
                    *(int *)(o + 0x180) = *(int *)(sub + 0x94);
                    *(int *)(o + 0x184) = *(int *)(sub + 0x98);
                }
                self[0x28] = 0;
                self[0xC8] = 3;
                self[0xC9] = 0;
            } else {
                hitVel = *(Vec3 *)(sub + 0x34);
                Vec3_AddNormalizedXZ(self, sub + 0x40, &hitVel);
                Mtx44_GetTranslation_RowMajor(&kartPos, KartDriver_GetKartRootMtx(*(void **)(sub + 0x9C)));
                Vec3_Add_DestFirst(self + 0xA0, &kartPos, sub + 0x40);
            }
            break;
        case 3:
            switch ((signed char)self[0xC9]) {
            case 0:
                GetSpawnPosition(self + 0xB8, 0.0f, 0.0f, 0.0f);
                self[0x3C] = 0;
                *(float *)(sub + 0x14) = 0.0f;
                *(float *)(sub + 0x18) = *(float *)(self + 0xC4);
                self[0xC9]++;
            case 1:
                break;
            }
            if (Item_AdvanceTetherToJoint13(self, sub + 0x14, *(float *)(sub + 0x18), 0.087266445f, 0.087266445f)) {
                self[0x28] = 0;
                self[0xC8] = 3;
                self[0xC9] = 0;
            }
            break;
        case 4:
            o = ItemObject_SpawnWithAlias(0x64, 0xFF);
            if (o) {
                Vec3_Copy(o + 0xA0, self + 0xA0);
                *(int *)(o + 0x180) = *(int *)(sub + 0x94);
                *(int *)(o + 0x184) = *(int *)(sub + 0x98);
            }
            self[0x28] = 0;
            self[0xC8] = 3;
            self[0xC9] = 0;
            break;
        case 7:
            o = ItemObject_SpawnWithAlias(0x64, 0xFF);
            if (o) {
                Vec3_Copy(o + 0xA0, self + 0xA0);
                *(int *)(o + 0x180) = *(int *)(sub + 0x94);
                *(int *)(o + 0x184) = *(int *)(sub + 0x98);
            }
            self[0x28] = 0;
            self[0xC8] = 3;
            self[0xC9] = 0;
            break;
        case 9:
            switch ((signed char)self[0xC9]) {
            case 0:
                *(unsigned int *)(sub + 0x4) = 10;
                self[0xC9]++;
            case 1:
                break;
            }
            if (*(unsigned int *)(sub + 0x4) == 0) {
                *(float *)(self + 0x2C) = *(float *)(self + 0x2C) - 0.05f;
                if (*(float *)(self + 0x2C) < 0.0f) {
                    self[0x28] = 0;
                    self[0xC8] = 3;
                    self[0xC9] = 0;
                }
            }
            break;
        }
        break;
    case 3:
        DrawEffect_Free(*(void **)(sub + 0x4C));
        *(void **)(sub + 0x4C) = 0;
        SpriteSlot_Container_Free(self);
        return;
    }
    Vec3_Add_DestFirst(self + 0xA0, self + 0xA0, self + 0xB8);
    rot = *(Vec3 *)(self + 0xAC);
    pos = *(Vec3 *)(self + 0xA0);
    SpriteSlot_SetTransform(self + 0x14, (float *)&pos, (float *)&rot, *(float *)(self + 0xC4));
    SpriteSlot_TickAnim(self + 0x14);
    JointByName_GetLocalMatrix4x3(m, self + 0x14, lbl_80331680);
    VfxEffect_UpdateChildSpinMatrix_Helper(*(void **)(sub + 0x4C), m);
    ItemObject_TickTimer((unsigned int *)(sub + 0x4));
    ItemObject_TickTimer((unsigned int *)(sub + 0x8));
    ItemObject_TickTimer((unsigned int *)(sub + 0xC));
    ItemObject_TickTimer((unsigned int *)(sub + 0x10));
}
