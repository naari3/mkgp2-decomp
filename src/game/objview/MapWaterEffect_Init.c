/* --- owned .rodata 0x8037D220..0x8037D61C (tools/own_data.py) --- */
#pragma force_active on
/* was a byte array; cut into strings, floats and small integers by value and at the offsets this unit uses
 * (tools/autodata_bytes.py). x_ members are bytes that fit
 * none of these and are still in the console's byte order if they are wider than a byte. */
typedef struct MapWaterEffect_Init_rodata_8037D220_Pool {
    float f_000[255];
} MapWaterEffect_Init_rodata_8037D220_Pool;
const MapWaterEffect_Init_rodata_8037D220_Pool MapWaterEffect_Init_rodata_8037D220 = {
    { 1.0f, 0.7f, 0.9f, 0.0f, 0.0f, 500.0f, 66.66667f, 1000.0f, 66.66667f, 2000.0f, 66.66667f, 3000.0f, 66.66667f, 4000.0f, 66.66667f, 5000.0f, 66.66667f, 0.0f, 0.0f, 500.0f, 66.66667f, 1000.0f, 66.66667f, 2000.0f, 66.66667f, 3000.0f, 66.66667f, 4000.0f, 66.66667f, 5000.0f, 66.66667f, 0.0f, 0.0f, 500.0f, 66.66667f, 1000.0f, 66.66667f, 2000.0f, 66.66667f, 3000.0f, 66.66667f, 4000.0f, 66.66667f, 5000.0f, 66.66667f, 0.0f, 0.0f, 500.0f, 66.66667f, 1000.0f, 66.66667f, 2000.0f, 66.66667f, 3000.0f, 66.66667f, 4000.0f, 66.66667f, 5000.0f, 66.66667f, 0.0f, 0.0f, 500.0f, 66.66667f, 1000.0f, 66.66667f, 2000.0f, 66.66667f, 3000.0f, 66.66667f, 4000.0f, 66.66667f, 5000.0f, 66.66667f, 0.0f, 0.0f, 500.0f, 66.66667f, 1000.0f, 66.66667f, 2000.0f, 66.66667f, 3000.0f, 66.66667f, 4000.0f, 66.66667f, 5000.0f, 66.66667f, 0.0f, 0.0f, 500.0f, 66.66667f, 1000.0f, 66.66667f, 2000.0f, 66.66667f, 3000.0f, 66.66667f, 4000.0f, 66.66667f, 5000.0f, 66.66667f, 0.0f, 0.0f, 500.0f, 66.66667f, 1000.0f, 66.66667f, 2000.0f, 66.66667f, 3000.0f, 66.66667f, 4000.0f, 66.66667f, 5000.0f, 66.66667f, 0.0f, 0.0f, 500.0f, 66.66667f, 1000.0f, 66.66667f, 2000.0f, 66.66667f, 3000.0f, 66.66667f, 4000.0f, 66.66667f, 5000.0f, 66.66667f, 0.0f, 0.0f, 500.0f, 66.66667f, 1000.0f, 66.66667f, 2000.0f, 66.66667f, 3000.0f, 66.66667f, 4000.0f, 66.66667f, 5000.0f, 66.66667f, 0.0f, 0.0f, 500.0f, 66.66667f, 1000.0f, 66.66667f, 2000.0f, 66.66667f, 3000.0f, 66.66667f, 4000.0f, 66.66667f, 5000.0f, 66.66667f, 0.0f, 0.0f, 500.0f, 66.66667f, 1000.0f, 66.66667f, 2000.0f, 66.66667f, 3000.0f, 66.66667f, 4000.0f, 66.66667f, 5000.0f, 66.66667f, 0.0f, 0.0f, 500.0f, 83.333336f, 1000.0f, 83.333336f, 2000.0f, 83.333336f, 3000.0f, 83.333336f, 4000.0f, 83.333336f, 5000.0f, 83.333336f, 0.0f, 0.0f, 500.0f, 83.333336f, 1000.0f, 83.333336f, 2000.0f, 83.333336f, 3000.0f, 83.333336f, 4000.0f, 83.333336f, 5000.0f, 83.333336f, 0.0f, 0.0f, 500.0f, 83.333336f, 1000.0f, 83.333336f, 2000.0f, 83.333336f, 3000.0f, 83.333336f, 4000.0f, 83.333336f, 5000.0f, 83.333336f, 0.0f, 0.0f, 500.0f, 83.333336f, 1000.0f, 83.333336f, 2000.0f, 83.333336f, 3000.0f, 83.333336f, 4000.0f, 83.333336f, 5000.0f, 83.333336f, 0.0f, 0.0f, 500.0f, 83.333336f, 1000.0f, 83.333336f, 2000.0f, 83.333336f, 3000.0f, 83.333336f, 4000.0f, 83.333336f, 5000.0f, 83.333336f, 0.0f, 0.0f, 500.0f, 83.333336f, 1000.0f, 83.333336f, 2000.0f, 83.333336f, 3000.0f, 83.333336f, 4000.0f, 83.333336f, 5000.0f, 83.333336f }
};
#pragma force_active reset
/* MapWaterEffect_Init @ 0x80195B94: MapWaterEffect ctor. Picks the water
 * group table for the current cup and builds one Group per entry.
 * Written in C with explicit vtable stores (base lbl_80490FE0, then derived
 * lbl_80495F54): the C++ ctor form computes the string-pool base after both
 * vtable stores instead of between them. The extab (DELETEPOINTER for the
 * new'd Group, DESTROYBASE dtor_8016A270) is emitted by hand. The empty
 * cases 0/1/3/4 make MWCC pick the jump table (jumptable_80495F6C); with only
 * cases 2/8/10 it emits a compare tree. */
#include "game/types/GroupParams.h"
typedef struct Group { struct Group *next; void *model; void *items; } Group;
#include "game/types/MapWaterEffect.h"

extern void *lbl_80490FE0[];
extern void *lbl_80495F54[];
extern unsigned int g_cupId;
extern int g_longRoundFlag;
extern void DebugPrintf(const char *, ...);
extern void *Alloc(unsigned long);
extern void fn_80195DA8(Group *, GroupParams *);
extern void fn_80195CD4(Group *, Group *);
extern void MemoryManager_TimedFree(void *);
extern void dtor_8016A270(void);

MapWaterEffect *MapWaterEffect_Init(MapWaterEffect *self);

#pragma section R ".extab_user"
__declspec(section ".extab_user") static const struct {
    unsigned int w[9]; void *f9; unsigned int w10; unsigned int w11; void *f12;
} extab_MapWaterEffect_Init = {
    { 0x28080000, 0x00000040, 0x002B0028, 0x000000FC, 0x00000020,
      0x00000110, 0x00000028, 0x00000000, 0x0A80001B },
    (void *)&MemoryManager_TimedFree, 0x8680001F, 0x00000000, (void *)&dtor_8016A270
};
#pragma section R ".extabindex_user"
__declspec(section ".extabindex_user") static const struct {
    void *fn; unsigned int fn_size; const void *extab;
} extabindex_MapWaterEffect_Init = { (void *)&MapWaterEffect_Init, 0x00000140, &extab_MapWaterEffect_Init };

MapWaterEffect *MapWaterEffect_Init(MapWaterEffect *self) {
    const char *data;
    GroupParams *params;
    int count;
    int i;

    data = (const char *)&MapWaterEffect_Init_rodata_8037D220;
    self->vt = lbl_80490FE0;
    self->vt = lbl_80495F54;
    DebugPrintf(data + 0x620);
    self->groups = 0;
    self->type = g_cupId;
    params = 0;
    count = 0;
    switch (g_cupId) {
    case 0:
        break;
    case 1:
        break;
    case 3:
        break;
    case 4:
        break;
    case 2:
        if (g_longRoundFlag == 0) {
            params = (GroupParams *)(data + 0x584);
            count = 1;
        } else {
            params = (GroupParams *)(data + 0x5a4);
            count = 1;
        }
        break;
    case 10:
        params = (GroupParams *)(data + 0x584);
        count = 1;
        break;
    case 8:
        if (g_longRoundFlag == 1) {
            params = (GroupParams *)(data + 0x5d4);
            count = 1;
        }
        break;
    }
    if (params == 0 || count == 0) return self;
    for (i = 0; i < count; i++) {
        Group *g = (Group *)Alloc(0xc);
        if (g != 0) {
            fn_80195DA8(g, &params[i]);
        }
        if (self->groups) fn_80195CD4(self->groups, g);
        else self->groups = g;
    }
    return self;
}
