typedef struct VtxDesc {
    int attr;
    int type;
    int count;
    int format;
    int frac;
    void *array;
} VtxDesc;

#include "game/types/VtxAttrEntry.h"

extern VtxAttrEntry lbl_80677E18[22];
extern unsigned int lbl_806D1678;
extern const char lbl_80376F60[];
extern void DebugPrintf(const char *, ...);

void fn_801866DC(VtxDesc *verts) {
    const char *messages = lbl_80376F60;
    int i;
    lbl_806D1678 = 0;
    if (verts == 0) return;
    for (i = 0; i < 22; ++i, ++verts) {
        lbl_80677E18[i].desc = verts;
        lbl_80677E18[i].offset = lbl_806D1678;
        switch (verts->attr) {
        case 0: case 1: case 2: case 3: case 4:
        case 5: case 6: case 7: case 8:
            lbl_806D1678 += 1;
            break;
        case 9:
            if (verts->type == 3) lbl_806D1678 += 2;
            else if (verts->type == 2) lbl_806D1678 += 1;
            else {
                DebugPrintf(messages + 0x90);
                DebugPrintf(messages + 0x9c);
                lbl_806D1678 = 0;
                return;
            }
            break;
        case 10: case 25:
            if (verts->type == 3) lbl_806D1678 += 2;
            else lbl_806D1678 += 1;
            break;
        case 13: case 14: case 15: case 16:
        case 17: case 18: case 19: case 20:
            if (verts->type == 3) lbl_806D1678 += 2;
            else lbl_806D1678 += 1;
            break;
        case 11: case 12:
            if (verts->type == 3) lbl_806D1678 += 2;
            else if (verts->type == 2) lbl_806D1678 += 1;
            else {
                switch (verts->format) {
                case 0: case 3: lbl_806D1678 += 2; break;
                case 1: case 4: lbl_806D1678 += 3; break;
                case 2: case 5: lbl_806D1678 += 4; break;
                }
            }
            break;
        case 255: return;
        default:
            DebugPrintf(messages + 0xbc);
            lbl_806D1678 = 0;
            return;
        }
    }
}
