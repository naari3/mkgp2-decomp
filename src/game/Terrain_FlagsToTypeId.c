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

typedef struct TerrainTypeEntry {
    unsigned int mask;
    signed char id;
} TerrainTypeEntry;

extern TerrainTypeEntry lbl_8040F100[9];
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
        if (Terrain_TestMask(lbl_8040F100[i].mask, flags) == 1) {
            id = lbl_8040F100[i].id;
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

static inline unsigned int Terrain_PatchHi(unsigned int flags)
{
    unsigned int mask = 0;
    unsigned int add = 0;
    if (flags & 0x800000) {
        mask |= 0x800000;
        add |= 0x100000;
    }
    flags &= mask;
    flags |= add;
    return flags;
}

static inline unsigned int Terrain_PatchLo(unsigned int flags)
{
    unsigned int r = flags & 0xFF0FFFFF;
    if (g_cupId == 2 && (r & 0x80)) {
        r &= ~0x80;
        r |= 0x40;
    }
    return r;
}

static inline unsigned int Terrain_PatchFlags(unsigned int flags)
{
    unsigned int hi = flags;
    unsigned int lo = flags & 0xFF0FFFFF;
    if (g_cupId == 2 && (lo & 0x80)) {
        lo &= ~0x80;
        lo |= 0x40;
        hi = Terrain_PatchHi(flags);
    }
    return lo | (hi & 0xF00000);
}

float Terrain_GetTractionFactor(unsigned int flags)
{
    unsigned int f = Terrain_PatchFlags(flags) & 0x500000;
    if (f & 0x100000) {
        return lbl_806D48B0;
    }
    if (f & 0x400000) {
        return lbl_806D48B4;
    }
    return lbl_806D48B8;
}

float Terrain_GetSlipFactor(unsigned int flags)
{
    unsigned int f = Terrain_PatchFlags(flags) & 0xA00000;
    float v = lbl_806D48B8;
    if (g_cupId == 2 && g_courseVariantIdx == 1) {
        v = lbl_806D48BC;
    }
    if (f & 0x200000) {
        v *= lbl_806D48C0;
    }
    if (f & 0x800000) {
        v *= lbl_806D48B0;
    }
    return v;
}
