/* AnimState_UpdateEquipped @ 0x8003DF8C: pose the equipped item on the
 * kart (with its draw-in spin) and fire it when the equip timer hits 30. */

typedef float Mtx[3][4];

typedef struct HSD_JObj {
    unsigned char pad0[0x14];
    unsigned int flags;
    unsigned char pad18[0x44 - 0x18];
    Mtx mtx;
} HSD_JObj;

typedef struct Vec3 {
    float x, y, z;
} Vec3;

extern char lbl_806D2548[7];
extern char lbl_806D2550[5];
extern void __assert(char *file, int line, char *expr);
extern void HSD_JObjSetupMatrixSub(HSD_JObj *jobj);

static inline unsigned char HSD_JObjMtxIsDirty(HSD_JObj *jobj)
{
    unsigned char result;

    if (jobj == 0) {
        __assert(lbl_806D2548, 0x25D, lbl_806D2550);
    }
    result = 0;
    if (!(jobj->flags & 0x00800000) && (jobj->flags & 0x40)) {
        result = 1;
    }
    return result;
}

static inline void HSD_JObjSetupMatrix(HSD_JObj *jobj)
{
    if (jobj == 0) {
        return;
    }
    if (HSD_JObjMtxIsDirty(jobj)) {
        HSD_JObjSetupMatrixSub(jobj);
    }
}

static inline float (*HSD_JObjGetMtxPtr(HSD_JObj *jobj))[4]
{
    if (jobj == 0) {
        __assert(lbl_806D2548, 0x47C, lbl_806D2550);
    }
    HSD_JObjSetupMatrix(jobj);
    return jobj->mtx;
}

typedef struct ItemKartFlag {
    unsigned char pad0[4];
    unsigned char active; /* 0x4 */
} ItemKartFlag;

typedef struct ItemKart {
    unsigned char pad000[0x1C];
    void *object; /* 0x1C */
    unsigned char pad020[0x11C - 0x20];
    HSD_JObj *bodyJObj; /* 0x11C */
    unsigned char pad120[0x13C - 0x120];
    HSD_JObj *muzzleJObj; /* 0x13C */
    unsigned char pad140[0x174 - 0x140];
    unsigned char field174;
    unsigned char pad175[3];
    int equipTimer; /* 0x178 */
    float (*baseMtx)[4]; /* 0x17C */
    unsigned char pad180[0x1CC - 0x180];
    float dt; /* 0x1CC */
    unsigned char pad1D0[0x1DC - 0x1D0];
    float field1DC;
    float stunTime; /* 0x1E0 */
    float field1E4;
    unsigned char pad1E8[0x1F0 - 0x1E8];
    int field1F0;
    unsigned char pad1F4[0x204 - 0x1F4];
    unsigned char field204;
    unsigned char flag205;
    unsigned char pad206[0x218 - 0x206];
    int field218;
    unsigned char pad21C[0x290 - 0x21C];
    int counter290;
    float field294;
    unsigned char field298;
    unsigned char pad299[0x29C - 0x299];
    void *field29C;
    float timer2A0;
    int hitDir; /* 0x2A4 */
    unsigned char pad2A8[0x2B0 - 0x2A8];
    unsigned char field2B0;
    unsigned char pad2B1[2];
    unsigned char iseActive; /* 0x2B3 */
    int field2B4;
    unsigned char pad2B8[0x2C0 - 0x2B8];
    int currentItemId; /* 0x2C0 */
    signed char itemKind; /* 0x2C4 */
    unsigned char pad2C5[3];
    int currentISESlot; /* 0x2C8 */
    unsigned char pad2CC[0x2DC - 0x2CC];
    void *iseSlots[20]; /* 0x2DC */
    void *field32C;
    unsigned char pad330[0x35C - 0x330];
    ItemKartFlag *field35C;
    ItemKartFlag *field360;
    unsigned char pad364[0x36C - 0x364];
    float spinAngle; /* 0x36C */
    int spinFrame; /* 0x370 */
} ItemKart;

void ISESlot_Deactivate(void *slot);
void ISESlot_StopEffect(void *slot, int a, int b);
void ItemEffectState_Init(void *state, int id);
void fn_80173B68(void *p, int v);
void fn_80173BE8(void *p);

static inline void ClearCurrentItem(ItemKart *kart)
{
    if (kart->iseActive == 1) {
        ISESlot_Deactivate(kart->iseSlots[kart->currentISESlot]);
    }
    kart->field2B0 = 0;
    kart->iseActive = 0;
    kart->field2B4 = 0;
    kart->currentISESlot = -1;
    kart->currentItemId = -1;
    kart->flag205 = 0;
    if (kart->field32C != 0) {
        ItemEffectState_Init(kart->field32C, -1);
    }
    kart->field174 = 0;
    fn_80173B68(kart->field29C, 0);
    fn_80173BE8(kart->field29C);
    if (kart->field35C != 0) {
        kart->field35C->active = 0;
    }
    if (kart->field360 != 0) {
        kart->field360->active = 0;
    }
    fn_80173BE8(kart->field29C);
}


extern const float lbl_806D2540;
extern const float lbl_806D2558;
extern const float lbl_806D2560;
extern const float lbl_806D2568;
extern void PSMTXCopy(const Mtx src, Mtx dst);
extern void PSMTXRotRad(Mtx m, char axis, float rad);
extern void PSMTXConcat(const Mtx a, const Mtx b, Mtx ab);
extern void Object_BindMatrixSource(void *obj, Mtx m, int flag);
extern void Object_DriveAnimMatrix(void *obj);
extern void *ItemObject_SpawnWithAlias(int id, int alias);
extern void Vec3_Normalize(Vec3 *src, Vec3 *dst);
extern void ItemObject_WritePositionTo(void *obj, Vec3 v);
extern void ItemObject_WriteVec3At0x190To(void *obj, Vec3 v);
extern void ItemObject_SetPair180(void *obj, int a, ItemKart *kart);
extern void ItemObject_SetField168(void *obj, ItemKart *kart);
extern unsigned char fn_80173BD0(void *p);
extern ItemKart **ItemEffectMgr_GetPickedSlot(void *state);

int AnimState_UpdateEquipped(ItemKart *kart)
{
    float (*bodyMtx)[4];
    HSD_JObj *jobj;
    Mtx m;

    if (kart->object == 0) {
        return 0;
    }
    jobj = kart->bodyJObj;
    if (jobj == 0) {
        return 0;
    }
    if (kart->field174 == 0) {
        return 0;
    }
    bodyMtx = jobj == 0 ? 0 : HSD_JObjGetMtxPtr(jobj);
    if (kart->spinFrame >= 0) {
        Mtx rot;

        PSMTXCopy(kart->baseMtx, m);
        m[0][3] = m[1][3] = m[2][3] = lbl_806D2540;
        PSMTXRotRad(rot, 'Y', lbl_806D2558 * -kart->spinAngle);
        PSMTXConcat(rot, m, m);
        if (kart->spinFrame > 1 && kart->spinFrame < 11) {
            if ((kart->spinAngle += 20.0f) >= lbl_806D2560) {
                kart->spinAngle = lbl_806D2560;
            }
        } else if (kart->spinFrame > 26 && kart->spinFrame < 40) {
            if ((kart->spinAngle -= 14.285714f) <= lbl_806D2540) {
                kart->spinAngle = lbl_806D2540;
            }
        }
        kart->spinFrame++;
    } else {
        PSMTXCopy(kart->baseMtx, m);
    }
    m[0][3] = bodyMtx[0][3];
    m[1][3] = bodyMtx[1][3];
    m[2][3] = bodyMtx[2][3];
    Object_BindMatrixSource(kart->object, m, 0);
    Object_DriveAnimMatrix(kart->object);
    if (kart->equipTimer != 0) {
        kart->equipTimer--;
        if (kart->equipTimer == 0) {
            ClearCurrentItem(kart);
            kart->field1F0 = 0;
            kart->field204 = 1;
            kart->field1DC = lbl_806D2568;
        }
        if (kart->equipTimer == 30) {
            int id = 0;
            int alias = 0xFF;
            void *obj;
            float (*muzzleMtx)[4];
            Vec3 pos;
            Vec3 dir;

            if (kart->currentItemId == 0x6C) {
                id = 0x35;
                alias = 0x35;
            } else if (kart->currentItemId == 0x6D) {
                id = 0x36;
                alias = 0x36;
            } else if (kart->currentItemId == 0x6E) {
                id = 0x49;
                alias = 0x49;
            } else if (kart->currentItemId == 0x6F) {
                id = 0x70;
                alias = 0x70;
            }
            obj = ItemObject_SpawnWithAlias(id, alias);
            jobj = kart->muzzleJObj;
            muzzleMtx = jobj == 0 ? 0 : HSD_JObjGetMtxPtr(jobj);
            pos.x = muzzleMtx[0][3];
            pos.y = muzzleMtx[1][3];
            pos.z = muzzleMtx[2][3];
            dir.x = m[0][2];
            dir.y = lbl_806D2540;
            dir.z = m[2][2];
            Vec3_Normalize(&dir, &dir);
            ItemObject_WritePositionTo(obj, pos);
            ItemObject_WriteVec3At0x190To(obj, dir);
            ItemObject_SetPair180(obj, kart->field218, kart);
            if (kart->itemKind == 6 && fn_80173BD0(kart->field29C) && kart->field32C != 0 &&
                ItemEffectMgr_GetPickedSlot(kart->field32C) != 0) {
                ItemObject_SetField168(obj, *ItemEffectMgr_GetPickedSlot(kart->field32C));
            }
        }
    }
    return 1;
}
