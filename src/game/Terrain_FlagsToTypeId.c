typedef struct TerrainState {
    int a;                       /* 0x00 */
    int b;                       /* 0x04 */
    int c;                       /* 0x08 */
    int d;                       /* 0x0C */
    unsigned char pad10[0x70 - 0x10];
    int e;                       /* 0x70 */
    unsigned char pad74[0x84 - 0x74];
    int f;                       /* 0x84 */
    int g;                       /* 0x88 */
    int h;                       /* 0x8C */
    int i;                       /* 0x90 */
    int j;                       /* 0x94 */
} TerrainState;

#include "game/types/TerrainTypeEntry.h"

extern TerrainTypeEntry Terrain_FlagsToTypeId_data_8040F100[9];
extern int g_cupId;
extern int g_courseVariantIdx;
extern const float lbl_806D48B0;
extern const float lbl_806D48B4;
extern const float lbl_806D48B8;
extern const float lbl_806D48BC;
extern const float lbl_806D48C0;

void fn_800A51C4(TerrainState *s)
{
    s->a = -1;
    s->b = -1;
    s->c = 0;
    s->d = 0;
    s->e = 0;
    s->f = 0;
    s->g = 0;
    s->h = 0;
    s->i = -1;
    s->j = -1;
}

static inline unsigned int Terrain_TestMask(unsigned int mask, unsigned int flags)
{
    return (mask & flags) != 0;
}

int Terrain_FlagsToTypeId(unsigned int flags)
{
    int id = 0;
    int i;

    for (i = 0; i < 9; i++) {
        if (Terrain_TestMask(Terrain_FlagsToTypeId_data_8040F100[i].mask, flags) == 1) {
            id = Terrain_FlagsToTypeId_data_8040F100[i].id;
            break;
        }
    }
    return id;
}

unsigned int Terrain_ApplyCup2FlagPatch(unsigned int flags)
{
    unsigned int r = flags & 0xFF0FFFFF;
    if (g_cupId == 2 && (flags & 0x80)) {
        r &= ~0x80;
        r |= 0x40;
    }
    return r;
}
