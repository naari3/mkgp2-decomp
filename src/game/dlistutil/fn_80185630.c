#include "game/DListGeometryPrivate.h"

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
                    PSMTXMultVec(GetMatrix(jobj), &v[0], &face->v[2]);
                    PSMTXMultVec(GetMatrix(jobj), &v[1], &face->v[1]);
                    PSMTXMultVec(GetMatrix(jobj), &v[2], &face->v[0]);
                    face->count = 3;
                    collected = 0;
                    break;
                case 0x98:
                    if (parity == 0) {
                        PSMTXMultVec(GetMatrix(jobj), &v[0], &face->v[2]);
                        PSMTXMultVec(GetMatrix(jobj), &v[1], &face->v[1]);
                        PSMTXMultVec(GetMatrix(jobj), &v[2], &face->v[0]);
                        face->count = 3;
                        parity = 1;
                    } else {
                        PSMTXMultVec(GetMatrix(jobj), &v[0], &face->v[1]);
                        PSMTXMultVec(GetMatrix(jobj), &v[1], &face->v[2]);
                        PSMTXMultVec(GetMatrix(jobj), &v[2], &face->v[0]);
                        face->count = 3;
                        parity = 0;
                    }
                    collected = 2;
                    v[0] = v[1];
                    v[1] = v[2];
                    break;
                case 0x80:
                    PSMTXMultVec(GetMatrix(jobj), &v[0], &face->v[3]);
                    PSMTXMultVec(GetMatrix(jobj), &v[1], &face->v[2]);
                    PSMTXMultVec(GetMatrix(jobj), &v[2], &face->v[1]);
                    PSMTXMultVec(GetMatrix(jobj), &v[3], &face->v[0]);
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
