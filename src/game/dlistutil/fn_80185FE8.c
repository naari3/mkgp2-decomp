#include "game/DListGeometryPrivate.h"

/* Return the first quad, accepting quads and four vertices of a strip. */
int fn_80185FE8(HSD_JObj *jobj, DListPObj *pobj,
                  DListVec *a, DListVec *b, DListVec *c, DListVec *d) {
    DListVec v[4];
    unsigned int collected;
    unsigned char *p, *end;
    unsigned int size, primitive, n, i;
    if (!jobj || !pobj) return 0;
    if (!a || !b || !c || !d) return 0;
    p = pobj->display;
    end = p + pobj->n_display * 32;
    collected = 0;
    fn_801866DC(pobj->verts);
    if (lbl_806D1678 == 0) return 0;
    while (p < end) {
        size = CmdSize(p);
        if (size) { p += size; continue; }
        n = *(unsigned short *)(p + 1);
        primitive = *p & 0xf8;
        p += 3;
        if (n < 4) { p += lbl_806D1678 * n; continue; }
        for (i = 0; i < n; ++i) {
            if (collected < 4) {
                ReadPosition(p, &v[collected]);
                ++collected;
            }
            p += lbl_806D1678;
        }
        if (collected == 4) {
            switch (primitive) {
            case 0x80:
                PSMTXMultVec(GetMatrix(jobj), &v[0], a);
                PSMTXMultVec(GetMatrix(jobj), &v[1], b);
                PSMTXMultVec(GetMatrix(jobj), &v[2], c);
                PSMTXMultVec(GetMatrix(jobj), &v[3], d);
                return 1;
            case 0x98:
                PSMTXMultVec(GetMatrix(jobj), &v[0], a);
                PSMTXMultVec(GetMatrix(jobj), &v[1], b);
                PSMTXMultVec(GetMatrix(jobj), &v[2], d);
                PSMTXMultVec(GetMatrix(jobj), &v[3], c);
                return 1;
            case 0x90: case 0xa0: case 0xa8: case 0xb0: case 0xb8: break;
            }
        }
        collected = 0;
    }
    return 0;
}
