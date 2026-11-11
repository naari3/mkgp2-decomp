#include "game/types/gx_data.h"
#include "game/DListGeometryPrivate.h"

static inline float (*QuadMatrix(HSD_JObj *jobj))[4] {
    if (!jobj) __assert(lbl_806D9280, 0x47c, lbl_806D9288);
    SetupMatrix(jobj);
    return (float (*)[4])&jobj->_pad_1c[0x28];
}

static inline void QuadReadPosition(unsigned char *p, DListVec *out) {
    int i;
    for (i = 0; i < 22; ++i) {
        if (!lbl_80677E18[i].desc || lbl_80677E18[i].desc->attr == 255) break;
        if (lbl_80677E18[i].desc->attr == 9) {
            DListVtxDesc *desc;
            unsigned int index;
            float *v;
            if (lbl_80677E18[i].desc->type == 3) index = GXDATA_U16(p + lbl_80677E18[i].offset);
            else index = *(unsigned char *)(p + lbl_80677E18[i].offset);
            desc = lbl_80677E18[i].desc;
            v = desc->array;
            v += index * (desc->stride / 4);
            out->x = GXDATA_F32(v); out->y = GXDATA_F32(v + 1); out->z = GXDATA_F32(v + 2);
            break;
        }
    }
}

/* Return the first quad, accepting quads and four vertices of a strip. */
int fn_80185FE8(HSD_JObj *jobj, DListPObj *pobj,
                  DListVec *a, DListVec *b, DListVec *c, DListVec *d) {
    DListVec v[4];
    unsigned int collected;
    unsigned char *display, *p, *end;
    unsigned int size, primitive, n, i;
    if (!jobj || !pobj) return 0;
    if (!a || !b || !c || !d) return 0;
    display = pobj->display;
    end = display + pobj->n_display * 32;
    p = display;
    collected = 0;
    fn_801866DC(pobj->verts);
    if (lbl_806D1678 == 0) return 0;
    while (p < end) {
        size = CmdSize(p);
        if (size) { p += size; continue; }
        n = GXDATA_U16(p + 1);
        primitive = *p & 0xf8;
        p += 3;
        if (n < 4) { p += lbl_806D1678 * n; continue; }
        for (i = 0; i < n; ++i) {
            if (collected < 4) {
                QuadReadPosition(p, &v[collected]);
                ++collected;
            }
            p += lbl_806D1678;
        }
        if (collected == 4) {
            switch (primitive) {
            case 0x80:
                PSMTXMultVec(QuadMatrix(jobj), &v[0], a);
                PSMTXMultVec(QuadMatrix(jobj), &v[1], b);
                PSMTXMultVec(QuadMatrix(jobj), &v[2], c);
                PSMTXMultVec(QuadMatrix(jobj), &v[3], d);
                return 1;
            case 0x98:
                PSMTXMultVec(QuadMatrix(jobj), &v[0], a);
                PSMTXMultVec(QuadMatrix(jobj), &v[1], b);
                PSMTXMultVec(QuadMatrix(jobj), &v[2], d);
                PSMTXMultVec(QuadMatrix(jobj), &v[3], c);
                return 1;
            case 0x90: case 0xa0: case 0xa8: case 0xb0: case 0xb8: break;
            }
        }
        collected = 0;
    }
    return 0;
}
