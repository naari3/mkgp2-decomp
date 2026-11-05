#include <game/dlistutil_extract_private.h>

static inline MtxPtr DListQuadMatrix(HSD_JObj *jobj) {
    if (!jobj) __assert(lbl_806D9280, 0x47c, lbl_806D9288);
    if (jobj && DListMatrixDirty(jobj)) HSD_JObjSetupMatrixSub(jobj);
    return (MtxPtr)&jobj->_pad_1c[0x28];
}

int fn_80184F24(HSD_JObj *jobj, DListPObj *pobj, DListQuadInfo *out, int capacity) {
    Vec pos[4];
    unsigned char *end;
    int offset;
    int count;
    unsigned char *p;
    int used;
    unsigned int size;
    int n;
    int primitive;
    int j;
    DListQuadInfo *quad;
    unsigned char *start;

    if (!jobj || !pobj) return 0;
    if (!out || capacity <= 0) return 0;
    start = pobj->display;
    p = start;
    end = start + pobj->n_display * 32;
    used = 0;
    count = 0;
    offset = 0;
    fn_801866DC(pobj->verts);
    if (!lbl_806D1678) return 0;
    while (p < end) {
        size = DListCmdSize(p);
        if (size) { p += size; continue; }
        n = *(unsigned short *)(p + 1);
        primitive = *p & 0xf8;
        p += 3;
        if (n < 4 || (primitive != 0x80 && primitive != 0x98)) {
            p += lbl_806D1678 * n;
            continue;
        }
        for (j = 0; j < n; ++j) {
            DListGetPosition(p, &pos[used++]);
            if (used >= 4) {
                if (primitive == 0x98) {
                    quad = (DListQuadInfo *)((unsigned char *)out + offset);
                    PSMTXMultVec(DListQuadMatrix(jobj), &pos[0], &quad->vertex[0]);
                    PSMTXMultVec(DListQuadMatrix(jobj), &pos[1], &quad->vertex[1]);
                    PSMTXMultVec(DListQuadMatrix(jobj), &pos[2], &quad->vertex[3]);
                    PSMTXMultVec(DListQuadMatrix(jobj), &pos[3], &quad->vertex[2]);
                    quad->flags = 0;
                    quad->value1 = lbl_806D927C;
                    quad->value2 = lbl_806D927C;
                    ++count;
                    used = 0;
                    offset += sizeof(DListQuadInfo);
                    if (count >= capacity) return count;
                } else if (primitive == 0x80) {
                    quad = (DListQuadInfo *)((unsigned char *)out + offset);
                    PSMTXMultVec(DListQuadMatrix(jobj), &pos[0], &quad->vertex[0]);
                    PSMTXMultVec(DListQuadMatrix(jobj), &pos[1], &quad->vertex[1]);
                    PSMTXMultVec(DListQuadMatrix(jobj), &pos[2], &quad->vertex[2]);
                    PSMTXMultVec(DListQuadMatrix(jobj), &pos[3], &quad->vertex[3]);
                    quad->flags = 0;
                    quad->value1 = lbl_806D927C;
                    quad->value2 = lbl_806D927C;
                    ++count;
                    used = 0;
                    offset += sizeof(DListQuadInfo);
                    if (count >= capacity) return count;
                }
            }
            p += lbl_806D1678;
        }
        used = 0;
    }
    return count;
}
