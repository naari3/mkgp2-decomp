extern int g_cupId;
extern int g_courseVariantIdx;
extern const float lbl_806D48B0;
extern const float lbl_806D48B4;
extern const float lbl_806D48B8;
extern const float lbl_806D48BC;
extern const float lbl_806D48C0;

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
