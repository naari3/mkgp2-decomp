/* Draw an item box: through the debris responder in channel 2, otherwise
 * as the shared box model placed, spun and faded per box, when it is on
 * screen and in front of the camera. */
typedef struct Vec {
    float x, y, z;
} Vec;

typedef struct clItemBoxResponder {
    unsigned char broken; /* 0x00 */
} clItemBoxResponder;

typedef struct clItemBox {
    unsigned char pad00[0x4];
    clItemBoxResponder *responder; /* 0x04 */
    Vec pos;                       /* 0x08 */
    float spin;                    /* 0x14 */
    unsigned char pad18[0xc];
    int state;                     /* 0x24 */
    unsigned char pad28[0x8];
    float alpha;                   /* 0x30 */
} clItemBox;

typedef struct GXChannel GXChannel;

extern int lbl_806CEEA0;
extern GXChannel *lbl_806D10B0;
extern GXChannel *lbl_806D10B4;
extern void *lbl_806D10BC;
extern const float lbl_806D29E0;
extern const double lbl_806D29F0;
extern const float lbl_806D2A04;
extern const float lbl_806D2A08;
extern const float lbl_806D2A0C;
extern void clItemBoxResponder_DrawDebris(clItemBoxResponder *self);
extern unsigned char fn_80137718(const Vec *pos, Vec *out, float radius);
extern void Object_SetColorAlphaOnly(void *object, int joint, float alpha);
extern void Object_SetJObjPositionXYZ(void *object, float x, float y, float z);
extern void Object_SetJObjRotationY(void *object, float y);
extern void *Object_GetJObjLocalMatrix(void *object);
extern void GXChannel_PushTransform(GXChannel *ch, void *mtx);

static inline void clItemBox_DrawModel(clItemBox *self, Vec *view)
{
    Object_SetColorAlphaOnly(lbl_806D10BC, 0, self->alpha);
    Object_SetJObjPositionXYZ(lbl_806D10BC, self->pos.x, lbl_806D2A0C + self->pos.y, self->pos.z);
    Object_SetJObjRotationY(lbl_806D10BC, lbl_806D29F0 * (lbl_806D29E0 * self->spin));
    if (lbl_806CEEA0 == 0) {
        GXChannel_PushTransform(lbl_806D10B4, Object_GetJObjLocalMatrix(lbl_806D10BC));
    } else {
        GXChannel_PushTransform(lbl_806D10B0, Object_GetJObjLocalMatrix(lbl_806D10BC));
    }
}

void clItemBox_Draw(clItemBox *self)
{
    Vec view;

    if (self->state == 3) {
        return;
    }
    if (lbl_806CEEA0 == 2) {
        clItemBoxResponder_DrawDebris(self->responder);
        return;
    }
    if (self->responder->broken == 1) {
        return;
    }
    if (!fn_80137718(&self->pos, &view, lbl_806D2A04) || view.z < lbl_806D2A08) {
        return;
    }
    clItemBox_DrawModel(self, &view);
}
