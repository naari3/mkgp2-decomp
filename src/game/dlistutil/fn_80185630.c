#include "game/types/gx_data.h"
#include "game/DListGeometryPrivate.h"

static inline float (*FaceMatrix(HSD_JObj *jobj))[4] {
    if (!jobj) __assert(lbl_806D9280, 0x47c, lbl_806D9288);
    SetupMatrix(jobj);
    return (float (*)[4])&jobj->_pad_1c[0x28];
}

/* Extract world-space faces, reversing winding and alternating strip parity. */
int fn_80185630(HSD_JObj *jobj, DListPObj *pobj, DListFace *faces, int capacity) {
    unsigned int size;
    DListVec v[4];
    DListFace *face;
    int primitive;
    int n;
    int collected;
    int needed;
    int parity;
    unsigned char *end;
    unsigned char *p;
    int count;
    unsigned char *display;
    int i;
    if (!jobj || !pobj) return 0;
    if (!faces || capacity <= 0) return 0;
    display = pobj->display;
    p = display;
    end = display + pobj->n_display * 32;
    count = 0;
    fn_801866DC(pobj->verts);
    if (lbl_806D1678 == 0) return 0;
    while (p < end) {
        size = CmdSize(p);
        if (size) { p += size; continue; }
        primitive = *p & 0xf8;
        n = GXDATA_U16(p + 1);
        p += 3;
        switch (primitive) {
        case 0x90: needed = 3; break;
        case 0x98: needed = 3; break;
        case 0x80: needed = 4; break;
        default: needed = 0; break;
        }
        if (n < needed || needed == 0) { p += lbl_806D1678 * n; continue; }
        collected = 0;
        parity = 0;
        for (i = 0; i < n; ++i) {
            ReadPosition(p, &v[collected++]);
            if (collected >= needed) {
                face = &faces[count];
                switch (primitive) {
                case 0x90:
                    PSMTXMultVec(FaceMatrix(jobj), &v[0], &face->v[2]);
                    PSMTXMultVec(FaceMatrix(jobj), &v[1], &face->v[1]);
                    PSMTXMultVec(FaceMatrix(jobj), &v[2], &face->v[0]);
                    collected = 0;
                    face->count = 3;
                    break;
                case 0x98:
                    if (parity == 0) {
                        PSMTXMultVec(FaceMatrix(jobj), &v[0], &face->v[2]);
                        PSMTXMultVec(FaceMatrix(jobj), &v[1], &face->v[1]);
                        PSMTXMultVec(FaceMatrix(jobj), &v[2], &face->v[0]);
                        face->count = 3;
                        parity = 1;
                    } else {
                        PSMTXMultVec(FaceMatrix(jobj), &v[0], &face->v[1]);
                        PSMTXMultVec(FaceMatrix(jobj), &v[1], &face->v[2]);
                        PSMTXMultVec(FaceMatrix(jobj), &v[2], &face->v[0]);
                        face->count = 3;
                        parity = 0;
                    }
                    collected = 2;
                    v[0].x = v[1].x; v[0].y = v[1].y; v[0].z = v[1].z;
                    v[1].x = v[2].x; v[1].y = v[2].y; v[1].z = v[2].z;
                    break;
                case 0x80:
                    PSMTXMultVec(FaceMatrix(jobj), &v[0], &face->v[3]);
                    PSMTXMultVec(FaceMatrix(jobj), &v[1], &face->v[2]);
                    PSMTXMultVec(FaceMatrix(jobj), &v[2], &face->v[1]);
                    PSMTXMultVec(FaceMatrix(jobj), &v[3], &face->v[0]);
                    collected = 0;
                    face->count = 4;
                    break;
                }
                ++count;
                if (count >= capacity) return count;
            }
            p += lbl_806D1678;
        }
    }
    return count;
}
