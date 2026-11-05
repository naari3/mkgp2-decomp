#include <game/dlistutil_extract_private.h>

int fn_80184928(HSD_JObj *jobj, DListPObj *pobj, DListQuad *out) {
    Vec pos[4];
    int n;
    unsigned char *p;
    int count;
    int offset;
    MtxPtr matrix;
    unsigned int size;
    int primitive;
    int j;
    int half;
    DListQuad *quad;
    Vec *dst;
    unsigned char *end;
    unsigned char *start;

    if (!jobj || !pobj) return 0;
    if (!out) return 0;
    matrix = DListGetMatrix(jobj);
    start = pobj->display;
    p = start;
    end = start + pobj->n_display * 32;
    count = 0;
    offset = 0;
    fn_801866DC(pobj->verts);
    if (!lbl_806D1678) return 0;
    while (p < end) {
        size = DListCmdSize(p);
        if (size) { p += size; continue; }
        primitive = *p & 0xf8;
        n = *(unsigned short *)(p + 1);
        p += 3;
        if (primitive != 0x80 && primitive != 0x98) {
            p += lbl_806D1678 * n;
            continue;
        }
        half = 0;
        if (primitive == 0x98) {
            dst = pos;
            quad = (DListQuad *)((unsigned char *)out + offset);
            for (j = 0; j < n; ++j) {
                if (j < 3) DListGetPosition(p, dst);
                else {
                    pos[0].x = pos[1].x;
                    pos[0].y = pos[1].y;
                    pos[0].z = pos[1].z;
                    pos[1].x = pos[2].x;
                    pos[1].y = pos[2].y;
                    pos[1].z = pos[2].z;
                    DListGetPosition(p, &pos[2]);
                }
                if (j >= 2) {
                    if (!half) {
                        PSMTXMultVec(matrix, &pos[0], &quad->vertex[0]);
                        PSMTXMultVec(matrix, &pos[1], &quad->vertex[1]);
                        PSMTXMultVec(matrix, &pos[2], &quad->vertex[3]);
                        half = 1;
                    } else {
                        PSMTXMultVec(matrix, &pos[2], &quad->vertex[2]);
                        ++count;
                        half = 0;
                        ++quad;
                        offset += sizeof(DListQuad);
                        if (count >= 6) return 1;
                    }
                }
                p += lbl_806D1678;
                ++dst;
            }
        } else {
            quad = (DListQuad *)((unsigned char *)out + offset);
            for (j = 0; j < n; ++j) {
                half = j & 3;
                DListGetPosition(p, &pos[half]);
                if (half == 3) {
                    PSMTXMultVec(matrix, &pos[0], &quad->vertex[0]);
                    PSMTXMultVec(matrix, &pos[1], &quad->vertex[1]);
                    PSMTXMultVec(matrix, &pos[2], &quad->vertex[2]);
                    PSMTXMultVec(matrix, &pos[3], &quad->vertex[3]);
                    ++count;
                    offset += sizeof(DListQuad);
                    ++quad;
                    if (count >= 6) return 1;
                }
                p += lbl_806D1678;
            }
        }
    }
    return 0;
}
