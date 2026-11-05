/* ObjectTree_BlendOrCopy (0x800322F8): walk two (or three) parallel JObj
 * trees, blending the transforms of src/dst with blend (quaternion lerp)
 * or copying src's rotation/scale/position onto dst.
 *
 * Object_CopyFieldsRotPosScale lives in its own TU now but was a sibling of
 * this function in the original file: MWCC inlines it into the top level,
 * inlines the self-recursive call once, and leaves the copy inside that
 * inlined level as a real call. `extern inline` reproduces this without
 * emitting a second definition. */
typedef struct HSD_JObj {
    unsigned char pad00[0x8];
    struct HSD_JObj *next;  /* 0x08 */
    unsigned char pad0C[0x4];
    struct HSD_JObj *child; /* 0x10 */
    unsigned char pad14[0x8];
    float rotation[4];      /* 0x1C */
    float scale[3];         /* 0x2C */
    float position[3];      /* 0x38 */
} HSD_JObj;

extern const float lbl_806D2340;

extern unsigned int HSD_JObjGetFlags(HSD_JObj *jobj);
extern void ObjectTree_BlendQuatLerp(void *object, HSD_JObj *src, HSD_JObj *dst,
                                     HSD_JObj *blend, float weight);
extern inline void Object_CopyFieldsRotPosScale(void *object, HSD_JObj *src, HSD_JObj *dst)
{
    dst->position[0] = src->position[0];
    dst->position[1] = src->position[1];
    dst->position[2] = src->position[2];
    dst->rotation[0] = src->rotation[0];
    dst->rotation[1] = src->rotation[1];
    dst->rotation[2] = src->rotation[2];
    dst->rotation[3] = src->rotation[3];
    dst->scale[0] = src->scale[0];
    dst->scale[1] = src->scale[1];
    dst->scale[2] = src->scale[2];
}

#pragma exceptions on
#pragma use_lmw_stmw on
void ObjectTree_BlendOrCopy(void *object, HSD_JObj *src, HSD_JObj *dst,
                            HSD_JObj *blend, float weight)
{
    HSD_JObj *s;
    HSD_JObj *d;
    HSD_JObj *b;

    if (src == 0 || dst == 0) {
        return;
    }
    if (blend != 0) {
        ObjectTree_BlendQuatLerp(object, src, dst, blend, weight);
    } else {
        Object_CopyFieldsRotPosScale(object, src, dst);
    }
    if (HSD_JObjGetFlags(src) & 0x1000) {
        return;
    }
    if (blend != 0) {
        for (s = src->child, d = dst->child, b = blend->child; s != 0;
             s = s->next, d = d->next, b = b->next) {
            ObjectTree_BlendOrCopy(object, s, d, b, weight);
        }
    } else {
        for (s = src->child, d = dst->child; s != 0; s = s->next, d = d->next) {
            ObjectTree_BlendOrCopy(object, s, d, 0, lbl_806D2340);
        }
    }
}
#pragma use_lmw_stmw reset
#pragma exceptions reset
