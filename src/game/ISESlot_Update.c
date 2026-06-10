/*
 * ISESlot_FrameUpdate @ 0x80049B70 (size 0x154)
 * ISESlot_SetByte18c  @ 0x80049CC4 (size 0x48)
 *
 * Two adjacent single-fn reversed-extab groups merged into one TU
 * (extab 0x800068A0..0x800068B0, extabindex 0x8002015C..0x80020174,
 * .text 0x80049B70..0x80049D0C). Built with CW 1.3.2 +
 * `-Cpp_exceptions on` so both extab/extabindex pairs are auto-emitted.
 *
 * ISESlot layout (extends the partial view in src/sound/ISESlot.c /
 * src/game/ISESlot_Deactivate.c):
 *   +0x00 : f32  timer (reset to lbl_806D26C8 when cleanup fires)
 *   +0x04 : u8   active flag
 *   +0x05 : u8   cleanup_pending flag
 *   +0x08 : s32  effect param (== 6 -> extra scale by lbl_806D26D0)
 *   +0x0C : s32  state (0 -> ItemSpawner_TimedRemapAndSpawn, 1 -> cleanup)
 *   +0x10 : s32  kart index
 *   +0x14 : s32  kind (0x12 -> respawn item 0x45 instead of releasing)
 *   +0x18 : ItemObject* bound item handle
 *   +0x1C : s32  pair param (forwarded to ItemObject_SetPair180)
 *   +0x20 : s32  column selector for ISE_ScaleColumnDirectionByMagnitude
 */

typedef struct ISESlot {
    float timer;            /* +0x00 */
    unsigned char active;   /* +0x04 */
    unsigned char pending;  /* +0x05 */
    unsigned char pad06[2]; /* +0x06 */
    int param;              /* +0x08 */
    int state;              /* +0x0C */
    int kartIdx;            /* +0x10 */
    int kind;               /* +0x14 */
    void *item;             /* +0x18 */
    int pairParam;          /* +0x1C */
    int column;             /* +0x20 */
} ISESlot;

typedef struct ISEVec3 {
    float x, y, z;
} ISEVec3;

extern const float lbl_806D26C8;
extern const float lbl_806D26CC;
extern const float lbl_806D26D0;

extern void ItemSpawner_TimedRemapAndSpawn(ISESlot *slot);
extern void ItemObject_SetByte18c(void *item, int val);
extern void *ItemObject_SpawnWithAlias(int alias, int param);
extern void ItemObject_SetPair180(void *item, int a, int b);
extern void *GetRaceContextPtr(void);
extern void *RaceContextSlot_GetIfAlive(void *ctx, int idx);
extern void ISE_ScaleColumnDirectionByMagnitude(void *kart, int column, ISEVec3 *out, float mag);
extern void ItemObject_WriteVec3At0x190To(void *item, ISEVec3 *vec);

#pragma exceptions on
int ISESlot_FrameUpdate(ISESlot *self) {
    ISEVec3 tmp;
    ISEVec3 vec;

    if (self->active == 0) {
        return 0;
    }
    switch (self->state) {
    case 0:
        ItemSpawner_TimedRemapAndSpawn(self);
        break;
    case 1:
        if (self->pending != 0) {
            self->timer = lbl_806D26C8;
            if (self->kind == 0x12) {
                if (self->item != 0) {
                    ItemObject_SetByte18c(self->item, 2);
                }
                self->item = ItemObject_SpawnWithAlias(0x45, 0xFF);
                ItemObject_SetPair180(self->item, self->kartIdx, self->pairParam);
            } else {
                ISE_ScaleColumnDirectionByMagnitude(
                    RaceContextSlot_GetIfAlive(GetRaceContextPtr(), self->kartIdx),
                    self->column, &vec, lbl_806D26CC);
                if (self->param == 6) {
                    vec.x *= lbl_806D26D0;
                    vec.y *= lbl_806D26D0;
                    vec.z *= lbl_806D26D0;
                }
                tmp = vec;
                ItemObject_WriteVec3At0x190To(self->item, &tmp);
                ItemObject_SetByte18c(self->item, 1);
                self->item = 0;
                self->active = 0;
                self->state += 1;
            }
        }
        break;
    }
    return 1;
}

int ISESlot_SetByte18c(ISESlot *self, char val) {
    void *item;
    if (self->active == 0) {
        return 0;
    }
    item = self->item;
    if (item != 0) {
        ItemObject_SetByte18c(item, val);
    }
    return 1;
}
#pragma exceptions reset
