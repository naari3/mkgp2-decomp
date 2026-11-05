#include "game/DListGeometryPrivate.h"

static inline float (*FaceMatrix(HSD_JObj *jobj))[4] {
    if (!jobj) __assert(lbl_806D9280, 0x47c, lbl_806D9288);
    SetupMatrix(jobj);
    return (float (*)[4])&jobj->_pad_1c[0x28];
}

/* Extract world-space faces, reversing winding and alternating strip parity. */
int fn_80185630(HSD_JObj *jobj, DListPObj *pobj, DListFace *out, int capacity) {
    DListVec v[4];
    unsigned char *p, *end;
    int count;
    unsigned int size;
    int n, primitive, needed, collected, i, parity;
    DListFace *face;
    if (!jobj || !pobj) return 0;
    if (!out || capacity <= 0) return 0;
    count = 0;
    p = pobj->display;
    end = p + pobj->n_display * 32;
    fn_801866DC(pobj->verts);
    if (lbl_806D1678 == 0) return 0;
    while (p < end) {
        size = CmdSize(p);
        if (size) { p += size; continue; }
        primitive = *p & 0xf8;
        n = *(unsigned short *)(p + 1);
        p += 3;
        switch (primitive) {
        case 0x90: needed = 3; break;
        case 0x98: needed = 3; break;
        case 0x80: needed = 4; break;
        default: needed = 0; break;
        }
        if (n < needed || needed == 0) { p += lbl_806D1678 * n; continue; }
        face = out;
        collected = 0;
        parity = 0;
        for (i = 0; i < n; ++i) {
            ReadPosition(p, &v[collected++]);
            if (collected >= needed) {
                switch (primitive) {
                case 0x90:
                    PSMTXMultVec(FaceMatrix(jobj), &v[0], &face->v[2]);
                    PSMTXMultVec(FaceMatrix(jobj), &v[1], &face->v[1]);
                    PSMTXMultVec(FaceMatrix(jobj), &v[2], &face->v[0]);
                    face->count = 3;
                    collected = 0;
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
                    face->count = 4;
                    collected = 0;
                    break;
                }
                ++count;
                ++out;
                ++face;
                if (count >= capacity) return count;
            }
            p += lbl_806D1678;
        }
    }
    return count;
}
