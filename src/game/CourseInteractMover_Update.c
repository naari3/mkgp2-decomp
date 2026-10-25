typedef struct Vec3 {
    float x, y, z;
} Vec3;

extern const float lbl_806D5078; /* pi/12 */

extern void SpriteSlot_InitNonLoop(void *slot, int animId);
extern void Vec3_Subtract_DestFirst(float *dst, const float *a, const float *b);
extern void Vec3_Add_DestFirst(float *dst, const float *a, const float *b);
extern int Item_OrbitAnchorKart(unsigned char *self, float *offset, unsigned int timer, float a, float b);
extern void SpriteSlot_Container_Free(void *self);
extern void SpriteSlot_SetTransform(void *slot, float *pos, float *rot, float scale);

static inline void ItemObject_TickTimer(unsigned int *t)
{
    if (*t != 0) {
        (*t)--;
    }
}

void CourseInteractMover_Update(unsigned char *self)
{
    Vec3 pos;
    Vec3 rot;

    switch ((signed char)self[0xC8]) {
    case 0:
        SpriteSlot_InitNonLoop(self + 0x14, 0x96);
        Vec3_Subtract_DestFirst((float *)(self + 0x120), (float *)(self + 0xA0),
                                (float *)(*(unsigned char **)(self + 0x9C) + 0xA0));
        self[0xC8]++;
        break;
    case 1:
        break;
    }
    if (Item_OrbitAnchorKart(self, (float *)(self + 0x120), *(unsigned int *)(self + 0xF0), lbl_806D5078, lbl_806D5078)) {
        SpriteSlot_Container_Free(self);
        return;
    }
    Vec3_Add_DestFirst((float *)(self + 0xA0), (float *)(self + 0xA0), (float *)(self + 0xB8));
    rot = *(Vec3 *)(self + 0xAC);
    pos = *(Vec3 *)(self + 0xA0);
    SpriteSlot_SetTransform(self + 0x14, (float *)&pos, (float *)&rot, *(float *)(self + 0xC4));
    ItemObject_TickTimer((unsigned int *)(self + 0xF0));
    ItemObject_TickTimer((unsigned int *)(self + 0xF4));
    ItemObject_TickTimer((unsigned int *)(self + 0xF8));
    ItemObject_TickTimer((unsigned int *)(self + 0xFC));
}
