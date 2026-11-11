#include "game/types/gx_data.h"
#include <game/dlistutil_extract_private.h>

static inline unsigned char ReadQuadPosition(unsigned char *p, Vec *out) {
    int i;
    for (i = 0; i < 22; ++i) {
        if (!lbl_80677E18[i].desc || lbl_80677E18[i].desc->attr == 0xff) break;
        if (lbl_80677E18[i].desc->attr == 9) {
            unsigned int index;
            float *src;
            if (lbl_80677E18[i].desc->type == 3)
                index = GXDATA_U16(p + lbl_80677E18[i].offset);
            else
                index = *(unsigned char *)(p + lbl_80677E18[i].offset);
            src = lbl_80677E18[i].desc->array;
            src += index * (lbl_80677E18[i].desc->stride / 4);
            out->x = GXDATA_F32(src);
            out->y = GXDATA_F32(src + 1);
            out->z = GXDATA_F32(src + 2);
            return 1;
        }
    }
    return 0;
}

static inline int ReadPrimitive(unsigned char **cursor, int *primitive) {
    unsigned char *header = *cursor;
    int vertex_count;
    *primitive = header[0] & 0xf8;
    vertex_count = GXDATA_U16(header + 1);
    *cursor = header + 3;
    return vertex_count;
}

int fn_80184928(HSD_JObj *jobj, DListPObj *pobj, DListQuad *out) {
    Vec pos[4];
    int n;
    unsigned char *p;
    int count;
    int offset;
    MtxPtr matrix;
    int j;
    DListQuad *quad;
    Vec *dst;
    unsigned char *end;
    unsigned char *start;
    unsigned int size;
    int primitive;
    int half;

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
        n = ReadPrimitive(&p, &primitive);
        if (primitive != 0x80 && primitive != 0x98) {
            p += lbl_806D1678 * n;
            continue;
        }
        half = 0;
        if (primitive == 0x98) {
            dst = pos;
            quad = (DListQuad *)((unsigned char *)out + offset);
            for (j = 0; j < n; ++j) {
                if (j < 3) ReadQuadPosition(p, dst);
                else {
                    pos[0].x = pos[1].x;
                    pos[0].y = pos[1].y;
                    pos[0].z = pos[1].z;
                    pos[1].x = pos[2].x;
                    pos[1].y = pos[2].y;
                    pos[1].z = pos[2].z;
                    ReadQuadPosition(p, &pos[2]);
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
                ReadQuadPosition(p, &pos[half]);
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

