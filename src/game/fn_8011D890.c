/* --- owned .data 0x804221C8..0x80422208 (tools/own_data.py) --- */
#pragma force_active on
/* element type read off the values (all small integers), not from code */
int lbl_804221C8[16] = {
    0, 1, 2, 3, 4, 5, 6, 7,
    8, 9, 10, 11, 12, 13, 14, 15
};
#pragma force_active reset
#include "game/types/GXTexObj.h"
#include "game/types/GXTlutObj.h"
#include "game/types/TEXHeader.h"
#include "game/types/TEXDescriptor.h"

#include "game/types/ResourceSlot.h"

extern unsigned char IsValidResourceId(int id);
extern int ResourceTable_GetSlotIndex(int id);
extern void ResourceTable_GetSizeXY(int id, float *x, float *y);
extern int ResourceTable_GetGroupKey(int id);
extern void ResourceTable_GetOffsetXY(int id, float *x, float *y);
extern int ResourceTable_GetChainNextId(int id);
extern TEXDescriptor *TEXGetPaletteEntry(void *palette, unsigned int index);
extern void GXLoadTlut(GXTlutObj *obj, unsigned int name);
extern void GXLoadTexObj(GXTexObj *obj, int map);

extern ResourceSlot SpriteHandle_bss_806573E8[600];

static inline ResourceSlot *FindSlot(int group)
{
    int i;
    for (i = 0; i < 600; i++) {
        if (group == SpriteHandle_bss_806573E8[i].group) {
            return &SpriteHandle_bss_806573E8[i];
        }
    }
    return 0;
}

int fn_8011D890(int id, float *uv, float *uv2)
{
    float sx, sy;
    float w, h;
    float fx, fy;
    int idx;
    int next;
    ResourceSlot *slot;
    TEXDescriptor *d;

    if (!IsValidResourceId(id)) {
        return 0;
    }
    idx = ResourceTable_GetSlotIndex(id);
    ResourceTable_GetSizeXY(id, &sx, &sy);
    slot = FindSlot(ResourceTable_GetGroupKey(id));
    if (!slot) {
        return 0;
    }
    d = TEXGetPaletteEntry(slot->palette, idx);
    w = d->tex->width;
    h = d->tex->height;
    if (d->clut) {
        GXLoadTlut(&slot->tlutObjs[idx], lbl_804221C8[(signed char)slot->tlutNames[idx]]);
    }
    GXLoadTexObj(&slot->texObjs[idx], 0);
    ResourceTable_GetOffsetXY(id, &uv[0], &uv[1]);
    fx = 1.0f / w;
    fy = 1.0f / h;
    uv[0] += 0.5f;
    uv[0] += 0.5f;
    uv[0] = fx * uv[0];
    uv[1] = fy * uv[1];
    uv[2] = fx * (sx - 1.0f) + uv[0];
    uv[3] = fy * (sy - 1.0f) + uv[1];

    next = ResourceTable_GetChainNextId(id);
    if (next != -1) {
        if (!IsValidResourceId(next)) {
            return 0;
        }
        idx = ResourceTable_GetSlotIndex(next);
        ResourceTable_GetSizeXY(next, &sx, &sy);
        slot = FindSlot(ResourceTable_GetGroupKey(next));
        if (!slot) {
            return 0;
        }
        d = TEXGetPaletteEntry(slot->palette, idx);
        w = d->tex->width;
        h = d->tex->height;
        if (d->clut) {
            GXLoadTlut(&slot->tlutObjs[idx], lbl_804221C8[(signed char)slot->tlutNames[idx]]);
        }
        GXLoadTexObj(&slot->texObjs[idx], 1);
        if (uv2) {
            ResourceTable_GetOffsetXY(next, &uv2[0], &uv2[1]);
            fx = 1.0f / w;
            fy = 1.0f / h;
            uv2[0] += 0.5f;
            uv2[0] += 0.5f;
            uv2[0] = fx * uv2[0];
            uv2[1] = fy * uv2[1];
            uv2[2] = fx * (sx - 1.0f) + uv2[0];
            uv2[3] = fy * (sy - 1.0f) + uv2[1];
        }
    }
    return 1;
}
