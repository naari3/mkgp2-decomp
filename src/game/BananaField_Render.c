/* BananaField_Render (0x80196AA0): draws idle bananas, then the bouncing/fading hit ones. */

typedef struct {
    int state;
    float x, y, z;
    float angle;
    float timer;
} Banana;
typedef struct {
    void *obj;
    Banana *items;
    int count;
} BananaField;

extern const float lbl_806D95B8;
extern const float lbl_806D95BC;
extern const float lbl_806D95C0;
extern const float lbl_806D95C4;
extern const float lbl_806D95C8;
extern const float lbl_806D95CC;
extern const float lbl_806D95D0;
extern const float lbl_806D95D4;
extern void Object_SetJObjRotationX(void *obj, float v);
extern void Object_SetJObjRotationZ(void *obj, float v);
extern void Object_SetColorAlphaOnly(void *obj, int idx, float a);
extern void Object_SetJObjPositionXYZ(void *obj, float x, float y, float z);
extern void Object_RenderJObjTree(void *obj, int flags);
extern float LUT_Sin12Bit(float a);
extern float LookupCos(float a);
extern float LookupSin(float a);

#pragma exceptions on
void BananaField_Render(BananaField *self) {
    Banana *b;
    float yofs;

    if (self->obj == 0 || self->items == 0 || self->count == 0) {
        return;
    }
    Object_SetJObjRotationX(self->obj, lbl_806D95B8);
    Object_SetJObjRotationZ(self->obj, lbl_806D95B8);
    Object_SetColorAlphaOnly(self->obj, 0, lbl_806D95BC);
    b = self->items;
    yofs = lbl_806D95C0;
    for (; b < self->items + self->count; b++) {
        if (b->state == 0) {
            Object_SetJObjPositionXYZ(self->obj, b->x, yofs + b->y, b->z);
            Object_RenderJObjTree(self->obj, 7);
        }
    }
    for (b = self->items; b < self->items + self->count; b++) {
        if (b->state == 1) {
            Object_SetJObjPositionXYZ(self->obj, b->x, lbl_806D95C4 * LUT_Sin12Bit(lbl_806D95C8 * b->timer) + b->y, b->z);
            Object_SetJObjRotationX(self->obj, lbl_806D95CC * (lbl_806D95D0 * b->timer) * LookupCos(b->angle));
            Object_SetJObjRotationZ(self->obj, lbl_806D95CC * (lbl_806D95D0 * b->timer) * LookupSin(b->angle));
            Object_SetColorAlphaOnly(self->obj, 0, lbl_806D95BC - lbl_806D95D4 * b->timer);
            Object_RenderJObjTree(self->obj, 7);
        }
    }
}
#pragma exceptions reset
