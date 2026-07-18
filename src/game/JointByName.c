/*
 * JointByName matrix getters (GitHub claim issue #13)
 *
 * JointByName_GetLocalMatrix4x3      @ 0x800D6670 (size 0xB8)
 * JointByName_GetMatrix4x4Transposed @ 0x800D6728 (size 0xB8)
 * JointByName_GetWorldPosition       @ 0x800D67E0 (size 0xF4)
 *
 * Three adjacent single-fn reversed-extab groups merged into one TU
 * (extab 0x8000B204..0x8000B21C, extabindex 0x80023894..0x800238B8,
 * .text 0x800D6670..0x800D68D4). Built with CW 1.3.2 +
 * `#pragma exceptions on` so all three extab/extabindex pairs are
 * auto-emitted in fn definition order.
 *
 * Each function resolves an HSD_JObj joint by name from the holder's
 * model (+0x4), lazily refreshes the joint matrix when the dirty flag
 * is set (inlined HSD_JObjGetMtx pattern, assert lines 0x47C / 0x25D
 * shared with the sysdolphin jobj.h helpers), then reads the joint's
 * 3x4 world matrix at +0x44.
 */

typedef float Mtx[3][4];

typedef struct HSD_JObj {
    unsigned char pad00[0x14]; /* +0x000 */
    unsigned int flags;        /* +0x014 */
    unsigned char pad18[0x2C]; /* +0x018 */
    Mtx mtx;                   /* +0x044 */
} HSD_JObj;

typedef struct JointByNameView {
    unsigned char pad00[0x4]; /* +0x000 */
    void *model;              /* +0x004 */
} JointByNameView;

extern char lbl_806D5968[7];
extern char lbl_806D5970[5];
extern void __assert(char *, int, char *);
extern HSD_JObj *ResolveJointByName(void *model, char *name);
extern void fn_802D1E34(HSD_JObj *jobj);
extern void fn_8025D1B8(const Mtx src, Mtx dst);
extern void Mtx_TransposeToMtx44(float *dst, const Mtx src);

static void update_matrix(HSD_JObj *jobj) {
    unsigned int flags;
    unsigned char dirty;

    flags = jobj->flags;
    dirty = 0;
    if (!(flags & 0x00800000) && (flags & 0x40)) {
        dirty = 1;
    }
    if (dirty) {
        fn_802D1E34(jobj);
    }
}

#pragma exceptions on
void JointByName_GetLocalMatrix4x3(Mtx dst, JointByNameView *holder, char *name) {
    HSD_JObj *jobj;
    float(*mtx)[4];

    if (holder != 0) {
        jobj = ResolveJointByName(holder->model, name);
        if (jobj != 0) {
            if (jobj == 0) {
                __assert(lbl_806D5968, 0x47C, lbl_806D5970);
            }
            if (jobj != 0) {
                if (jobj == 0) {
                    __assert(lbl_806D5968, 0x25D, lbl_806D5970);
                }
                update_matrix(jobj);
            }
            mtx = jobj->mtx;
            if (mtx != 0) {
                fn_8025D1B8(mtx, dst);
            }
        }
    }
}

void JointByName_GetMatrix4x4Transposed(float *dst, JointByNameView *holder, char *name) {
    HSD_JObj *jobj;
    float(*mtx)[4];

    if (holder != 0) {
        jobj = ResolveJointByName(holder->model, name);
        if (jobj != 0) {
            if (jobj == 0) {
                __assert(lbl_806D5968, 0x47C, lbl_806D5970);
            }
            if (jobj != 0) {
                if (jobj == 0) {
                    __assert(lbl_806D5968, 0x25D, lbl_806D5970);
                }
                update_matrix(jobj);
            }
            mtx = jobj->mtx;
            if (mtx != 0) {
                Mtx_TransposeToMtx44(dst, mtx);
            }
        }
    }
}

int JointByName_GetWorldPosition(float *out, JointByNameView *holder, char *name) {
    HSD_JObj *jobj;
    void *model;
    float(*mtx)[4];

    if (holder == 0) {
        return 0;
    }
    model = holder->model;
    if (model == 0) {
        return 0;
    }
    jobj = ResolveJointByName(model, name);
    if (jobj == 0) {
        return 0;
    }
    if (jobj == 0) {
        __assert(lbl_806D5968, 0x47C, lbl_806D5970);
    }
    if (jobj != 0) {
        if (jobj == 0) {
            __assert(lbl_806D5968, 0x25D, lbl_806D5970);
        }
        update_matrix(jobj);
    }
    mtx = jobj->mtx;
    if (mtx == 0) {
        return 0;
    }
    out[0] = mtx[0][3];
    out[1] = mtx[1][3];
    out[2] = mtx[2][3];
    return 1;
}
#pragma exceptions reset
