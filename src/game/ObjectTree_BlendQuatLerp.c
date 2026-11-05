/* ObjectTree_BlendQuatLerp (0x800326D0): blend two JObj transforms into a
 * third one.  Position and scale are linearly interpolated; the rotation is
 * lerped along the shorter arc (src's quaternion is compared against dst's
 * and dst's is negated when the sum is shorter than the difference). */
typedef struct Quaternion {
    float x, y, z, w;
} Quaternion;

typedef struct HSD_JObj {
    unsigned char pad00[0x1C];
    Quaternion rotation; /* 0x1C */
    float scale[3];      /* 0x2C */
    float position[3];   /* 0x38 */
} HSD_JObj;

extern const float lbl_806D2344; /* 1.0f */
extern const char lbl_806D2348[7];
extern const char lbl_806D2350[5];
extern void __assert(const char *file, int line, const char *expression);
extern void PSQUATAdd(const Quaternion *p, const Quaternion *q, Quaternion *r);
extern void PSQUATSubtract(const Quaternion *p, const Quaternion *q, Quaternion *r);
extern float PSQUATDotProduct(const Quaternion *p, const Quaternion *q);
extern void C_QUATLerp(const Quaternion *p, const Quaternion *q, Quaternion *r, float t);

static inline void HSD_JObjGetRotation(HSD_JObj *jobj, Quaternion *quat)
{
    if (jobj == 0) {
        __assert(lbl_806D2348, 0x2DD, lbl_806D2350);
    }
    quat->x = jobj->rotation.x;
    quat->y = jobj->rotation.y;
    quat->z = jobj->rotation.z;
    quat->w = jobj->rotation.w;
}

#pragma exceptions on
void ObjectTree_BlendQuatLerp(void *object, HSD_JObj *src, HSD_JObj *dst,
                              HSD_JObj *blend, float weight)
{
    Quaternion q0;
    Quaternion q1;
    Quaternion tmp;
    float diff;

    blend->position[0] = src->position[0] * (lbl_806D2344 - weight) + dst->position[0] * weight;
    blend->position[1] = src->position[1] * (lbl_806D2344 - weight) + dst->position[1] * weight;
    blend->position[2] = src->position[2] * (lbl_806D2344 - weight) + dst->position[2] * weight;
    blend->scale[0] = src->scale[0] * (lbl_806D2344 - weight) + dst->scale[0] * weight;
    blend->scale[1] = src->scale[1] * (lbl_806D2344 - weight) + dst->scale[1] * weight;
    blend->scale[2] = src->scale[2] * (lbl_806D2344 - weight) + dst->scale[2] * weight;

    HSD_JObjGetRotation(src, &q0);
    HSD_JObjGetRotation(dst, &q1);
    PSQUATSubtract(&q0, &q1, &tmp);
    diff = PSQUATDotProduct(&tmp, &tmp);
    PSQUATAdd(&q0, &q1, &tmp);
    if (diff > PSQUATDotProduct(&tmp, &tmp)) {
        q1.x = -q1.x;
        q1.y = -q1.y;
        q1.z = -q1.z;
        q1.w = -q1.w;
    }
    C_QUATLerp(&q0, &q1, &blend->rotation, weight);
}
#pragma exceptions reset
